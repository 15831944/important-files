#ifndef __i8desk_logrpt_inc__
#define __i8desk_logrpt_inc__

#include "../../include/frame.h"
#include "../../include/Zip/XZip.h"

#include <vector>

namespace i8desk
{
	class tagUserInfo
	{
	public:
		//in param.
		DWORD	dwCpuID;				//Ӳ��ID
		stdex::tString szUser;			//�û���
		stdex::tString szPassword;		//����
		stdex::tString oau1;			//OAU1
		stdex::tString oau2;			//OAU2
		stdex::tString szSrvMac;		//������MAC��ַ
		stdex::tString szSrvVersion;	//����������汾

		//out param.
		DWORD   dwResCode;				//��ʾ�û���֤���ص�flagֵ
		DWORD   dwNibID;				//����nid		
		DWORD	dwSID;					//���ɷ�����sid
		DWORD	dwRID;					//�û�����rid
		DWORD	dwYear;					//�û�����������
		DWORD	dwMonth;				//�û�����������
		DWORD	dwDay;					//�û���������
		bool    dwUploadLog;			//�Ƿ��ϴ���־
		stdex::tString szNbName;		//��������:��ʾ���˵����ɵ�ַ�ĵ�һ��
		stdex::tString szNbProvince;	//��������ʡ
		stdex::tString szNbCity;		//����������
		stdex::tString szNbRealityUrl;	//����ʵ����Ϣ�޸���ַ
		stdex::tString szNbAddress;		//���ɵ�ַ����ʵ�����ɵ�ַ
		stdex::tString szNbPhone;		//���ɵ绰��������
		stdex::tString szNbMobile;		//�����ƶ��绰���ֻ���
		stdex::tString szNbTitle;		//��ʾ���˵��������Ƶĵڶ��С�
		stdex::tString szNbSubTitle;	//��ʾ���˵��������Ƶĵ�����
		stdex::tString szNbTitleUrl;	//������ҳ�������˵����ɵ�ַ�󣬵������url.���Ϊ�գ�������������ƺ���ʾ����
		DWORD	dwConShowDialog;		//�����·�������̨����Ϣ:�Ƿ񵯳��Ի���(1|0)
		DWORD   dwConShowCancel;		//�����·�������̨����Ϣ:�Ƿ���ʾȡ����ť
		stdex::tString szConMessage;	//�����·�������̨����Ϣ:��Ϣ����
		stdex::tString szConOkUrl;		//�����·�������̨����Ϣ:��ȷ���󵯳�����ַ
		stdex::tString szOemID;			//����id.
		stdex::tString szOemName;		//��������
		stdex::tString szUserType;		//�û�����
		stdex::tString szMessage;		//���ĸ��û���ʾ��Ϣ
		stdex::tString szPlugParam;		//ע�����Ĳ�����Ϣ
		stdex::tString szTaskInfo;		//��¼�����������Ϣ
		stdex::tString szError;			//���صĴ�����Ϣ(��flag������1ʱ)
		stdex::tString szMenuGGao;		//�˵����浯������.p1=-1|0|1(��ʾ����������|ǿ�ƹ�|ǿ�ƿ�),p2=n����
		stdex::tString szMenuPop;		//�˵����½ǹ�浯������.p1=0|1(��ʾ��|��),p2=n����
		stdex::tString szBotLayer;		//�˵��ײ����
		stdex::tString szMenuPage;		//�˵�Ĭ��ҳ
		stdex::tString szUrlNav;		//��ַ�����б�
		stdex::tString szVdMus;			//��Ƶ�����б�
		stdex::tString szDotCard;		//�㿨�̳ǵ�ַ
		stdex::tString szGameRoomUrl;	//��Ϸ����������ַ
		stdex::tString szPersonUrl;		//�˵������û�������ַ

		stdex::tString szNic;			// ��������
		int uAdslSpeed;					// ADSL Speed 0�ǲ��ϴ���-1�ǲ����ƣ������������ٶ�
	
		int createDay;					// ���ɴ���������
		int diskType;					// �������� 1:���� 2:���� 3:���
		stdex::tString diskName;		// ���̲�Ʒ����
		stdex::tString feeName;			// �շѲ�Ʒ����
		stdex::tString culturalName;	// ��ȫ����������
		int broadBandType;				// ����״��1:���� 2:ADSL 3:����
		int reality;					// �Ƿ���ͨ��ʵ�� 1:�� 0:��


		tagUserInfo()
		{
			dwCpuID = 0;
			dwResCode = 0;
			dwNibID	= 0;
			dwSID	= 0;
			dwRID	= 0;
			dwYear  = 0;
			dwMonth	= 0;
			dwDay	= 0;
			dwUploadLog = false;
			dwConShowDialog = 0;
			dwConShowCancel = 0;
			uAdslSpeed = 0;
			createDay = 0;
			diskType = 0;
			broadBandType = 0;
			reality = 0;
		}
	};

	stdex::tString uri_encode(stdex::tString& source);
	inline  stdex::tString uri_encode(LPCTSTR source) { return uri_encode(stdex::tString(source)); }
	void	GetSvrMacAddr(tagUserInfo* pUserInfo);
	stdex::tString GetFileVersion(IN LPCTSTR pFileName);
	stdex::tString GetAppPath();
	void	splitString(const stdex::tString &strSource, std::vector<stdex::tString>& plugs, TCHAR ch);
	int		GetOemId();
	DWORD	IsSystemType();
	DWORD	CheckProcess(LPCTSTR lpszProcName);
	stdex::tString handleStr(stdex::tString &src);
	inline  stdex::tString handleStr(LPCTSTR src) { return handleStr(stdex::tString(src)); }
	stdex::tString GetServerDeviceInfo(tagUserInfo* pUserInfo);
	stdex::tString GetNodeSvrDeviceInfo(ISvrPlugMgr* pPlugMgr);
	void	UpLoadLog(tagUserInfo* pUserInfo, HANDLE hExited);
	void	DeleteMoreLogFile(HANDLE m_hExit);
};

#endif