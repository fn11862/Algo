#pragma once
#include <fstream>
#include <string>
#include <vector>

struct FileTestData : public std::ifstream
{
	//#TODO: pre-parse? Probably file IO + ifstream::operator>> may take a lot of resources compare to algorithm body
	FileTestData(const std::string& fileName, unsigned run);
};

class Result
{
public:
	Result(); //Console run
	Result(const std::string& fileName, unsigned run);
	~Result();

	Result& operator << (const char* const str)
	{
		m_received.push_back(std::string(str));
		return *this;
	}

	Result& operator << (const std::string& str)
	{
		m_received.push_back(str);
		return *this;
	}

	template<typename T>
	Result& operator << (const T& data)
	{
		m_received.push_back(std::to_string(data));
		return *this;
	}

private:
	const bool               m_consoleRun;
	std::vector<std::string> m_expected;
	std::vector<std::string> m_received;
};

std::string GetTestCasePath(const std::string& testCaseName, unsigned run, bool input);