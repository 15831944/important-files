#include "stdafx.h"
#include "DataMgr.h"

#include <sstream>


namespace data
{

	DataMgr &DataMgrInstance()
	{
		static DataMgr mgr;
		return mgr;
	}

	DataMgr::DataMgr()
		: permission_(0)
	{

	}
	DataMgr::~DataMgr()
	{

	}


	void DataMgr::SetUserInfo(const std::wstring &userName, const std::wstring &psw)
	{
		userName_ = userName;
		psw_ = psw;
	}

	std::pair<const std::wstring, const std::wstring> DataMgr::GetUserInfo() const
	{
		return std::make_pair(userName_, psw_);
	}

	std::wstring DataMgr::GetUrl(size_t index) const
	{
		static LPCWSTR urls[] = 
		{
			L"http://www.hmj001.com/webk/login.php",
			L"http://www.hmj001.com/webk/uppass.php",
			L"http://www.hmj001.com/webk/sy.php",
			L"http://www.hmj001.com/webk/nc.php",
			L"http://www.hmj001.com/webk/sp.php",
			L"http://www.hmj001.com/webk/tgpj.php",
			L"http://www.hmj001.com/webk/hjb.php",
			L"http://www.hmj001.com/webk/smyj.php",
			L"http://www.hmj001.com/webk/jgnc.php",
			L"http://www.hmj001.com/webk/tgpje.php",
			L"http://www.hmj001.com/webk/hjbe",
			L"http://www.hmj001.com/webk/smyje.php"
		}; 

		assert(index >=0 && index < _countof(urls));

		std::wstring url;
		if( index != 0 || index != 1 )
		{
			std::wstringstream os;
			os << urls[index] << L"?username=" 
				<< userName_ << L"&password=" 
				<< psw_;

			url = os.str();
		}
		else
		{
			url = urls[index];
		}

		return url;
	}

	void DataMgr::SetPermission(size_t permission)
	{
		permission_ = permission;
	}

	bool DataMgr::HasPermission(size_t index) const
	{
		// ǰ3����������Ȩ���û�
		switch(index)
		{
		case 2:
		case 3:
		case 4:
			return true;
			// ������Ϊ�ƹ��ռ�Ȩ��
		case 5:
			{
				if( permission_ == NORMAL )
					return true;
				else
					return false;
			}
			break;
			// ������Ϊ�ƽ��Ȩ��
		case 6:
			{
				if( permission_ == GOLDEN )
					return true;
				else
					return false;
			}
			break;
			// ������Ϊ˽ļӮ�Ұ�
		case 7:
			{
				if( permission_ == Diamond )
					return true;
				else
					return false;
			}
			break;
		default:
			assert(0);
		}
		
		return false;
	}
}