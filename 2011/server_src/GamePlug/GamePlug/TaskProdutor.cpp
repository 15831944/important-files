#include "stdafx.h"
#include "TaskProductor.h"

#include "LogHelper.h"
#include "DataSvrHelper.h"

#include "ForceGameZip.h"

namespace i8desk
{

	namespace productor_condition
	{
		// ǿ�������Ĺ�����
		struct ForceFilter : public IGameFilter 
		{
			bool bypass(const db::tGame *const d) 
			{
				// ���İ汾�뱾�ذ汾��ͬ 
				return d->IdcVer == d->SvrVer || d->Force != 1;
			}
		};


		// ���������ȼ������ĵ��������
		struct Sorter : public IGameSorter 
		{
			bool sort(const db::tGame *const d1, const db::tGame *const d2) 
			{
				// ����������ȼ���ͬ��Ƚ����ĵ����
				if( d1->Priority == d2->Priority ) 
				{
					return d1->IdcClick > d2->IdcClick;
				}

				return d1->Priority > d2->Priority;
			}
		};



		// �Զ�������Ϸ�Ĺ�����
		struct AutoUpdateFilter : public IGameFilter 
		{
			bool bypass(const db::tGame *const d) 
			{
				// ������İ汾�뱾�ذ汾��ͬ ��
				// �����Զ����� ��
				// ���Ǳ�����Ϸ
				return d->IdcVer == d->SvrVer
					|| d->AutoUpt != 1 
					|| d->Status != 1;   
			}
		};
	}



	TaskProductor::TaskProductor(IGameTable *gameTable, ISysOpt *sysOpt, UnZipGame *unZipGame, const Callback &callback)
		: gameTable_(gameTable)
		, sysOpt_(sysOpt)
		, unZipGame_(unZipGame)
		, callback_(callback)
	{
		assert(gameTable);
	}

	TaskProductor::~TaskProductor()
	{}


	void TaskProductor::Start()
	{
		wait_.Create();
		exit_.Create();
		
		thread_.RegisterFunc(std::tr1::bind(&TaskProductor::_Thread, this));
		thread_.Start();
	}

	void TaskProductor::Stop()
	{
		exit_.SetEvent();
		thread_.Stop();
		
		Log(LM_DEBUG, _T("TaskProductor �˳��ɹ�"));
	}

	void TaskProductor::ForceCheck()
	{
		wait_.SetEvent();
	}

	DWORD TaskProductor::ForceUpdateGame(long gid, DWORD ip, const db::tGame &game)
	{
		callback_(gid, 0, game.Priority, game.IdcClick, game.IdcVer, 1, 0, ip, tForceTask);

		Log(LM_DEBUG, _T("ͬ��ǿ�Ƹ�����Ϸ.GID = %d   IdcVer = %d  SvrVer = %d\n"),
			game.GID, game.IdcVer, game.SvrVer);

		return 0;
	}

	void TaskProductor::_HasForceZipTask()
	{
		// �õ�ǿ��ѹ����������
		IGameRecordset *pRecordset = 0;
		gameTable_->Select(&pRecordset, 0, 0);

		for(uint32 i = 0; i != pRecordset->GetCount(); ++i) 
		{
			db::tGame *d = pRecordset->GetData(i);
			// PL����Ϊǿ������Ϸ���ڱ���
			if( unZipGame_->IsForceZip(d->GID) )
			{
				long forceGID = unZipGame_->GetForceGID(d->GID);
				if( forceGID != 0 )
				{
					Log(LM_DEBUG, _T("ǿ��ѹ����.GID = %d	IdcVer = %d  SvrVer = %d\n"), d->GID, d->IdcVer, d->SvrVer);
					callback_(forceGID, d->GID, d->Priority, d->IdcClick, d->IdcVer, 0, 1, 0, tForceTask);
				}
			}
		}

		pRecordset->Release();
	}


	void TaskProductor::_HasForceTask()
	{
		//һ.�õ�ǿ�Ƶ�����
		productor_condition::ForceFilter filter;
		productor_condition::Sorter sorter;

		IGameRecordset *pRecordset = 0;
		gameTable_->Select(&pRecordset, &filter, &sorter);


		for(uint32 i = 0; i < pRecordset->GetCount(); ++i) 
		{
			db::tGame *d = pRecordset->GetData(i);

			//if( /* && !unZipGame_->IsForceZip(d->GID) */) 
			{
				Log(LM_DEBUG, _T("ǿ��.GID = %d   IdcVer = %d  SvrVer = %d\n"), d->GID, d->IdcVer, d->SvrVer);

				callback_(d->GID, 0, d->Priority, d->IdcClick, d->IdcVer, 0, 1, 0, tForceTask);
			}
		}

		pRecordset->Release();
	}

	void TaskProductor::_HasTimeUpdateTask()
	{
		// �õ�ʱ�θ�������
		bool bTimeCondition = data_helper::CheckTimeCondition(sysOpt_);
		if( !bTimeCondition )
		{
			Log(LM_INFO, _T("��ǰʱ�β����Զ�����ʱ����"));
			return;
		}

		productor_condition::AutoUpdateFilter filter;
		productor_condition::Sorter sorter;

		IGameRecordset *pRecordset = 0;
		gameTable_->Select(&pRecordset, &filter, &sorter);

		for (uint32 i = 0; i < pRecordset->GetCount(); i++) 
		{
			db::tGame *d = pRecordset->GetData(i);

			Log(LM_DEBUG, _T("�Զ�����.GID = %d   IdcVer = %d  SvrVer = %d\n"), d->GID, d->IdcVer, d->SvrVer);

			/*if( !unZipGame_->IsForceZip(d->GID) )
			{*/
				callback_(d->GID, 0, d->Priority, d->IdcClick, d->IdcVer, 0, 1, 0, d->Repair == 1 ? tForceTask : tTimeTask);
			//}
		}

		pRecordset->Release();

	}

	DWORD TaskProductor::_Thread()
	{
		HANDLE handle[] = { wait_, exit_ };

		while( !thread_.IsAborted() )
		{
			DWORD ret = ::WaitForMultipleObjects(_countof(handle), handle, FALSE, WAIT_TIME);
		
			if( ret == WAIT_OBJECT_0  || ret == WAIT_TIMEOUT )
			{
				// ���ǿ��ѹ��������
				//_HasForceZipTask();

				if( exit_.IsSignalled() )
					break;

				// ���ǿ������
				_HasForceTask();

				if( exit_.IsSignalled() )
					break;

				// ���ʱ�θ�������
				_HasTimeUpdateTask();
			}
			else if( ret == WAIT_OBJECT_0 + 1 )
			{
				break;
			}
			else
			{
				assert(0);
			}
		}

		return 0;
	}

}