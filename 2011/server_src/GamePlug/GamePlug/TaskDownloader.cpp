#include "stdafx.h"
#include "TaskDownloader.h"


#include "../../../include/AsyncIO/iocp/WinException.hpp"
#include "../../../include/Extend STL/StringAlgorithm.h"
#include "../../../include/Zip/XUnzip.h"
#include "../../../include/Win32/FileSystem/FileHelper.hpp"

#include "TaskItem.h"

#include "LogHelper.h"
#include "DataSvrHelper.h"
#include "Msc.h"
#include "PLInfo.h"

namespace i8desk
{


	// ��������
	namespace 
	{
		template< typename T, size_t N >
		inline bool _CheckDiskSpace(const T (&dir)[N], ulonglong diskSpaceLimit = 1024LL * 1024LL * 1024LL * 30LL)
		{
			// ���Ŀ¼�Ƿ��㹻
			stdex::tString info;
			stdex::tString path(dir);
			if( !win32::file::CheckDiskSpace(path, diskSpaceLimit, info) )
			{
				Log(LM_WARNING, info);
				return false;
			}

			return true;
		}

		// ��ȡ�����б��е���������
		template<typename ListT, typename ContainerT>
		void GetJobList(const ListT &taskList, size_t jobCnt, ContainerT &container)
		{
			unsigned int i = 0, j = 0, k = 0;

			while( k < jobCnt )
			{
				if( taskList[i] == 0 )
				{
					wchar_t taskName[256] = {0};
					wcsncpy_s(taskName, &taskList[j], _countof(taskName));

					j = i + 1;
			
					container[k] = taskName;
					
					++k;
				}
				++i;
			}

			
		}


		template<typename EventT>
		inline bool IsStop(EventT &event)
		{
			if( ::WaitForSingleObject(event, 0) == WAIT_OBJECT_0 )
				return true;

			return false;
		}

	}

	// ����ɾ��
	template < typename CharT, size_t N >
	void SmartClean(const CharT (&path)[N], IRTDataSvr *rtData, long curGID)
	{
		// 1. 15��
		// 2. 100M
		// 3. ���ص������
		// 4. ���ĵ������
		// 5. ��С��

		struct SmartCleanPolicy
		{
			bool operator()(const db::tGame *lhs, const db::tGame *rhs) const
			{
				return lhs->SvrClick < rhs->SvrClick ||
					(lhs->SvrClick == rhs->SvrClick && lhs->IdcClick < rhs->IdcClick);
			}
		};

				
		IGameRecordset *record = 0;
		rtData->GetGameTable()->Select(&record, 0, 0);

		std::vector<const db::tGame *> cleanGames;
		cleanGames.reserve(record->GetCount());
		const db::tGame *curGame = 0;
		for(size_t i = 0; i != record->GetCount(); ++i)
		{
			const db::tGame *game = record->GetData(i);

			if( game->Status != StatusLocal || game->Force )
				continue;

			if( game->GID == curGID )
				curGame = game;

			CTime start(game->SvrVer);
			CTime end = CTime::GetCurrentTime();
			CTimeSpan span = end - start;
			
			if( game->GID != curGID &&
				span.GetDays() > 15 && 
				game->Size >= 100 * 1024 )
				cleanGames.push_back(game);
		}
		
		std::sort(cleanGames.begin(), cleanGames.end(), SmartCleanPolicy());

		// ֻ��Ҫ�г����ϴ�С����Ϸ
		const ulonglong matchSize = curGame->Size * 1024LL;

		ulonglong totalSize = 0;
		size_t i = 0;
		for(; i != cleanGames.size(); ++i)
		{
			if( totalSize < matchSize )
			{
				totalSize += cleanGames[i]->Size;
			}
			else
				break;
		}
		cleanGames.resize(i);

		for(; i != cleanGames.size(); ++i)
		{
			DeleteInfo::GetInstance().PushGame(cleanGames[i]->GID, DelLocal | DelRecord);
		}

		record->Release();
	}



	TaskDownloader::TaskDownloader(const TaskItemPtr &taskItem,
		IRTDataSvr *rtDatasvr, ISysOpt *sysOpt, async::thread::AutoEvent &exit, const std::wstring &plRoot)
		: taskItem_(taskItem)
		, rtDataSvr_(rtDatasvr)
		, sysOpt_(sysOpt)
		, exit_(exit)
		, plRoot_(plRoot)
		, isDeleteted_(0)
		, isSuspended_(0)
		, isResume_(0)
		, ok_(false)
		, badSpeedStartTime_(0)
	{
		complate_.Create();
	}

