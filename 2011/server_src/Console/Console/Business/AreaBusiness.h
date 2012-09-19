#ifndef __BUSINESS_AREA_HPP
#define __BUSINESS_AREA_HPP

#include "../Data/DataHelper.h"


namespace i8desk
{
	namespace business
	{

		// ---------------------------------
		// Area

		namespace Area
		{
			// ��AID�õ�����
			const stdex::tString &GetAIDByName(const stdex::tString &name);
		
			// �Ƿ�ΪĬ�Ϸ���
			bool IsDefaultArea(const data_helper::AreaTraits::ValueType &val);

			// ȷ��Ĭ�Ϸ�������
			void EnsureDefaultArea();

			// ��������
			bool ParseArea(const stdex::tString &area, data_helper::RunTypeTraits::ValueType &runType);

			// �����������з�ʽ
			stdex::tString ParseRunType(const stdex::tString &AID, const stdex::tString &areaRunType);
			stdex::tString ParseRunType(const stdex::tString &AID, const data_helper::RunTypeTraits::VectorType &runTypes);
		
			// ��������Ƿ��ظ�
			bool HasSameName(const data_helper::AreaTraits::ValueType &val);

		}
	}

}


#endif