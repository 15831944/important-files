#ifndef _i8desk_dbengine_h_
#define _i8desk_dbengine_h_

#include <wctype.h>
#include <tchar.h>
#import "c:\\program Files\\Common Files\\System\\ADO\\msado15.dll" no_namespace rename("EOF","adoEOF")

namespace i8desk
{
	//ͳһ�����ݲ����ӿ�.
	struct IDatabase 
	{
		//�ͷŽӿ�
		virtual void Release()			= 0;

		//�����ݿ�
		virtual bool Open(LPCTSTR lpszConnString, LPCTSTR lpszUser = TEXT(""), LPCTSTR lpszPassword = TEXT("")) = 0;

		//�ر����ݿ�
		virtual void Close()			= 0;

		//�õ����ݿ�����������Ϣ
		virtual LPCTSTR GetErrInfo()	= 0;

		//�õ���Ӧ�õĴ������
		virtual long GetErrCode()		= 0;

		//��ס���ݿ����
		virtual void Lock()				= 0;

		//�������ݿ����
		virtual void UnLock()			= 0;

		//���������ʼ���ύ���ع�����
		virtual void BeginTrans()		= 0;
		virtual void CommitTrans()		= 0;
		virtual void RollbackTrans()	= 0;

		//ִ��SQL���.����Ҫ�õ����ؽ��������ǲ����ɾ�����޸ģ�����ͨ���ڶ��������õ�Ӱ����С�
		//�������Ҫ�ڶ���������ֵ���������ÿգ����߲����Ĭ��ֵ��
		virtual bool ExecSql(LPCTSTR lpszSql, PLONG RecordsAffected = NULL) = 0;

		//ִ��SQL���.��Ҫ�õ����صĽ����.���ص��ǣ��ģϵ�Recordset�ӿڽӿ�.����ɹ���Ҫ�Լ�ִ��prcd->Close();
		//ex. 
		//	CAutoLock<IDatabase> lock(m_pDatabase);
		//  _RecordsetPrt prcd;
		//  if (m_pDatabase->ExecSql(lpszSql, prcd))
		//	{
		//		while (prcd->IsEof() == VARIANT_FALSE)
		//		{
		//			//get line value.	
		//		}
		//		prcd->Close();
		//		prcd.Release();	//���Բ���Ҫ����������������ָ����Լ������ͷŽӿڡ�
		//	}
		//	else
		//		OutputDebugString(m_pDatabase->GetErrInfo());
		
		virtual bool ExecSql(LPCTSTR lpszSql, _RecordsetPtr& prcd)			= 0;

		//���ߺ���:ѹ�����ݿ�.ֻ��Ҫû�д�����ʱ����ѹ��.
		virtual bool CompactDatabase(LPCTSTR lpszDbFile) = 0;
	};

	//ϵͳͳһ��ѡ������������Ǵ��������ݿ����һ�����
	struct ISysOpt
	{
		//�ͷŽӿ�
		virtual void	Release()										= 0;

		//09�����ó����ݿ�������10�����ó����ݿ⻺��������ص�ѡ���ָ�롣
		virtual void	SetIDatabase(void* pDatabase)					= 0;

		//�õ�ϵͳѡ��.�������û�����ѡ����Զ����룬��д��Ĭ��ֵ
		virtual bool	GetOpt(LPCTSTR optName, bool defValue = true)	= 0;
		virtual long	GetOpt(LPCTSTR optName, long defValue = 0)		= 0;
		virtual __int64 GetOpt(LPCTSTR optName, __int64 defValue = 0)	= 0;
		virtual void	GetOpt(LPCTSTR optName, LPTSTR lpszValue, LPCTSTR defValue = TEXT("")) = 0;

		//����ϵͳѡ��.�������û�����ѡ����Զ����룬��д�����õ�ֵ
		virtual void	SetOpt(LPCTSTR optName, bool optValue)			= 0;
		virtual void	SetOpt(LPCTSTR optName, long optValue)			= 0;
		virtual void	SetOpt(LPCTSTR optName, __int64 optValue)		= 0;
		virtual void	SetOpt(LPCTSTR optName, LPCTSTR optValue)		= 0;
	};

	//ϵͳͨ��д��־����������������һ��Ҫ�����Լ�����־�ļ������������ļ������ڣ������ļ�����-yyyymmdd.log��
	enum I8_Log_Priority
	{
		LM_SHUTDOWN		= 01,
		LM_TRACE		= 02,
		LM_DEBUG		= 04,			//�������ļ����д����־�ļ���
		LM_INFO			= 010,
		LM_NOTICE		= 020,
		LM_WARNING		= 040,
		LM_STARTUP		= 0100,
		LM_ERROR		= 0200,
		LM_CRITICAL		= 0400,
		LM_ALERT		= 01000,
		LM_EMERGENCY	= 02000,
		LM_MAX			= LM_EMERGENCY,
		LM_ENSURE_32_BITS = 0x7FFFFFFF
	};

	struct ILogger
	{
		virtual void Release()	= 0;

		//������־�ļ���.����Ҫ�ļ���(��Ҫ��·���Լ���չ��).����log,������ɵ��ļ�����\log\log-yyymmdd.log.
		//�ڲ����Զ����ݵ��������������־���������Զ����ļ�������ӵ�������ڣ���������չ��.log,��ͳһ�ŵ�logĿ¼��
		//�����Բ������Ϊ��־�ļ���.���������е���־�ļ��������ظ���Ҳ����鿴
		virtual void SetLogFileName(LPCTSTR lpszLogFile)	= 0;

		//������־�ļ����Ĵ�С��(�ֽ�Ϊ��λ)
		virtual void SetMaxLogSize(DWORD dwMaxSize)			= 0;

		//��ÿ����־ǰ�����־���������
		virtual void SetAddDateBefore(bool bAddDate)		= 0;

		//��ÿ����־�����һ���س����з�
		virtual void SetAddCrLfAfter(bool bAddCrLf)			= 0;

		//���ö���ڲ����ԡ�
		virtual void SetProptery(LPCTSTR lpszLogFile, DWORD dwMaxLogSize, bool bAddDate) = 0;

		//������־���������̨��ip,port.�ڲ�ͨ��udp��������̨��//������
		virtual void SetConsole(DWORD ip, DWORD port)		= 0;

		//�õ����������
		virtual LPCTSTR GetLogFileName()					= 0;
		virtual DWORD	GetMaxLogSize()						= 0;
		virtual bool	GetAddCrLfAfter()					= 0;
		virtual bool	GetAddDateBefore()					= 0;

		//дһ����־������
		virtual void WriteLog(DWORD level, LPCTSTR lpszFormater, ...)		= 0;
		virtual void WriteLog2(DWORD level, LPCTSTR lpszLog, int nLen = -1) = 0;

		//������е���־
		virtual void CleanLog()								= 0;
	};

	BOOL WINAPI CreateDatabase(IDatabase** ppIDatabase);
	BOOL WINAPI CreateSysOpt(ISysOpt** ppISysOpt);
	BOOL WINAPI CreateLogger(ILogger** ppILogger);
}


#endif