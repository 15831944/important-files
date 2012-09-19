#ifndef __BOOTTASK_BUSINESS_HPP
#define __BOOTTASK_BUSINESS_HPP

#include "../ManagerInstance.h"
#include <atlpath.h>

namespace i8desk
{
	namespace business
	{

		namespace BootTask
		{
			// ��ȡ����������������
			stdex::tString GetAreaDesc(const data_helper::BootTaskTraits::ValueType &val);

			// ��ȡִ�����ڶ�
			stdex::tString GetRangeDate(const data_helper::BootTaskTraits::ValueType &val);

			// ��ȡִ��ʱ���
			stdex::tString GetRangeTime(const data_helper::BootTaskTraits::ValueType &val);

			// ��ȡ����ִ������
			stdex::tString GetRunType(const data_helper::BootTaskTraits::ValueType &val);
			
			// ��ȡ����������������
			stdex::tString GetTypeDesc(const data_helper::BootTaskTraits::ValueType &val);

			// ������Ϣ�ص�
			typedef std::tr1::function<int (LPCTSTR)> TypeDescCallback;
			typedef std::tr1::function<int (int, DWORD_PTR)> TypeDataCallback;
			void TypeDesc(const TypeDescCallback &descCallback, const TypeDataCallback &dataCallback);

			// ��������Ƿ��ظ�
			bool HasSameName(const data_helper::BootTaskTraits::ValueType &val);

			// ���
			template < typename AIDT >
			bool Add(const data_helper::BootTaskTraits::ValueType &bootTask, const AIDT &aids)
			{
				using data_helper::BootTaskTraits;
				using data_helper::BootTaskAreaTraits;

				BootTaskTraits::MapType &bootTasks = GetDataMgr().GetBootTasks();
				BootTaskAreaTraits::MapType &bootAreas = GetDataMgr().GetBootTaskAreas();

				if( !GetDataMgr().AddData(bootTasks, bootTask->TID, bootTask) )
					return false;

				for(typename AIDT::const_iterator iter = aids.begin(); iter != aids.end(); ++iter)
				{
					BootTaskAreaTraits::ValueType val(new BootTaskAreaTraits::ElementType);

					utility::Strcpy(val->TID, bootTask->TID);
					utility::Strcpy(val->AID, *iter);

					if( !GetDataMgr().AddData(bootAreas, std::make_pair(val->TID, val->AID), val) )
						return false;
				}

				return true;
			}

			// �޸�
			template < typename AIDT >
			bool Modify(const data_helper::BootTaskTraits::ValueType &bootTask, const AIDT &srcAID, AIDT &destAID)
			{
				using data_helper::BootTaskTraits;
				using data_helper::BootTaskAreaTraits;

				BootTaskTraits::MapType &bootTasks = GetDataMgr().GetBootTasks();

				if( !GetDataMgr().ModifyData(bootTasks, bootTask->TID, bootTask) )
					return false;

				BootTaskAreaTraits::MapType &bootAreas = GetDataMgr().GetBootTaskAreas();
				// ɾ����Ԫ��
				for(typename AIDT::const_iterator iter = srcAID.begin(); iter != srcAID.end(); ++iter)
				{
					if( destAID.find(*iter) != destAID.end() )
					{
						destAID.erase(*iter);
					}
					else
					{
						BootTaskAreaTraits::ValueType val(new BootTaskAreaTraits::ElementType);

						utility::Strcpy(val->TID, bootTask->TID);
						utility::Strcpy(val->AID, *iter);

						if( !GetDataMgr().DelData(bootAreas, std::make_pair(val->TID, val->AID)) )
							return false;
					}
				}

				// �����Ԫ��
				for(typename AIDT::const_iterator iter = destAID.begin(); iter != destAID.end(); ++iter)
				{
					BootTaskAreaTraits::ValueType val(new BootTaskAreaTraits::ElementType);

					utility::Strcpy(val->TID, bootTask->TID);
					utility::Strcpy(val->AID, *iter);

					if( !GetDataMgr().AddData(bootAreas, std::make_pair(val->TID, val->AID), val) )
						return false;
				}

				return true;
			}
			
			// ��ȡͼƬ����
			void GetImageFileName( std::vector<stdex::tString> &files );

			// �Ƿ�ΪͼƬ��ʽ
			bool IsImage(const CString &ext);
		
		
			// ��ȡִ������
			void GetRunDate(const std::tr1::function<void(int, LPCTSTR)> &callback);

			// ��ȡѡ������
			void GetCheckDate(const std::tr1::function<void(int)> &callback);

			// ���з�ʽ
			bool IsRunAtBoot(const data_helper::BootTaskTraits::ValueType &val);

			// �������з�ʽ
			int SetRunType(bool isRunBoot);
			
		}
	}
}


#endif