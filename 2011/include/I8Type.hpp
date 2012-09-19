#ifndef __I8_TYPE_HPP
#define __I8_TYPE_HPP



namespace i8desk
{

	//�ϴ���������
	enum UpLoadPacketType 
	{
		uptFirst,
		uptMiddle,
		uptLast,
		upOnlyOne
	};

	//�����̵�����
	enum VDiskType
	{
		VDISK_TYPE_I8DESK				=	0,			//��ʾI8Desk������
		VDISK_TYPE_OTHER				=	1			//������������,���ѷ������̷�ӳ��ɵ��ͻ������̷�.
	};


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

	//�õ��̷���Ŀ¼�����ļ��б�
	enum GetFileOrDirType
	{
		GET_DRVLIST,		
		GET_DIRLIST,		
		GET_FILELIST	
	};

	// ֪ͨ����
	enum TaskNotifyType
	{
		GamePlug,
		PlugPlug
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

	// ͬ������
	enum emSyncType
	{
		SYNC_UNKNOWN = 0,	// δ����
		SYNC_LOCAL,			// ��ͬ�����ظ�����Դ
		SYNC_VDISK,			// ��ͬ����������Դ
		SYNC_CUSTOM,		// �Զ���ͬ��
		SYNC_ALL,			// ͬ��������Դ
		SYNC_SERVER			// ͬ�����������
	};

	// ����ƽ��
	enum emBalanceType
	{
		BALANCE_UNKNOWN = 0,	// δ֪
		BALANCE_POLL,			// ��ѯ
		BALANCE_AREAPRIORITY,	// ��������
		BALANCE_DYNAMIC			// ��̬
	};

	// ����ģʽ
	enum FC_COPY_MODE
	{
		FC_COPY_COMPARE = 0,
		FC_COPY_QUICK	= 1,  // �Ա��ļ�
		FC_COPY_FORE	= 2,  // ���Ա�ȫ������
		FC_COPY_VERSION = 3   // �Ա������汾��
	};

	// ���Ͳ������ø�ʽ
	enum PUSH_PARAM_FORMAT
	{
		fst_maxspeed	= 1,	// ����ٶ�
		scd_cheecktype	= 2,	// �Աȷ�ʽ
		trd_gid			= 3		// ������Ϸ��GID
	};

	// ��������
	enum BootRunTask 
	{  
		brDeskTop		= 0,		// ������
		brShortcut		= 1,		// �����ݷ�ʽ
		brIEHomePage	= 2,		// IE��ҳ����
		brCliExecFile	= 3,		// ִ�пͻ�����һ�Զ����EXE
		brSvrExecFile	= 4,		// ���������·ŵ������ļ�
		brDelFile		= 5,		// ɾ���ļ����ļ��л�ĳһ��Ϸ
		brDelGames		= 6,		// ɾ����Ϸ
		brSalfCenterXMl = 7,		// ����ȫ����XML
		brUpdateGame	= 8,		// ������Ϸ
		brDirectUpdate  = 9,		// �ͻ�����������
		brExecSvrFolder = 10,    	// ���Ʒ�����ļ���/ִ���ļ����ڳ���

        //�ͻ����ӿ�������(�ɿ����������ɶ����ӿ�������)
        brAtom_DownloadFile,       // �����ļ�
        brAtom_DeskTop,            // ������(ʹ�ñ���ͼƬ)
	};


	// �Ƿ�Ϊ������Ϸ
	enum LocalGame
	{
		StatusNone	= 0,			// ���ڱ���
		StatusLocal					// �ڱ���
	};


	// ��Ϸ�������ȼ�
	enum DownloadPriority
	{
		Lowest = 0,					// ���
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

	// �ͻ������ӷ�����IP
	enum ClientConnectSvr
	{
		UpdateIP = 0,				// ��������IP����
		VDiskIP						// ������IP����
	};

	//�����̵��������ͣ����ͻ���ˢ�̵�ʱ����
	enum VDiskRefreshType 
	{
		VDISK_RT_Boot					=	0,			/*����*/
		VDISK_RT_RunMenu				=	1,			/*���˵�*/
		VDISK_RT_RunGame				=	2			/*����Ϸ*/
	};

	//��Ϸ�����з�ʽ
	enum GameRunType
	{
		GAME_RT_NONE					=	0,			//δ����
		GAME_RT_LOCAL					=	1,			//���ظ���
		GAME_RT_VDISK					=	2,			//������.(���һ��ָ�����Ǹ�����������)
		GAME_RT_DIRECT					=	3			//ֱ������(������ֱ�Ӵӿͻ���������,��Ҫ����Ե�����������)
	};

	//�ͻ��˶�������	//for packageheader.resv[0]
	enum OBJECT_TYPE
	{
		OBJECT_UNKOWN					=	0,
		OBJECT_I8DESKCLISVR				=	1,
		OBJECT_CONSOLE					=	2,
		OBJECT_VDISKSVR					=	3,
		OBJECT_BARONLINE				=	4,
		OBJECT_NODESERVER				=	5
	};


