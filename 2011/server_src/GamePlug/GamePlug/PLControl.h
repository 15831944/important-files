#ifndef __I8DESK_PL_CONTROL_HPP
#define __I8DESK_PL_CONTROL_HPP


#include "../../../include/Utility/utility.h"
#include "../../../include/MultiThread/Lock.hpp"
#include "../../../include/MultiThread/Thread.hpp"
#include "../../../include/Utility/SmartPtr.hpp"
#include "../../../include/Http/HttpHelper.h"

#include "plparser.h"

namespace i8desk
{

	// -------------------------------------
	// class PLControl

	// PL ����
	class PLControl
	{
		typedef PLParser::PLComplate				PLComplate;
		typedef async::thread::AutoCriticalSection	SCLock;
		typedef async::thread::AutoLock<SCLock>		AutoLock;

		typedef std::tr1::function<void()>			Callback;
		typedef std::vector<Callback>				Callbacks;

		// ��ʱ����PL�ļ��
		static const size_t REFRESH_PL_INTERVAL = 1000 * 60 * 10;

	private:
		IRTDataSvr		*pRTDataSvr_;
		ISysOpt			*pSysOpt_;

		SCLock			mutex_;		
		async::thread::AutoEvent		exitEvent_;			// �˳��¼�
		async::thread::AutoEvent		refreshEvent_;		// ˢ���¼�
		async::thread::ThreadImplEx		thread_;

		std::auto_ptr<PLParser>			plHandler_;			// PL������
		ISAXXMLReaderPtr				rdr_;							
		
		Callbacks						callbacks_;			// ����XML��ϻص�

	public:
		PLControl(ISysOpt *sysOpt, IRTDataSvr *rtDataSvr);
		~PLControl();

	private:
		PLControl(const PLControl &);
		PLControl &operator=(const PLControl &);

	public:
		void Start(const PLComplate &plComplate);			// ʧ���׳��쳣
		void Stop();

		void SetForceRefresh();								// ǿ�Ƹ���
		void RegisterCallback(const Callback &callback);	// PL������Ͻ��лص�

	private:
		bool _Init(const PLComplate &plComplate);
		DWORD _Thread();

		http::Buffer _DownLoadCGI();						// ����CGI
		bool _DownloadFileCallback();						// HTTP�ص�
		
		http::Buffer _DownLoadPl(const stdex::tString &plUrl);			// ����ɾ����ϷXML
		http::Buffer _UnZipPL(const http::Buffer &inBuf);		// ��ѹPL


		stdex::tString _GetCGIParam() const;						// ȡ��CGI�Ĳ���
		stdex::tString _ParserCGI(stdex::tString &cgiBuf);			// ����CGI
	};


}




#endif