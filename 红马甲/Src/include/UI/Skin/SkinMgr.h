#ifndef __SKIN_MANAGER_HPP
#define __SKIN_MANAGER_HPP

#include <memory>
#include <map>
#include "SkinInfo.h"
#include "SkinLoader.h"


namespace i8desk
{
	namespace ui
	{
		class SkinMgr
		{
		private:
			stdex::tString skinsPath_;								// Ƥ��·��
			stdex::tString defaultSkinPath_;						// Ĭ��Ƥ��·��
			std::auto_ptr<SkinInfo> currentSkin_;					// ��ǰƤ��
			SkinLoaderPtr loader_;									// Ƥ��������
			typedef std::map<stdex::tString, utility::BITMAPPtr> Skins;
			Skins skins_;											// ����Ƥ��

			typedef std::map<long, utility::ICONPtr> Icons;
			Icons icons_;											// ����ͼ��

		public:
			SkinMgr();
			~SkinMgr();

			// Ban
		private:
			SkinMgr(const SkinMgr&);
			SkinMgr& operator=(const SkinMgr&);


		public:
			const SkinInfo *GetSkinInfo() const;						// ��ȡ��ǰƤ����Ϣ	
			void SetSkinInfo(const stdex::tString &skinFile);			// ���õ�ǰƤ����Ϣ

		public:
			utility::BITMAPPtr GetSkin(const stdex::tString &name);		// ��ȡƤ��
			utility::ICONPtr GetIcon(long gid);							// ��ȡͼ��
		};


		SkinMgr &SkinMgrInstance();
	}

}




#endif