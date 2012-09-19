#ifndef __CUSTOM_DATA_TYPE_HPP
#define __CUSTOM_DATA_TYPE_HPP

#include "../../../../include/tablestruct.h"
#include "../../../../include/Utility/SmartHandle.hpp"
#include <vector>
#include <array>
#include <functional>

namespace i8desk
{
	namespace data_helper
	{
		const stdex::tString RT_UNKNOWN = _T("δ����");
		const stdex::tString RT_LOCAL	= _T("���ظ���");
		const stdex::tString RT_VDISK	= _T("������");
		const stdex::tString RT_DIRECT	= _T("������,ֱ������");


		// �����̿�ʼ����
		enum VDStartType 
		{
			VD_BOOT	=	0,			/*����*/
			VD_STARTMENU,			/*���˵�*/
			VD_STARTGAME,			/*����Ϸ*/
		};


		// �ļ�·��������
		enum FPType 
		{
			FP_ABSPATH,				/*����·��*/
			FP_REALPATH,			/*���·��*/
		};

		enum FType 
		{
			fFile,
			fDir
		};


		// �ϴ���������
		enum UpLoadPacketType 
		{
			uptFirst,
			uptMiddle,
			uptLast,
			upOnlyOne
		};

		//�õ��̷���Ŀ¼�����ļ��б�
		enum GetFileOrDirType
		{
			 GET_DRVLIST,		
			 GET_DIRLIST,		
			 GET_FILELIST	
		};


		// ��������֪ͨ
		enum TaskNotify 
		{
			TASK_COMPLATE,
			TASK_DOWNLOADFAILED,
			TASK_CHECHFAILED,
			TASK_STOPCOMPLATE
		}; 

		// ���з�ʽ
		enum emRunType
		{
			ERT_NONE = 0,		// δ����
			ERT_LOCAL,			// ���ظ���
			ERT_VDISK,			// ������
			ERT_DIRECT,			// ֱ�����У�������ֱ�Ӵӿͻ��������У�
		};


		// ����ƽ��
		enum emBalanceType
		{
			BALANCE_UNKNOWN = 0,	// δ֪
			BALANCE_POLL,		// ��ѯ����
			BALANCE_AREAPRIORITY,	// ��������
			BALANCE_DYNAMIC,		// ��̬
		};

		// ����ģʽ
		enum FC_COPY_MODE
		{
			FC_COPY_COMPARE = 0,
			FC_COPY_QUICK	= 1,  // �Ա��ļ�
			FC_COPY_FORE	= 2,  // ���Ա� ȫ������
			FC_COPY_VERSION = 3   // �Ա������汾��
		};

		enum E_CliCtrlCmd
		{
			Ctrl_InstallProt	= 0,	//��װ��ԭ��info:�����и�dword��ʾ�Ƿ񱣻����з���.Ϊ����ʾ������Ϊ����ʾ������
			Ctrl_RemoveProt		= 1,	//ɾ����ԭ��info:��
			Ctrl_ProtArea		= 2,	//������ԭ����, info:������String,��һ����ʾ�����ķ����б��ڶ�����ʾȡ�������ķ����б�
			Ctrl_ShutDown		= 3,	//������������info:��1��dword��ʾ��Ϊ1��ʾ������Ϊ0��ʾ�ػ�
			Ctrl_ExecFile		= 4,	//ִ��ָ���ļ���info:������һ��String��ʾ��Ҫ���е��ļ�.
			Ctrl_ViewSysInfo	= 5,	//��ȡϵͳ��Ϣ��info:��
			Ctrl_ViewProcInfo	= 6,	//��ȡ������Ϣ��info:��
			Ctrl_ViewSvrInfo	= 7,	//��ȡ������Ϣ��info:��
			Ctrl_KillProcSvr	= 8,	//kill���̻��߷���info:һ��DWORD(0��ʾ�Ƿ���1��ʾ�ǽ���),һ��String��ʾ�Ľ��̻��߷�����
			Ctrl_Remote         = 9,	//�ͻ���Զ�̿����������رգ�info:�ø�dword��ʾ��Ϊ����ʾ������Ϊ����ʾ�ر� 
			Ctrl_Chkdsk         = 10,	//�ͻ����޸�����
			Ctrl_PushGameAtOnce = 11,	//ʵʱ������Ϸ 

			Ctrl_EnableSC       = 100,  //���ð�ȫ����
			Ctrl_EnableIEProt   = 101,  //����IE����
			Ctrl_EnableDogProt  = 102   //���÷�������
		};

		// �Ƿ�Ϊ������Ϸ
		enum LocalGame
		{
			StatusNone	= 0,			// ���ڱ���
			StatusLocal					// �ڱ���
		};