	TaskDownloader::~TaskDownloader()
	{
	}


	void TaskDownloader::Run()
	{
		_RunImpl();
	}
	void TaskDownloader::Stop()
	{

	}

	bool TaskDownloader::_SeedRun()
	{
		taskItem_->SetTaskState(tsWaitSeed);

		if( IsStop(exit_) )
			return false;

		stdex::tString url;
		// 1. ��������url
		Log(LM_DEBUG, _T("1. ��������·��\n"));
		_ConstructURL(url);


		if( IsStop(exit_) )
			return false;

		// 2. ͨ��url��������
		Log(LM_DEBUG, _T("2. ���������ļ� %s\n"), url.c_str());
		size_t bufLen = 0;
		
		http::Buffer seedBuf = _DownloadIndex(url);

		if( IsStop(exit_) )
			return false;

		// 3. ��ѹ�����ļ�
		Log(LM_DEBUG, _T("3. ��ѹ����\n"));
		
		http::Buffer unZipBuf = _UnZipFile(seedBuf);

		if( IsStop(exit_) )
			return false;

		// 4. ����
		Log(LM_DEBUG, _T("4. ���������Ϣ\n"));
		_SaveData(unZipBuf.first.get(), unZipBuf.second);

		return true;
	}


	void TaskDownloader::_ConstructURL(stdex::tString &url)
	{
		url = CW2T(plRoot_.c_str());
		

		// ����URL
		stdex::tStringstream os;
		os << _T("/") 
			<< taskItem_->GetGid() 
			<< _T("/") 
			<< taskItem_->GetGid() 
			<< _T(".i8")
			<< _T("?t=")
			<< _time32(NULL);

		url += os.str();
	}

	bool TaskDownloader::_DownloadCallback()
	{
		return IsStop(exit_);
	}

	http::Buffer TaskDownloader::_DownloadIndex(const stdex::tString &url)
	{
		http::Buffer buf = http::DownloadFile2(url, std::tr1::bind(&TaskDownloader::_DownloadCallback, this));

#ifdef _DEBUG
		stdex::tString path = utility::GetAppPath() + _T("tmp/tmp.zip");
		std::ofstream out(path.c_str(), std::ios::binary | std::ios::out);
		out.write(buf.first.get(), buf.second);
#endif
		return buf;
	}


	http::Buffer TaskDownloader::_UnZipFile(const http::Buffer &inBuf)
	{
		http::Buffer outBuf;
		try
		{
			outBuf = http::UnZip(inBuf);
		}
		catch(std::exception &e)
		{
			std::string error = "��ѹ����ʧ��: ";
			error += e.what();
			throw std::logic_error(error);
		}

		return outBuf;
	}


	void TaskDownloader::_SaveData(const char *data, size_t len)
	{
		// ���������Ϣ
		BSTR seed = ::SysAllocStringByteLen(data, len);
		taskItem_->SetSeed(seed, len);

		// ��������ǿ��ѹ����
		long gid = taskItem_->GetNormalGID();
		if( gid == 0 )
			gid = taskItem_->GetGid();

		if( taskItem_->GetServerPath().empty() )
		{
			stdex::tString gamePath;
			data_helper::GetGamePathFromGid(rtDataSvr_, sysOpt_, taskItem_->GetGid(), gamePath);
			taskItem_->SetServerPath(gamePath);
		}

		stdex::tString gameExeName;
		data_helper::GetExeNameFromGid(rtDataSvr_->GetGameTable(), taskItem_->GetGid(), gameExeName);
		taskItem_->SetExeName(gameExeName);
	}

	bool TaskDownloader::_MscRun()
	{
		if( IsStop(exit_) )
			return false;

		// ��������
		Log(LM_DEBUG, _T("����������������"));
		_BuildMscTask();


		if( IsStop(exit_) )
			return false;

		// ѭ�����״̬
		Log(LM_DEBUG, _T("���������������״̬"));
		_LoopMsc();

		return true;
	}

