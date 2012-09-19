#ifndef __BUSINESS_PLUG_HPP
#define __BUSINESS_PLUG_HPP

#include <memory>
#include "I8ExInfoMgrS.h"


namespace engine
{
	class DownloadEngine;
}


namespace i8desk
{
	
	struct ILogger;

	class TaskProductor;

	// -----------------------------
	// class BusinessPlug

	// ������Ĳ��
	class BusinessPlug
		: public ISvrPlug
	{
	private:
		// ��������� 
		ISvrPlugMgr	*plugMgr_;
		// ��־���
		ILogger		*log_;
		// ���ݻ�����
		IRTDataSvr	*rtDataSvr_;
	
		// ��������
		std::auto_ptr<engine::DownloadEngine> engine_;

		// �����Ϸ��չ�Ƿ���Ҫ����
        std::auto_ptr<TaskProductor> checker_;

        //��Ϸ��չ��Ϣ����
        std::auto_ptr<CI8ExInfoMgrS> clExInfoMgr_;

	public:
		BusinessPlug();
		~BusinessPlug();

	private:
		BusinessPlug(const BusinessPlug &);
		BusinessPlug &operator=(const BusinessPlug &);

	public:
		//�ͷŲ��
		virtual void	Release();

		//�õ����������
		virtual LPCTSTR GetPlugName();
		//�õ�����İ汾0xaabbccdd.
		virtual DWORD  	GetVersion();
		//�õ���������Ĺ�˾��
		virtual LPCTSTR GetCompany();
		//�õ������һЩ����
		virtual LPCTSTR GetDescription();

		//��������Ҫ��ܼ���������˿ڣ��������Ҫ�������򷵻�0.
		//������յ��ö˿��¼�ʱ����ص����ýӿڵ�INetLayerEvent��Ӧ���麯��
		virtual DWORD   GetListPort();

		//����ڲ��ĳ�ʼ������,��ISvrPlugMgr����һ����������øú���
		virtual bool	Initialize(ISvrPlugMgr* pPlugMgr);
		//��ISvrPlugMgr�˳�ʱ����ȵ��øú����󣬲ŵ���Release()���ͷŲ����
		virtual bool	UnInitialize();

		//����ܻ��������������ͨ���ú������໥������������Windows����Ϣ����,
		//����cmd�Ĳ�ͬ��param1,parma2ʵ�ʵ������벻ͬ.
		//�����Ҫ�ڲ���ڲ������ڴ淵�ظ������ߡ������ڲ�ͨ��CoTaskMemFree�������ڴ棬
		//������ͨ��CoTaskMemFree���ͷŲ��������ڴ棬��˲���ӿڲ����ṩ�����ڴ�����ͷ��ڴ�.
		virtual DWORD	SendMessage(DWORD cmd, DWORD param1, DWORD param2);


		virtual void OnAccept(i8desk::INetLayer*pNetLayer, SOCKET sck, DWORD param);
		virtual void OnSend(i8desk::INetLayer*pNetLayer, SOCKET sck, LPCSTR lpPackage, DWORD param); 
		virtual void OnRecv(i8desk::INetLayer*pNetLayer, SOCKET sck, LPCSTR lpPackage, DWORD param);
		virtual void OnClose(i8desk::INetLayer*pNetLayer, SOCKET sck, DWORD param);

	private:
		void _AddTask(long type, long gid, long priority);

	};
}


#endif