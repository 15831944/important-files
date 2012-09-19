#ifndef __CONSOLE_MISC_HPP
#define __CONSOLE_MISC_HPP



namespace i8desk
{
	// IP ���
	stdex::tString IP2String(unsigned long ip);
	unsigned long String2IP(const std::string &ip);
	unsigned long String2IP(const std::wstring &ip);

	bool IsValidIP(LPCTSTR lpszIP);

	// �õ���������IP
	bool GetLocalIps(std::vector<std::string> &IPs);

	// ��ʽ��ʱ��
	stdex::tString FormatTime(time_t time);

	// ��ʱ��
	stdex::tString TotalTime(time_t time);

	// �������ж�
	bool IsLocalMachine(const std::string &ip);
	bool IsRunOnServer();


	//"00-12-EF-AC-0A-78" TO {0x00, 0x12, 0xef, 0xac, 0x0a, 0x78}
	bool StringMacToBinaryMac(const unsigned char *lpszMac, unsigned char *pbuf);

	bool IsValidDirName(const stdex::tString &dir);

	
	// ���ٽ�16������ת��Ϊ��д
	TCHAR *HexStrToUpper(TCHAR *str);

	// Hex 2 QWord
	QWORD HexstrToQword(const TCHAR *str);

	// ת��ʱ�ļ�ʱ��
	DWORD MakeTimeFromFileTime(const FILETIME& ft);

	// Format Size
	void FormatSize(const unsigned long long &size, stdex::tString &text);

	// ���ݺ��ֻ�ȡƴ��
	void GetPY(const stdex::tString &sChinese, stdex::tString &result);
}


#endif