		// ����������
		enum VDiskType
		{
			I8VDisk = 0,				// I8������
			OtherVDisk					// ������������
		};


		// ��Ϸ�������ȼ�
		enum DownloadPriority
		{
			Lowest = 1,					// ���
			Lower,						// �ϵ�
			Normal,						// ����
			Higher,						// �ϸ�
			Highest						// ���
		};

		// �ͻ�������
		enum ClientStatus
		{
			Offline = 0,				// ����
			Online						// ����
		};


		// ��������ִ������
		enum StartupRunDate
		{
			Mon	= 1,							// ����һ
			Tue	= 2	<< 0,						// ���ڶ�
			Wed	= 2	<< 1,						// ������
			Thu	= 2	<< 2,						// ������
			Fri = 2	<< 3,						// ������
			Sat	= 2	<< 4,						// ������
			Sun	= 2	<< 5						// ������
		};

		// ��������ִ�з�ʽ
		enum StartupRunType
		{
			Boot,						// ��������
			Menu						// �˵�����
		};

	}


	


	namespace db
	{
		// ---------------------------------

		struct tClientStatus
			: public tClient
		{};
		typedef std::tr1::shared_ptr<tClientStatus> TClientStatusPtr;


		struct tPushGame
			: public tCmpBootTask
		{};
		typedef std::tr1::shared_ptr<tPushGame> TPushGamePtr;

		struct tCustomRunType
			: public tRunType
		{
			stdex::tString Name;
		};
		typedef std::tr1::shared_ptr<tCustomRunType>	TCustomRunTypePtr;

		struct tCustomGame
			: public tGame
		{
			utility::ICONPtr Icon;
			std::vector<TCustomRunTypePtr> Runtypes;
			stdex::tString RuntypeDesc;
			stdex::tString StatusDesc;
			stdex::tString GIDDesc;
		};
		typedef std::tr1::shared_ptr<tCustomGame>		TCustomGamePtr;

		struct tCustomClass
			: public tClass
		{
			utility::BITMAPPtr Icon;
			utility::BITMAPPtr Thumbnail;
			size_t ImgIndex;

			tCustomClass()
				: ImgIndex(0)
			{}
		};
		typedef std::tr1::shared_ptr<tCustomClass>		TCustomClassPtr;


		struct tCustomPlugTool
			: public tPlugTool
		{
			utility::ICONPtr Icon;
			std::tr1::array<utility::BITMAPPtr, 4> StatusBmp;
			utility::BITMAPPtr rateBmp;

		};
		typedef std::tr1::shared_ptr<tCustomPlugTool>	TCustomPlugToolPtr;


		// ͳ����Ϣ
		struct tCustomStatics
		{
			ulong IdcCount;
			unsigned long long IdcSize;
			ulong LocalCount;
			unsigned long long LocalSize;
		
			ulong OnlineClients;
			ulong TotalClients;

			DWORD LogState;

			tCustomStatics()
			{
				memset(this, 0, sizeof(*this));
			}
		};
		typedef std::tr1::shared_ptr<tCustomStatics> TCustomStaticsPtr;


		// �����ҳ���ݽṹ
		struct tCustomMonitor
		{
			struct tServer
			{
				TCHAR SvrName[MAX_NAME_LEN];
				int   SvrType;
				DWORD Status;
				ulong ClientConnects;
				ulong Connects;
				ulong TotalSpeed;
				uint64 TotalReadData; 

				tServer()
				{
					memset(this, 0, sizeof(*this));
				}
			};
			typedef std::tr1::shared_ptr<tServer> tServerPtr;
			std::vector<tServerPtr> ServersInfo;


			struct tDownloadRes
			{
				ulong Status;
				ulong DownlaodingCount;
				ulong TotalSpeed;
				ulong QueueCount;
				ushort TotalConnect;
				ulonglong TmpSize;
				long LimitSpeed;
				ulong CPUUsage;

				tDownloadRes()
				{
					memset(this, 0, sizeof(*this));
				}
			};
			tDownloadRes DownloadResInfo;

			struct tUpdate
			{
				ulong TotalClients;
				ulong TotalSpeed;

				tUpdate()
				{
					memset(this, 0, sizeof(*this));
				}
			};
			tUpdate UpdateInfo;

			struct tSyncTask
			{
				ulong TotalClients;
				ulong TotalSpeed;

				tSyncTask()
				{
					memset(this, 0, sizeof(*this));
				}
			};
			tSyncTask SyncTaskInfo;
		};
		typedef std::tr1::shared_ptr<tCustomMonitor> TCustomMonitorPtr;


		// Area����
		struct AreaLess
			: std::less<stdex::tString>
		{
			bool operator()(const stdex::tString &lhs, const stdex::tString &rhs) const
			{
				return lhs < rhs;
			}
		};
	}
}





#endif