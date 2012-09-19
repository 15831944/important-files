#ifndef __PUSHGAME_BUSINESS_HPP
#define __PUSHGAME_BUSINESS_HPP

#include "../ManagerInstance.h"


namespace i8desk
{
	namespace business
	{

		namespace PushGame
		{
			// ��ȡ����������������
			stdex::tString GetAreaDesc(const data_helper::PushGameTraits::ValueType &val);

			// ��ȡ���Ͳ�������
			stdex::tString GetParameterDesc(const data_helper::PushGameTraits::ValueType &val, int type );

			// ������Ϸ����
			void LocalAllFilter(data_helper::GameTraits::VectorType &curGames);

			// ����������
			void ClassFilter(data_helper::GameTraits::VectorType &curGames, data_helper::ClassTraits::MapType &curClass);

			// �����������
			void TaskAreaFilter(stdex::tString TID, data_helper::BootTaskAreaTraits::VectorType &curTaskareas);

			// ��������Ƿ��ظ�
			bool HasSameName(const data_helper::PushGameTraits::ValueType &val);

			// �õ��Ա�����
			stdex::tString GetCheckDesc(const size_t checktype );

			// ���
			template < typename AIDT >
			bool Add(const data_helper::PushGameTraits::ValueType &pushgame, const AIDT &aids)
			{
				using data_helper::PushGameTraits;
				using data_helper::BootTaskAreaTraits;

				PushGameTraits::MapType &pushgames = GetDataMgr().GetPushGames();
				BootTaskAreaTraits::MapType &bootAreas = GetDataMgr().GetBootTaskAreas();

				if( !GetDataMgr().AddData(pushgames, pushgame->TID, pushgame) )
					return false;

				for(typename AIDT::const_iterator iter = aids.begin(); iter != aids.end(); ++iter)
				{
					BootTaskAreaTraits::ValueType val(new BootTaskAreaTraits::ElementType);

					utility::Strcpy(val->TID, pushgame->TID);
					utility::Strcpy(val->AID, *iter);

					if( !GetDataMgr().AddData(bootAreas, std::make_pair(val->TID, val->AID), val) )
						return false;
				}

				return true;
			}

			// �޸�
			template < typename AIDT >
			bool Modify(const data_helper::PushGameTraits::ValueType &pushgame, const AIDT &srcAID, AIDT &destAID)
			{
				using data_helper::PushGameTraits;
				using data_helper::BootTaskAreaTraits;

				PushGameTraits::MapType &pushgames = GetDataMgr().GetPushGames();

				if( !GetDataMgr().ModifyData(pushgames, pushgame->TID, pushgame) )
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

						utility::Strcpy(val->TID, pushgame->TID);
						utility::Strcpy(val->AID, *iter);

						if( !GetDataMgr().DelData(bootAreas, std::make_pair(val->TID, val->AID)) )
							return false;
					}
				}

				// �����Ԫ��
				for(typename AIDT::const_iterator iter = destAID.begin(); iter != destAID.end(); ++iter)
				{
					BootTaskAreaTraits::ValueType val(new BootTaskAreaTraits::ElementType);

					utility::Strcpy(val->TID, pushgame->TID);
					utility::Strcpy(val->AID, *iter);

					if( !GetDataMgr().AddData(bootAreas, std::make_pair(val->TID, val->AID), val) )
						return false;
				}

				return true;
			}
			
		}
	}
}


#endif