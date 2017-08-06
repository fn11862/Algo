#include "Check.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

Exception::Exception(int line, const char* fileName)
	: Exception{ fileName, line }
{
	const DWORD err = GetLastError();
	std::ostringstream oss;
	oss << "GetLastError() = " << err << "; ";

	wchar_t buffer[4096];
	DWORD wchars = ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, nullptr, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), buffer, _countof(buffer), nullptr);
	if (wchars)
	{
		std::wstring wstr(buffer, buffer + wchars);
		std::string str(wstr.cbegin(), wstr.cend());
		oss << str << "\t";
	}

	m_strDescription += oss.str();
}
