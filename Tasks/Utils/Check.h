#pragma once

#include <sstream>
#include <string>

class Exception : public std::exception
{
public:
	Exception(const char* fileName, int line)
	{
		std::ostringstream oss;
		oss << fileName << '(' << line << ") Failed: ";
		m_strDescription = oss.str();
	}
	Exception(int line, const char* fileName); //GetLastError() implementation

	template <typename T>
	Exception& operator << (const T& description)
	{
		std::ostringstream oss;
		oss << ' ' << description;
		m_strDescription += oss.str();
		return *this;
	}
	
	const char* what() const
	{
		return m_strDescription.c_str();
	}

private:
	std::string m_strDescription;
};

#define _throw()						throw Exception(__FILE__, __LINE__)
#define _check(expr)	  if (!(expr))  throw Exception(__FILE__, __LINE__)
#define _check_GLE(expr)  if (!(expr))  throw Exception(__LINE__, __FILE__)