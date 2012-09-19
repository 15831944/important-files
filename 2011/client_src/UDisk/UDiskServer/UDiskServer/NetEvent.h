#pragma once

class CNetEvent :
	public INetLayerEvent
{
public:
	CNetEvent(void);
	~CNetEvent(void);


	virtual void Release();

	//���ͻ�����������ʱ���������¼�
	virtual void OnAccept(INetLayer*pNetLayer, SOCKET sck, DWORD param) ;

	//������˷��ͻ��˷������һ�����ݰ�ʱ�������¼�
	virtual void OnSend(INetLayer*pNetLayer, SOCKET sck, LPCSTR lpPackage, DWORD param) ; 

	//������˽��յ��ͻ���һ�����������ʱ���������¼���Ӧ�ò㴦��һ������
	virtual void OnRecv(INetLayer*pNetLayer, SOCKET sck, LPCSTR lpPackage, DWORD param) ;

	//���ͻ��˶Ͽ�ʱ�������¼�.
	virtual void OnClose(INetLayer*pNetLayer, SOCKET sck, DWORD param) ;
protected:
	BOOL	RegisteClient(char* username,char* password,string& str);
	void	GetFilepath();
	int     WriteBlockFile(LPSTR lpackage);
	bool    LogVaild(char* pbuf);
	bool	SendData(SOCKET sck,INetLayer*pNetLayer,WORD cmd,const char* pdata= NULL,DWORD length= 0);
	bool    ScanFile(char* path,vector<FileInfo>& vecfileLst);
	void	SendBlcokFile(INetLayer*pNetLayer, SOCKET sck, LPCSTR lpPackage);
	bool    GetDiskFreeSize();
	bool	ReSetPassword(char* buf);
	void	ScanGameGid(const string& szfile,map<DWORD,FILETIME>& maplst);
private:
	CLock	m_optex;

	map<string,HANDLE> m_mapHandle; //�ļ����֣��ļ������
	SrvConfigInfo* m_pConfigInfo;
};
