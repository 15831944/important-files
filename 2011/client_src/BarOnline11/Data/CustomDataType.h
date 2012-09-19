#ifndef __BARONLINE_CUSTOM_DATA_TYPE_HPP
#define __BARONLINE_CUSTOM_DATA_TYPE_HPP

#include "../../../include/tablestruct.h"

namespace i8desk
{

	namespace data
	{
		// �ղؼ���Ϣ
		struct Favorite
		{
			stdex::tString Type;			// ����
			stdex::tString Name;			// ����
			stdex::tString Url;				// ��ַ
		};


		// ��Ϸ��Ϣ
		struct GameInfo
		{

			DWORD				Gid;			// ��Ϸid.
			DWORD				Pid;			// ��Ϸ����id.
			stdex::tString		Name;			// ��Ϸ����
			stdex::tString		IdcClass;		// ��Ϸ���
			stdex::tString		Exe;			// ��Ϸ���еģţأ�.(���·��)
			stdex::tString		Param;			// ���еĲ���
			stdex::tString		Py;				// ��Ϸ���Ƶ�ƴ��
			stdex::tString		MultiPy;        // ������ƴ��
			size_t				FindPos;		// ƥ���λ��
			DWORD				Size;			// ��Ϸ�Ĵ�С���ԣ�Ϊ��λ��
			DWORD				DeleteFlag;     // ��Ϸ�ռ䲻��ʱ����ɾ��
			bool				DeskLnk;		// �Ƿ���ʾ�������ݷ�ʽ
			bool				Toolbar;		// �Ƿ���ʾ���˵�������
			stdex::tString		SvrPath;		// ��Ϸ�����·��
			stdex::tString		CliPath;		// ��Ϸ�ͻ���·��
			stdex::tString		MatchFile;		// ��Ϸ�Զ����������ļ�
			stdex::tString		SaveFilter;		// ��Ϸ�浵��Ϣ
			DWORD				I8Play;			// ��ֵ���Ϸ
			DWORD				IdcClick;		// ��Ϸȫ������
			DWORD				SvrClick;		// ��Ϸ���ɵ���
			DWORD				RunType;		// ��Ϸ���з�ʽ
			DWORD				NetbarVer;      // ���ɷ������汾
			stdex::tString		VID;			// ��Ϸ����������ID
			stdex::tString      GameArea;       // ר��URL
			stdex::tString      RegUrl;         // ע���ַ 
			stdex::tString      PayUrl;         // ֧����ַ
			stdex::tString      VideoUrl;       // ��Ƶ����

			utility::ICONPtr	hIcon;			// ��Ϸͼ��
		};

		// ��������Ϣ
		struct VDiskInfo
			: public db::tVDisk
		{

		};

		// ��������б�����
		struct SvrCfg
			: public db::tServer
		{
			DWORD	SyncType;				// ͬ����ʽ
		};

		// ͼ������
		struct IconInfo
			: public db::tIcon
		{

		};
	}


}






#endif