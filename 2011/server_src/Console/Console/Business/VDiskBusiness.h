#ifndef __BUSINESS_VDISK_HPP
#define __BUSINESS_VDISK_HPP

#include "../Data/DataHelper.h"

namespace i8desk
{
	namespace business
	{
		// -----------------------------
		// VDISK

		namespace VDisk
		{
			extern u_short VDiskPort;

			// �������з�ʽ
			void RunTypeDesc(const data_helper::VDiskTraits::ValueType &val, stdex::tString &msg);

			template < typename CallBackT >
			void RunTypeDesc(const CallBackT &callback)
			{
				i8desk::GetDataMgr().GetAllData(i8desk::GetDataMgr().GetVDisks());

				using data_helper::VDiskTraits;
				const VDiskTraits::MapType &vDisks = GetDataMgr().GetVDisks();

				stdex::tString msg;
				for(VDiskTraits::MapConstIterator iter = vDisks.begin();
					iter != vDisks.end(); ++iter)
				{
					RunTypeDesc(iter->second, msg);

					callback(msg.c_str(), iter->second);
				}
			}


			// �������������
			void Check(const std::string &ip, u_short port, CString &result);

			// ˢ��������
			void Refresh(const std::string &ip, u_short port, CString &result);

			// ��������̷������̷���ͻ����̷�Ψһ��
			bool IsValid(const stdex::tString &curVID, ulong ip, TCHAR svrDrv, TCHAR cliDrv, const std::tr1::function<void(LPCTSTR, LPCTSTR)> &errCallback);
		
			// ��ȡ����������
			stdex::tString GetVDiskName(const data_helper::VDiskTraits::ValueType &val);
		
			// ɾ��������
			bool Delete(const stdex::tString &VID);

			// ��ȡ������ˢ�̷�ʽ
			void GetLoadTypes(const std::tr1::function<void(int, LPCTSTR)> &callback);
		
			// ͨ��ˢ�̷�ʽ��ȡ������ˢ�̷�ʽ����
			LPCTSTR GetLoadTypeDescByType(int type);

			void GetSsdDrv(const std::tr1::function<void(int, LPCTSTR)> &callback);

			LPCTSTR GetSsdDescByType(int type);

		}

	}

}


#endif