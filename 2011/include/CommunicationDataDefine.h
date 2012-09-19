#pragma once 

namespace CommunicationData_ns
{
    struct PlugIn_st //�����Ϣ
    {
        //Attribuild
        DWORD    gid;                           //����ID
        TCHAR    cid[ MAX_GUID_LEN ];           //������� 
        DWORD    dwIdcVer;                      //���İ汾��
        DWORD    dwSvrVer;                      //���ذ汾��
        //Base Elenment
        TCHAR    atName[ MAX_NAME_LEN ];        //��������
        DWORD    dwSize;                        //���ߴ�С    
        DWORD    dwIdcClick;                    //���Ŷ�
        DWORD    dwDownloadType;                //��������    enum{
                                                //1����ʾServer Element;
                                                //2����ʾClient Element;
                                                //4����ʾConfig Element;}
        DWORD    dwDownloadStatus;              // 0:δ���أ�1��������
        DWORD    dwStatus;                      // 0��δ����;1�������ã�
        //Client Element
        TCHAR    atCliName[ MAX_NAME_LEN ];
        TCHAR    atCliExe[ MAX_PATH ];
        TCHAR    atCliParam[ MAX_PARAM_LEN ];
        TCHAR    atCliPath[ MAX_PATH ];
        DWORD    dwCliRunType;
    
        template<class STREAM>
        void Read(STREAM& clStream)
        {
            clStream>>gid>>cid>>dwIdcVer>>dwSvrVer>>atName>>dwSize>>dwIdcClick>>dwDownloadType>>dwDownloadStatus>>dwStatus>>atCliName>>atCliExe>>atCliParam>>atCliPath>>dwCliRunType;
        }
        template<class STREAM>
        void Write(STREAM& clStream) const
        {
            clStream<<gid<<cid<<dwIdcVer<<dwSvrVer<<atName<<dwSize<<dwIdcClick<<dwDownloadType<<dwDownloadStatus<<dwStatus<<atCliName<<atCliExe<<atCliParam<<atCliPath<<dwCliRunType;
        }
        BOOL IsEnable() const
        {
            return dwDownloadStatus && (dwDownloadType & 0x2) && dwStatus;
        }
    };
}
