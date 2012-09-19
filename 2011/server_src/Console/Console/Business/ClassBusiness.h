#ifndef __CLASS_BUSINESS_HPP
#define __CLASS_BUSINESS_HPP

#include "../Data/DataHelper.h"


namespace i8desk
{
	namespace business
	{

		namespace Class
		{
			// ����Class Name��ȡCID
			stdex::tString GetCID(const stdex::tString &className);

			// ����Class CID�õ�Name
			stdex::tString GetName(const stdex::tString &CID);

			// �Ƿ�Ϊ������Ϸ
			bool IsSingleGame(const stdex::tString &CID);

			// �õ�Ĭ������������Class��
			void GetAllSortedClasses( data_helper::ClassTraits::VectorType &classes );

			// �õ�Ĭ�������Ĺٷ�Class��
			void GetSortDefaultClass( data_helper::ClassTraits::VectorType &classes );

			// �Ƿ�ΪĬ�����
			bool IsDefault(const stdex::tString &CID);

			// ��ȡͼ��
			const utility::BITMAPPtr &GetIcon(const data_helper::ClassTraits::ValueType &val);

			// ����ͼ��
			void SetIcon(const data_helper::ClassTraits::ValueType &val, const utility::BITMAPPtr &icon);
		
			// ��������Ƿ��ظ�
			bool HasSameName(const data_helper::ClassTraits::ValueType &val);
			
			// ��ȡ·��
			stdex::tString GetPath(const data_helper::ClassTraits::ValueType &val);

			// ���������Ƿ������Ϸ
			bool HasGame(const stdex::tString &CID);

			// ���������ݷ�ʽ
			void SetDeskTopClass( const data_helper::ClassTraits::ValueType &val);

			// ȡ�������ݷ�ʽ
			void UnSetDeskTopClass(const data_helper::ClassTraits::ValueType &val);

			// �Ƿ����������ݷ�ʽ
			bool IsSetDeskTopClass(const data_helper::ClassTraits::ValueType &val);

		}
	}
}



#endif