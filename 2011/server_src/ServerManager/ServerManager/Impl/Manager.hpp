#ifndef __MANAGER_HPP
#define __MANAGER_HPP

#include <functional>

namespace mgr
{

	class ServiceMgr
	{
		typedef std::tr1::function<stdex::tString (const stdex::tString &)> RunVDiskCallback;

	public:
		ServiceMgr();

	private:
		ServiceMgr(const ServiceMgr &);
		ServiceMgr &operator=(const ServiceMgr &);

	public:
		// �Ƿ�Ϊ������
		bool IsManService() const;

		// �Ƿ�Ϊ�����̷���
		bool IsVDiskService() const;

		// �Ƿ�����������
		bool IsRunMainService() const;

		// �Ƿ����������̷���
		bool IsRunVDiskService() const;

		// ����������
		bool RunMainService();

		// ���������̷���
		bool RunVDiskService();

		// ֹͣ������
		bool StopMainService();

		// ֹͣ�����̷���
		bool StopVDiskService();

		// ��������������
		void RunMainConfig();

		// ��������������
		void RunVDiskConfig(const RunVDiskCallback &callback);
	};
}


#endif