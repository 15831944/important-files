#ifndef __CLIENT__BUSINESS_HPP
#define __CLIENT__BUSINESS_HPP

#include "../Data/DataHelper.h"
#include "../ui/DlgClientSystemInfo.h"

namespace i8desk
{
	namespace business
	{

		namespace Client
		{

			typedef std::tr1::function<bool()> Callback;

			// ����IP�õ��ͻ�����
			stdex::tString GetNameByIP(ulong ip);

			// ���绽��
			void ControlStart(const data_helper::ClientTraits::VectorType &clients);

			// �����ͻ���
			void ControlRestart(const data_helper::ClientTraits::VectorType &clients);

			// �رտͻ���
			void ControlShutdown(const data_helper::ClientTraits::VectorType &clients);

			// ���̼��
			void ControlDiskRecorver(const data_helper::ClientTraits::VectorType &clients, const stdex::tString &areas);

			// ִ�пͻ����ļ�
			void ControlRunClientFile(const data_helper::ClientTraits::VectorType &clients,  const stdex::tString &path);

			// ��װȫ�̱�����ԭ
			void ControlInstallAll(const data_helper::ClientTraits::VectorType &clients);

			// ��װ��ԭ
			void ControlInstall(const data_helper::ClientTraits::VectorType &clients);

			// ����������ԭ
			void ControlProtoArea(const data_helper::ClientTraits::VectorType &clients, const stdex::tString &protAreas, const stdex::tString &unProtAreas);

			// ж�ػ�ԭ
			void ControlRestore(const data_helper::ClientTraits::VectorType &clients);

			// �鿴ϵͳ��Ϣ
			void ControlViewSystem(const data_helper::ClientTraits::VectorType &clients, stdex::tString &text);

			// �鿴������Ϣ
			void ControlViewProcess(const data_helper::ClientTraits::VectorType &clients, stdex::tString &text);

			// �鿴������Ϣ
			void ControlViewService(const data_helper::ClientTraits::VectorType &clients, stdex::tString &text);

			// �鿴��Ϸ��Ϣ
			void ControlViewGames(const data_helper::ClientTraits::VectorType &clients);

			// Զ�̿���
			void ControlRemoteControl(const data_helper::ClientTraits::VectorType &clients);

			// Զ�̲鿴
			void ControlRemoteView(const data_helper::ClientTraits::VectorType &clients);

			// ˢ�¿ͻ���
			void ControlRefresh(const data_helper::ClientTraits::VectorType &clients);
			
			// ��������/ֹͣ����
			void ControlKillProcess(const stdex::tString &file, const DWORD clientIP, bool IsProcess );
			
			// ��������
			void AreaFilter(data_helper::ClientTraits::VectorType &curClients, const stdex::tString &AID);

			// ��������
			void AreaRealFilter(data_helper::ClientTraits::VectorType &sClients, data_helper::ClientTraits::VectorType &dClients, const stdex::tString &AID);

			
			// ����ϵͳ��Ϣ
			void PraseViewSystem( CString &text );
			
			// ���ͽ�����Ϣ
			void PraseViewProcess( std::vector<ListVector> &listVector ,const stdex::tString &Info);
			
			// ���ͷ�����Ϣ
			void PraseViewService( std::vector<ListVector> &listVector ,const stdex::tString &Info );

			// �õ�δ��������
			void GetUnProtArea(const CString &allAreas, const CString &protAreas, stdex::tString &unprotAreas);
		
			// ��ʽ������
			void ParseProtArea(const stdex::tString &clientName,  std::vector<stdex::tString> &partiions);
			
			// �õ���������
			void GetProtArea( const stdex::tString &Partition, stdex::tString &protarea);
		}
	}
}

#endif