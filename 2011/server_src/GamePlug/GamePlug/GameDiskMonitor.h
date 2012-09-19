#ifndef __I8DESK_GAME_DISK_MONITOR_HPP
#define __I8DESK_GAME_DISK_MONITOR_HPP


#include "../../../include/MultiThread/Lock.hpp"
#include "../../../include/MultiThread/Thread.hpp"

namespace i8desk
{
	// ----------------------------------------------
	// class GameDiskMonitor

	// ��Ϸ���̼��
	class GameDiskMonitor
		: public IGameEventHandler
	{
		typedef async::thread::AutoCriticalSection	SCLock;
		typedef async::thread::AutoLock<SCLock>		AutoLock;

	public:
		typedef std::set<TCHAR> DiskPartionType;

	private:
		IRTDataSvr *rtDataSvr_						;
		ISysOpt *sysOpt_							;	// ѡ���

		ulonglong mscSize_							;	// ����������ʱĿ¼

		SCLock mutex_								;	
		async::thread::AutoEvent update_			;		
		async::thread::AutoEvent exit_				;
		async::thread::ThreadImplEx thread_			;

	

	public:
		explicit GameDiskMonitor(IRTDataSvr *pRTDataSvr, ISysOpt *sysOpt);
		~GameDiskMonitor();

	private:
		GameDiskMonitor(const GameDiskMonitor &);
		GameDiskMonitor &operator=(const GameDiskMonitor &);

	public:
		// IGameEventHandler
		virtual uint32 GetEvents();
		virtual void HandleEvent(uint32 optype, uint32 gid, uint64 mask);

		// ����ӿ�
	public:
		void Start();		// ʧ���׳��쳣
		void Stop();

		// ���¶�ȡ�ٶ�
		void Update();

		// ����״̬
		void UpdateStatus();

		// ��ȡ����������ʱĿ¼��С
		ulonglong MscTmpSize() const;

	private:
		bool _Init();
		void _Uninit();

		// ��ȡӲ�̷���
		void _GetPartitions(DiskPartionType &partion);
		// �����������
		void _InsertPartition(TCHAR partition);

		DWORD _Thread();
	};
}




#endif