#ifndef __PARSE_PL_HPP
#define __PARSE_PL_HPP

#include "ThreadPoolHelper.h"


namespace i8desk
{
	class IconHelper;

	// ---------------------------------------
	// class Parse PL

	class ParsePL
	{
	private:
		IRTDataSvr *rtData_;
		ulonglong version_;			// �汾��
		IconHelper *iconHelper_;	// ͼ�괦��
		volatile long isExit_;

	public:
		ParsePL(IRTDataSvr *rtData, IconHelper *iconHelper);
	
	private:
		ParsePL(const ParsePL &);
		ParsePL &operator=(const ParsePL &);

	public:
		void Parse(LPCTSTR data);
		void Stop();

	private:
		void _ParseImpl(LPCTSTR data);
	};
}



#endif