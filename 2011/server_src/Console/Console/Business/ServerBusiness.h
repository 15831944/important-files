#ifndef __BUSINESS_SERVER_HPP
#define __BUSINESS_SERVER_HPP

#include "../Data/DataHelper.h"


namespace i8desk
{
	namespace business
	{
		namespace Server
		{
			// �Ƿ�����������������
			bool IsRunOnMainServer();

			// �Ƿ���������������
			bool IsMainServer(const data_helper::ServerTraits::ValueType &svr);

			// ��ȡ���з�����
			void GetAllService(const std::tr1::function<void(LPCTSTR, LPCTSTR)> &callback);

			// ͨ��SID���Service
			const data_helper::ServerTraits::ValueType &GetServiceBySID(const stdex::tString &sid);

			// ���˷�����������
			void VDiskFilter(data_helper::VDiskClientTraits::VectorType &disks, const stdex::tString &svrName, const stdex::tString &vID);
		
			// ���˷�����״̬
			void ServerFilter(data_helper::ServerStatusTraits::VectorType &servers, const stdex::tString &serverName);
			

			// ��������Ƿ��ظ�
			bool HasSameName(const stdex::tString &svrID, const stdex::tString &svrName);

			// �޸���������
			bool ModifyAreaPriority(bool isNew, const data_helper::AreaTraits::ElementType *area, const stdex::tString &svrName);
		
			// �Ƿ�����������IP
			bool IsMainServerIP(const ulong svrip);

			// ���÷������Ƿ��Ѵ���
			bool IsServerExsit(const stdex::tString &SID);

			// ��ȡ��������
			const data_helper::ServerTraits::ValueType &GetMainServer();

			// ͨ��IP�ҷ�����ID
			stdex::tString GetServerIDBySvrIP(ulong ip);

			// ͨ��SIDɾ��������
			bool Delete(const stdex::tString &SID, const std::tr1::function<void(LPCTSTR, LPCTSTR)> &error);

			// ��ʽ��������IP
			void FormatIP(const stdex::tString &svrID, stdex::tString &text);

			// ��ʽ��������������Ϣ
			void FormatDisk(const stdex::tString &svrID, stdex::tString &text);

			// ���������з�ʽ
			void GetBalanceTypes(const std::tr1::function<void(int, LPCTSTR)> &callback);
			LPCTSTR GetBalanceTypeDescByType(int type);

			// ����������
			void GetSvrTypes(const std::tr1::function<void(int, LPCTSTR)> &callback);
			LPCTSTR GetSvrTypeDescByType(int type);

			// ͨ��SID�ҷ�������������
			void GetSvrAreaPriotyDescBySID(const stdex::tString &svrID, stdex::tString &text);

			// ͨ��SID���Service����
			stdex::tString GetNameBySID(const stdex::tString &sid);

		}
	}
}

#endif