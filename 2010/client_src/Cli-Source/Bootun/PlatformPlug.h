#pragma once

#include "UpdateGameCli.h"
#include <string>
#include <vector>
using namespace std;
namespace i8desk
{

#define       PLATFORMPLUG_CONFIG_FILENAME               TEXT("plugin_config.xml") //��������ļ���


	//�����Ϣ
	typedef struct tagSTPlugInfo
	{
		DWORD                    dwGameId;                   //���ID
		DWORD                    dwRunType;                  //������з�ʽ
		BOOL                     bEnable;                    //�Ƿ�����
		char                     szServerDir[MAX_PATH];      //�����Ŀ¼
		char                     szClientDir[MAX_PATH];      //�ͻ���Ŀ¼
		char                     szExeName[MAX_PATH];        //�ͻ���ִ���ļ�
		char                     szExeParam[MAX_PATH];       //ִ�в���

		tagSTPlugInfo()
		{
			ZeroMemory(this, sizeof(tagSTPlugInfo));			
		}
	}STPlugInfo;

	//ƽ̨�����
	class CPlatformPlug
	{
		//��������
	public:
		CPlatformPlug(void);
		virtual ~CPlatformPlug(void);

	public:
		//��ʼ����
		BOOL                     Start(ILogger* pLogger, IPlugMgr* pPlugMgr, HANDLE hExit, CHyOperator* pRestore);

		//�����߳�
	public:
		UINT                     WorkThread();
		static UINT __stdcall    _WorkThread(PVOID lpVoid);

	private:
		//��������
		BOOL                     DownloadConfig();
		//��������
		BOOL                     ParserConfig();
		//���пͻ���
		BOOL                     ExecClient(STPlugInfo stPlugInfo);
		//�����ļ��Ƿ���Ҫ����
		BOOL                     FileIsNeedUpdate(DWORD dwProgramType, DWORD dwPathType, LPSTR lpRemoteFileName, LPSTR lpLocalFilePath = NULL);
		//�����ļ�
		BOOL                     DownloadFile( DWORD dwProgramType, DWORD dwPathType, string strRemoteFileName, char** pRecvBuffer, DWORD &dwRecvLen);
		//����������Ϣ��������Ϸ���ݣ������̣�ϵͳ����,�ղؼеȷ�������ݣ�
		void                     WriteDataFile(string FileName, char* data,bool bInprotect, DWORD datalength = 0);	
		//�����ļ�CRC
		DWORD	                 GetFileCRC32(const std::string&  szFile);
		//ɾ��Ŀ¼����͸��ԭ��
		BOOL                     DeleteDirectory(char *pszDir);
		//���н���
		BOOL                     RunProcess(LPCSTR lpImage,LPCSTR lpPara);
		BOOL                     GetTokenByName(HANDLE &hToken,LPSTR lpName);

		//�������º���ָ��
	private:
		FASTCOPY_START           FastCopy_Start;
		FASTCOPY_END             FastCopy_End;
		FASTCOPY_GETSPEEDEX      FastCopy_GetSpeedEx;

	private:
		//��ǰĿ¼
		string                   m_strCurrentDir;
		//������IP
		string                   m_strMajorSvrIp;
		//�ӷ���IP
		vector<string>           m_strSubSvrIp;
		//��־���
		ILogger                 *m_pLogger;
		//���������
		IPlugMgr                *m_pPlugMgr;
		//���
		vector<tagSTPlugInfo>    m_vtPlugInfo;
		//��ԭ�ӿ�
		CHyOperator             *m_pRestore;
		//�˳��¼�
		HANDLE                   m_hExit;
		//�߳�
		HANDLE                   m_hWorkThread;
		//����ģ��
		HMODULE                  m_hUpdateModule;
	};


}








