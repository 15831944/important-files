#ifndef __SKIN_INFO_HPP
#define __SKIN_INFO_HPP

#include <array>


namespace i8desk
{
	namespace ui
	{
		// Ƥ����Ϣ
		struct SkinInfo  
		{		
			stdex::tString skinPath_;

			// ��󻯰�ť
			std::tr1::array<stdex::tString, 3> maxBtn_;
			// ��С����ť
			std::tr1::array<stdex::tString, 3> minBtn_;
			// �رհ�ť
			std::tr1::array<stdex::tString, 3> closeBtn_;
			// ���ð�ť
			std::tr1::array<stdex::tString, 3> settingBtn_;

			// Main Frame
			std::tr1::array<stdex::tString, 10> mainFrame_;

			// Top Logo
			stdex::tString topLogo_;

			// Navigate Tabe
			std::tr1::array<stdex::tString, 18> navTab_;

			// Menu Background
			std::tr1::array<stdex::tString, 3> menuBg_;

			// Add Modify Delete
			std::tr1::array<stdex::tString, 3> addBtn_;
			std::tr1::array<stdex::tString, 3> delBtn_;
			std::tr1::array<stdex::tString, 3> modBtn_;

			// List Header
			std::tr1::array<stdex::tString, 2> listHeader_;

			// Left Working Area
			std::tr1::array<stdex::tString, 3> leftWorking_;
			// Right Working Area
			std::tr1::array<stdex::tString, 5> rightWorking_;

			// OutBox Line & Table Line
			std::tr1::array<stdex::tString, 2> boxLine_;

			// Query Input & button
			std::tr1::array<stdex::tString, 2> query_;

			// Server
			stdex::tString serverMain_;
			stdex::tString serverVDiskClient_;
		

			// Sync Task
			stdex::tString syncTaskMain_;
			stdex::tString syncTaskRes_;

			stdex::tString syncTaskTransfering_;
			stdex::tString syncTaskTransferOK_;
			
			std::tr1::array<stdex::tString, 2> syncTaskStateNormal_;
			std::tr1::array<stdex::tString, 2> syncTaskStateCurrent_;
			std::tr1::array<stdex::tString, 2> syncTaskFromTo_;
			std::tr1::array<stdex::tString, 3> syncBg_;

			// Client
			stdex::tString clientMain_;
			std::tr1::array<stdex::tString, 2> clientStatus_;

			// Ctor
			SkinInfo();
			// Dtor
			~SkinInfo();

			const stdex::tString &GetSkinPath() const;			// ��ȡƤ��·��
			void Load(const stdex::tString &filePath);		// ��ָ��Ƥ�������ļ��м���Ƥ����Ϣ
		};
	}
}

#endif