	void TaskDownloader::_BuildMscTask()
	{
		// ȷ��Ŀ¼����
		stdex::tString savePath = taskItem_->GetServerPath();
		assert(!savePath.empty());
		savePath.erase(savePath.begin() + savePath.find_last_of(_T("\\")), savePath.end());
		if( !::PathFileExists(savePath.c_str()) ) 
		{
			BOOL suc = utility::mkpath(savePath);
			if( !suc )
			{
				std::ostringstream os;
				os << "�����·��������: " << (LPCSTR)CT2A(savePath.c_str());
				throw std::logic_error(os.str().c_str());
			}
		}

		const std::wstring strPathW = CT2W(savePath.c_str());
		wchar_t mdes[MAX_PATH * 3] = {0};
		::wcscpy_s(mdes, strPathW.c_str());

		UINT mode = taskItem_->IsForceRepair() ? (REBUILD_NO_TOPDIR | REBUILD_NO_QUICKCHK) : REBUILD_NO_TOPDIR;
		if( taskItem_->IsForceRepair() )
		{
			const stdex::tString oldIdx = taskItem_->GetServerPath() + taskItem_->GetExeName();
			::DeleteFile(oldIdx.c_str());
		}

		// ��ʱĿ¼�汾
		// ���ص���ʱĿ¼��
		// ��ʱ des Ϊ multi-string����һ��ΪĿ��Ŀ¼���ڶ���Ϊ��ʱĿ¼���м���0��������˫���β��

		// ������ʱĿ¼
		wchar_t tmpdir[MAX_PATH] = {0};
		wchar_t wcsGid[16] = {0};
		_itow_s(taskItem_->GetGid(), wcsGid, 10);

		sysOpt_->GetOpt(OPT_D_TEMPDIR, tmpdir, _T("E:\\msctmp\\"));
		::PathAddBackslash(tmpdir);
		::wcscat_s(tmpdir, wcsGid);

		if( !utility::mkpath(tmpdir) )
		{
			std::ostringstream os;
			os << "����������ʱ·��������: " << CW2A(tmpdir);
			throw std::runtime_error(os.str());
		}

		taskItem_->SetMscTmpDir(tmpdir);


		// ���Ŀ¼��С�������ǿ����Ϸ�������������
		_CheckDiskSpace(tmpdir);

		db::tGame game;
		rtDataSvr_->GetGameTable()->GetData(taskItem_->GetGid(), &game);
		if( !_CheckDiskSpace(mdes, game.Size * 1024LL) && taskItem_->IsPush() )
		{
			Log(LM_WARNING, _T("ǿ����ϷʱӲ�̿ռ䲻��, ��ɾ��������Ϸ, �ɴ˴����Ĳ��������½�."));
			SmartClean(mdes, rtDataSvr_, taskItem_->GetGid());
		}


		::wcscpy(mdes + strPathW.length() + 1, tmpdir);
		mode |= REBUILD_IN_TEMPDIR;

		bool ret = _BuildMscImpl(taskItem_->GetSeed().first, mdes, mode, reinterpret_cast<MSCPROGRESS>(&TaskItem::OnMscProgress));
		if( !ret )
		{
			std::ostringstream os;
			os << "����������������ʧ��: gid = " << taskItem_->GetGid();
			throw std::runtime_error(os.str());
		}

		Log(LM_INFO, _T("����������������ɹ�, GID=%u\n"), taskItem_->GetGid());
	}

	bool TaskDownloader::_BuildMscImpl(BSTR seed, const wchar_t *mdes, UINT mode, MSCPROGRESS progressfn)
	{
		wchar_t taskName[128] = {0};
		bool iRet = msc::MscRebuild(seed, mdes, mode, taskName, progressfn, taskItem_);
		if( !iRet )
		{
			msc::MscDelete(taskItem_);

			std::wstringstream os;
			os << L"msc_rebuildʧ��" << L"Gid = " << taskItem_->GetGid() << L"·�� = " << mdes;

			const std::string error = CW2A(os.str().c_str());
			throw std::runtime_error(error);
		}

		taskItem_->SetTaskName(taskName);

		return iRet;
	}

	void TaskDownloader::_LoopMsc()
	{
		HANDLE handles[] = { exit_, complate_ };
		while(true)
		{
			// ����Ƿ��˳�
			DWORD ret = ::WaitForMultipleObjects(_countof(handles), handles, FALSE, WAIT_TIME);
			if( ret == WAIT_OBJECT_0 || ret == WAIT_OBJECT_0 + 1 )
			{
				if( IsDelete() )
				{
					msc::MscDelete(taskItem_);
				}

				break;
			}

			// ��ͣ����
			if( ::InterlockedExchangeAdd(&isSuspended_, 0) == 1 )
			{
				msc::MscPause(taskItem_);
				::InterlockedExchange(&isSuspended_, 0);
			}

			// �ָ�����
			if( ::InterlockedExchangeAdd(&isResume_, 0) == 1 ) 
			{
				msc::MscResume(taskItem_);
				::InterlockedExchange(&isResume_, 0);
			}

			// ������е���������״̬
			_CheckMscTaskStatus();

			// ȡ�ϴ����ص����ٶ�
			msc::MscSpeed::GetInstance().Update();
		}
	}

