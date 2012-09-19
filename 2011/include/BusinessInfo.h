#ifndef __BUSINESS_INFO_HPP
#define __BUSINESS_INFO_HPP


namespace i8desk
{
    struct GameExInfoVersion_st
    {
        DWORD gid;
        DWORD dwVersion;
    };
    struct GameExInfoVersionArray_st
    {
        DWORD dwCount;
        GameExInfoVersion_st astItem[1];
    };
	// ��������
	enum BusinessCmd_en
    {
        E_BSC_GET_EX_INFO = 1,    //ȡ����չ��Ϣ��param1��չ��Ϣ���ͣ�param2�����ϷGID��
                                  //����ֵΪ�ձ�ʾ��Ϣ��û�����أ���ֵ������CoTaskMemAlloc����һ���ڴ�ĵ�ַ��
                                  //ǰ�ĸ��ֽڼ�¼��չ��Ϣ���ȣ����涼����չ��Ϣ
        E_BSC_UPDATE_EX_INFO,     //������չ��Ϣ��param1��չ��Ϣ���ͣ�param2�����ϷGID
        E_BSC_GET_GAMEEX_VERSION, //ȡ��������Ϸ����չ��Ϣ�汾������ֵΪ����CoTaskMemAlloc����һ���ڴ�ĵ�ַ���ṹ��GameExInfoVersionArray_st
        E_BSC_GET_GAMEEX_GLOBAL_VERSION, //ȡ����Ϸ����չ��Ϣ�ܰ汾������ֵ���ǰ汾��
	};

	// ��չ��Ϣ����
	enum 
	{ 
		GameXML = 1,	// ��Ϸ���
		ClientXML		// �˵����
	};

}



#endif