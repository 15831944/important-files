#ifndef __CONFIG_BUSINESS_HPP
#define __CONFIG_BUSINESS_HPP

#include <functional>


namespace i8desk
{
	namespace business
	{
		namespace config
		{
			// ��ȡ����ʡ����
			void GetProvinceName(const std::tr1::function<void(LPCTSTR, size_t)> &callback);

			// ��ȡʡ������������
			void GetCityName(size_t parentID, const std::tr1::function<void(LPCTSTR, size_t)> &callback);

			// ��ȡ������������
			void GetDiskType(const std::tr1::function<void(LPCTSTR, size_t)> &callback);

			// ��ȡ������������
			void GetNetworkType(const std::tr1::function<void(LPCTSTR, size_t)> &callback);

			// ��ȡ������������
			stdex::tString GetDiskNameByType(size_t type);

			// ��ȡ��������
			stdex::tString GetNetworkByType(size_t type);

		
			// ��ȡ���̲�Ʒ����
			void GetDiskProduct(const std::tr1::function<void(LPCTSTR, size_t)> &callback);
		
			// ��ȡ�շ��������
			void GetFeeProductName(const std::tr1::function<void(LPCTSTR, size_t)> &callback);

			// ��ȡ�Ļ��������
			void GetCulturalProductName(const std::tr1::function<void(LPCTSTR, size_t)> &callback);

			//�ж��̷��Ƿ���ڣ��̷�����������ʾ��������·���Ƿ���ڣ�·���������򴴽�
			bool IsValidPath(LPCTSTR path);
		}
	}
}


#endif