	void TaskDownloader::_CheckMscTaskStatus()
	{
		// ������ڼ���򲻼���
		if( !taskItem_->IsCheckCompleted() ) 
		{
			taskItem_->SetTaskState(tsChecking);
			Log(LM_DEBUG, _T("����״̬���δ���, GID = %d"), taskItem_->GetGid());
			return;
		}


		size_t jobCount = 0;
		BSTR tasklist;

		if( msc::MscTaskList(tasklist, jobCount) ) 
		{
			msc::MscDelete(taskItem_);

			std::stringstream os;
			os << "��ȡ�����б�ʧ��!";
			throw std::runtime_error(os.str());
		}

		CComBSTR autoTaskList;
		autoTaskList.Attach(tasklist);

		// �õ������е������б�
		typedef std::vector<std::wstring> JobList;
		typedef JobList::const_iterator JobListIter;
		JobList vJobList(jobCount);
		GetJobList(tasklist, jobCount, vJobList);

		JobListIter iter = std::find(vJobList.begin(), vJobList.end(), taskItem_->GetTaskName());
		if( iter == vJobList.end() )
		{
			msc::MscDelete(taskItem_);

			std::stringstream os;
			os << "msc��û���ҵ���Ӧ������ gid = " << taskItem_->GetGid();
			throw std::runtime_error(os.str());
		}

		MSC_DOWNLOAD_PROGRESS pdp = {0};
		bool ret = msc::MscProgress(taskItem_, &pdp);
		if( !ret ) 
		{
			msc::MscDelete(taskItem_);

			std::stringstream os;
			os << "msc���ȡ����״̬ʧ�� gid = " << taskItem_->GetGid();
			throw std::runtime_error(os.str());
		}

		taskItem_->SetPdp(pdp);

		_CheckSpeed(pdp.TransferRate);

		switch(pdp.State)
		{
		case P2P_JOB_STATE_COMPLETE: 
			{// 3
				// �ύ����
				if( !msc::MscCommitEx(taskItem_, reinterpret_cast<MSCPROGRESS>(&TaskItem::OnMscProgress)) )
				{
					msc::MscDelete(taskItem_);
					throw std::runtime_error("�ύ����ʧ��!");
				}
				else 
				{
					taskItem_->SetTaskState(tsComplete);
					// ���֪ͨ
					complate_.SetEvent();
				}
				break;
			}
		case P2P_JOB_STATE_SUSPENDED: 
			{//2
				taskItem_->SetTaskState(tsSuspend);
				break; 
			}
		case MSC_JOB_STATE_ERROR: 
			{
				std::ostringstream os;
				os << "�������ع�����ʧ��, GID = " << taskItem_->GetGid();
				throw std::runtime_error(os.str());

				break; 
			}
		default: 
			// ������������ػ��Ŷӵ��ļ���ȡ����״̬
			if( pdp.State == P2P_JOB_STATE_QUEUED ) //0
			{
				taskItem_->SetTaskState(tsQueue);
			}
			else 
			{
				taskItem_->SetTaskState(tsDownloading);//1
			}
			break; 
		}
	}

	void TaskDownloader::_CheckSpeed(size_t rate)
	{
		// ��������ٶ�Ϊ0�ҳ���ʱ�䳬��WAIT_BAD_SPEED_TIME
		if( rate == 0 )
		{
			if( badSpeedStartTime_ == 0 )
				badSpeedStartTime_ = ::GetTickCount();

			DWORD curTime = ::GetTickCount();
			if( curTime - badSpeedStartTime_ >= WAIT_BAD_SPEED_TIME )
				throw std::logic_error("�����ٶ�Ϊ0�ҳ����涨ʱ��,��������������");
		}
		else
		{
			badSpeedStartTime_ = 0;
		}
	}


	void TaskDownloader::_RunImpl()
	{
		ok_ = false;

		// 1. ��������/����
		if( !_SeedRun() )
			return;

		// 2. �����ļ�
		if( !_MscRun() )
			return;

		ok_ = true;
	}	
}