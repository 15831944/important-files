#include "stdafx.h"
#include "BootTaskBusiness.h"


#include "../../../../include/Utility/utility.h"
#include "../../../../include/I8Type.hpp"



namespace i8desk
{
	namespace business
	{
		namespace BootTask
		{

			static const struct
			{
				int taskType_;
				const stdex::tString taskTypeDesc_;
			} TaskType[] = 
			{
				{ i8desk::brDeskTop,		_T("�����ͻ�����ֽ") },
				{ i8desk::brShortcut,		_T("���������ݷ�ʽ")},
				{ i8desk::brExecSvrFolder,	_T("�ļ�ִ�е��ͻ���")},
				{ i8desk::brSvrExecFile,	_T("ִ�з������ļ���ű�")},
				{ i8desk::brDelFile,		_T("ɾ��ָ���ļ�")	},
				{ i8desk::brDirectUpdate,	_T("�ͻ�����������")	}
			};



			namespace detail
			{
				using namespace i8desk::data_helper;

				static struct 
				{
					int type;
					LPCTSTR desc;
				}date[] = 
				{
					{ Mon, _T("��һ") },
					{ Tue, _T("�ܶ�") },
					{ Wed, _T("����") },
					{ Thu, _T("����") },
					{ Fri, _T("����") },
					{ Sat, _T("����") },
					{ Sun, _T("����") }
				};
			}

			stdex::tString GetAreaDesc(const data_helper::BootTaskTraits::ValueType &val)
			{
				const data_helper::AreaTraits::MapType &areas = GetDataMgr().GetAreas();
				const data_helper::BootTaskAreaTraits::MapType &bootAreas = GetDataMgr().GetBootTaskAreas();

				stdex::tString areaDesc;
				for(data_helper::BootTaskAreaTraits::MapConstIterator iter = bootAreas.begin();
					iter != bootAreas.end(); ++iter)
				{
					if( utility::Strcmp(val->TID, iter->second->TID) != 0 )
						continue;

					data_helper::AreaTraits::MapConstIterator areaIter = areas.find(iter->second->AID);
					if( areaIter != areas.end() )
					{
						areaDesc += areaIter->second->Name;
						areaDesc += _T("|");
					}
				}

				if( !areaDesc.empty() )
					areaDesc.erase(areaDesc.begin() + areaDesc.find_last_of('|'), areaDesc.end());

				return areaDesc;
			}


			stdex::tString GetRangeDate(const data_helper::BootTaskTraits::ValueType &val)
			{
				stdex::tString text;
				for(size_t i = 0; i != _countof(detail::date); ++i)
				{
					if( val->RunDate & detail::date[i].type )
					{
						text += detail::date[i].desc;
						text += _T(" ");
					}
				}

				if( !text.empty() )
					text.resize(text.length());

				return text;
			}

			// ��ȡִ��ʱ���
			stdex::tString GetRangeTime(const data_helper::BootTaskTraits::ValueType &val)
			{
				CTime startTime(val->StartTime);
				stdex::tString start = (LPCTSTR)startTime.Format(_T("%H:%M:%S"));

				CTime endTime(val->EndTime);
				stdex::tString end = (LPCTSTR)endTime.Format(_T("%H:%M:%S"));

				return start + _T("--") + end; 
			}

			// ��ȡ����ִ������
			stdex::tString GetRunType(const data_helper::BootTaskTraits::ValueType &val)
			{
				stdex::tOstringstream os;
				if( val->RunType == data_helper::Boot )
					os << _T("����ִ��");
				else
					os << _T("�˵�����ִ��");

				os << _T(" �ӳ� ") << val->DelayTime << _T("��");
				return os.str();
			}


			stdex::tString GetTypeDesc(const data_helper::BootTaskTraits::ValueType &val)
			{
				for(size_t i = 0; i != _countof(TaskType); ++i)
				{
					if( TaskType[i].taskType_ == val->Type )
						return TaskType[i].taskTypeDesc_;
				}

				//assert(0);
				return _T("");
			}


			void TypeDesc(const TypeDescCallback &descCallback, const TypeDataCallback &dataCallback)
			{
				for(size_t i = 0; i != _countof(TaskType); ++i)
				{
					descCallback(TaskType[i].taskTypeDesc_.c_str());
					dataCallback(i, TaskType[i].taskType_);
				}
			}


			bool HasSameName(const data_helper::BootTaskTraits::ValueType &val)
			{
				using i8desk::data_helper::BootTaskTraits;
				const BootTaskTraits::MapType &bootTasks = i8desk::GetDataMgr().GetBootTasks();

				for(BootTaskTraits::MapConstIterator iter = bootTasks.begin(); iter != bootTasks.end(); ++iter)
				{
					if( utility::Strcmp(iter->second->TID, val->TID) == 0 )
						continue;
					if( utility::Strcmp(iter->second->Name, val->Name) == 0 )
						return true;
				}

				return false;
			}

			void GetImageFileName( std::vector<stdex::tString> &curfiles )
			{
				const stdex::tString WallPaperPath = _T("Data\\WallPaper");
				std::vector<stdex::tString> files;

				if( i8desk::GetControlMgr().GetFileOrDir(WallPaperPath, i8desk::data_helper::GET_FILELIST, false, files) )
				{
					for(std::vector<stdex::tString>::const_iterator iter = files.begin(); 
						iter != files.end(); ++iter)
					{
						CPath path(iter->c_str());
						if( IsImage(path.GetExtension() ) )
							curfiles.push_back(iter->c_str());
					}
				}

			}

			stdex::tString Imagesformat[] = 
			{
				_T("bmp"),
				_T("jpg"),
				_T("jpeg"),
				_T("gif"),
				_T("png")
			};

			bool IsImage(const CString &ext)
			{
				for(size_t i = 0; i != _countof(Imagesformat); ++i)
				{
					CString lpExt = ext.Mid(1);
					if( utility::Stricmp(lpExt, Imagesformat[i].c_str()) == 0 )
					{
						return true;
					}
				}	

				return false;
			}


			void GetRunDate(const std::tr1::function<void(int, LPCTSTR)> &callback)
			{
				for(size_t i = 0; i != _countof(detail::date); ++i)
					callback(detail::date[i].type, detail::date[i].desc);
			}


			void GetCheckDate(const std::tr1::function<void(int)> &callback)
			{
				for(size_t i = 0; i != _countof(detail::date); ++i)
					callback(detail::date[i].type);
			}

			bool IsRunAtBoot(const data_helper::BootTaskTraits::ValueType &val)
			{
				if( val->RunType == data_helper::Boot )
					return true;
				else
					return false;
			}

			int SetRunType(bool isRunBoot)
			{
				return isRunBoot ? data_helper::Boot : data_helper::Menu;
			}
			
		}
	}
}