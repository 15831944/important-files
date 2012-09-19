#ifndef __MONITOR_BUSINESS_HPP
#define __MONITOR_BUSINESS_HPP

#include "../LogRecord.h"
#include "../Data/DataHelper.h"

#include <list>
#include <tuple>

namespace i8desk
{
	namespace business
	{

		
		namespace monitor
		{

			// ������־��Ϣ
			void PushLog(const LogRecordPtr &log);


			// �ı�Debug ģʽ
			void ChangeDebugMode();

			// ��ȡ������Ϣ
			void GetLogRecord(size_t index, i8desk::LogRecord &log);

			// ��ȡ��Ϣ�ܸ���
			size_t GetLogCount();


			// ����ͻ����쳣��Ϣ
			void PushExcept(const std::tr1::tuple<data_helper::ClientTraits::ValueType, DWORD> &exceptInfo);

			// ��ȡ�쳣��Ϣ
			std::tr1::tuple<stdex::tString, stdex::tString, stdex::tString, stdex::tString > GetExceptInfo(size_t index);

			// ��ȡ�쳣��Ϣ�ܸ���
			size_t GetExceptCount();

			// �Ƿ����쳣
			std::pair<bool, UINT> IsException(const stdex::tString &name, const stdex::tString &ip);

			// ����쳣
			void ClearException();

		}
	}
}




#endif