	//�ͻ��˿�������
	enum ClientCtrlCmd
	{
		Ctrl_InstallProt				=	0,	//��װ��ԭ��info:�����и�dword��ʾ�Ƿ񱣻����з���.Ϊ����ʾ������Ϊ����ʾ������
		Ctrl_RemoveProt					=	1,	//ɾ����ԭ��info:��
		Ctrl_ProtArea					=	2,	//������ԭ����, info:������String,��һ����ʾ�����ķ����б��ڶ�����ʾȡ�������ķ����б�
		Ctrl_ShutDown					=	3,	//������������info:��1��dword��ʾ��Ϊ1��ʾ������Ϊ0��ʾ�ػ�
		Ctrl_ExecFile					=	4,	//ִ��ָ���ļ���info:������һ��String��ʾ��Ҫ���е��ļ�.
		Ctrl_ViewSysInfo				=	5,	//��ȡϵͳ��Ϣ��info:��
		Ctrl_ViewProcInfo				=	6,	//��ȡ������Ϣ��info:��
		Ctrl_ViewSvrInfo				=	7,	//��ȡ������Ϣ��info:��
		Ctrl_KillProcSvr				=	8,	//kill���̻��߷���info:һ��DWORD(0��ʾ�Ƿ���1��ʾ�ǽ���),һ��String��ʾ�Ľ��̻��߷�����
		Ctrl_Remote						=	9,	//�ͻ���Զ�̿����������رգ�info:�ø�dword��ʾ��Ϊ����ʾ������Ϊ����ʾ�ر� 
		Ctrl_Chkdsk						=	10,	//�ͻ����޸�����
		Ctrl_PushGameAtOnce				=	11,	//ʵʱ������Ϸ 

		Ctrl_EnableSC					=	100,  //���ð�ȫ����
		Ctrl_EnableIEProt				=	101,  //����IE����
		Ctrl_EnableDogProt				=	102  //���÷�������
	};

	// ��ȡ�����������
	enum RtStatusCmd
	{
		UP_SPEED						= 0x10,	// �������ٶ� 
		DOWN_SPEED						,		// �������ٶ�
		DOWNLOAD_STATUS					,		// ������Ϣ
		UPDATE_DISK						,		// ������Ϸ����Ϣ
		PL_VERSION						,		// PL�汾
		DELETE_FILE						,		// ���������ʱ�ļ�
		GAMEEX_VERSION					,		// �õ���Ϸ��չ�汾
		SMART_CLEAN						,		// ����ɾ��
		MSC_TMP_SIZE					,		// ����������ʱĿ¼��С
		CLEINT_DELETE_GAME				,		// �ͻ������ִ��ɾ����Ϸ�ļ�
		CON_SAVE_DATA
	};

	// CmdType
	enum CmdType
	{	
		CMD_PLUG_TOOL					= 0x333	// ���֪ͨ
	};

	// GameMgrɾ������
	enum DelOperation 
	{
		DelNone			= 0,					// ����ɾ������
		DelRecord		= 1,					// ֻɾ�����ݿ��¼
		DelLocal		= 2,					// ֻɾ���������ļ�	
		DelSync			= 4,					// ֻ֪ͨͬ��ɾ��
		DelClient		= 8,					// ֻɾ���ͻ����ļ�
		DelLock			= 16,					// ͣ����Ϸ
		DelTmp			= 32,					// ɾ����ʱĿ¼
		DelIdc			= 64,					// ɾ����¼
		DelAll			= DelIdc | DelLocal | DelSync | DelClient, // ɾ����������

	};


	// ͼ�����
	enum IconOperation 
	{
		ioAdd,									// ����	
		ioDel,									// ɾ��
		ioGet									// �޸�
	};



	// ��������־
	enum emServerType
	{
		OtherServer	= 0,					// �ӷ���
		MainServer		= 1					// ������
	};

	// ��չ��Ϣ����
	enum ExInfo_Type_en
	{
		E_EXINFO_GAME = 1,						//��Ϸ��չ��Ϣ
		E_EXINFO_MENU,                          //�˵��ּ���Ϣ
	};


	// ͬ���������
	enum SyncOperate
	{
		Driver = 1,								// ����
		Pause,									// ��ͣ
		Resume									// �ָ�
	};
	
	// ��ȫ��������
	enum SafeCenterType
	{
		UNKOWN	= 0,							// δ֪
		DISKLESS= 1,						// ���̰�ȫ����
		KONGHE	= 2								// ���̰�ȫ����
	};

	// ��ֹ��������
	enum ForbidType
	{
		ForbidExe	= 1,							// ��ֹ���е�Exe
		ForbidWnd	= 2,							// ��ֹ���еĴ���
	};

	// ��Ϸ�Ƿ�����
	enum HideType
	{
		NoHide	= 0,							// ��Ϸ������
		Hide	= 1,							// ��Ϸ����
	};

	// �������з�ʽ
	enum GongGaoRunType
	{
		Pic		= 0,							// ������ʾͼƬ
		Text	= 1,							// ������ʾ����
		All		= 2,							// ���漴��ʾ���֣�����ʾͼƬ	
	};

	// ͬ����������
	enum SyncType
	{
		Class	= 0,							// �����ͬ��
		Game	= 1								// ����Ϸͬ��
	};

    //ͬ������״̬
    enum SyncTaskState
    {
        TaskStarted = 1,
        TaskStopped,
        TaskPaused,
        TaskResumed
    };

	// ͬ����Ϸ״̬
	enum SyncGameState
	{
		GameComplate = 0,							// ���
		GameUnComplate,								// δ���
		GamePaused,									// ��ͣ
		GameError,									// ����
		GameRunning,								// ������
	};

	// ����״��
	enum NetType
	{
		other = 1,							// ����
		adsl,								// ADSL
		opticalfiber						// ����
	};

	// ����״��
	enum DelClientGameOp
	{
		Add = 0,							// ���
		Del,								// ɾ��
		Find								// ����
	};
}






#endif