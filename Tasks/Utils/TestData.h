#pragma once
#include <fstream>
#include <string>
#include <vector>

struct FileTestData : public std::ifstream
{
	//#TODO: pre-parse? Probably file IO + ifstream::operator>> may take a lot of resources compare to algorithm body
	FileTestData(const std::string& fileName, unsigned run);
};

struct ConsoleTestData
{
	ConsoleTestData& operator >> (bool& val);
	ConsoleTestData& operator >> (short& val);
	ConsoleTestData& operator >> (unsigned short& val);
	ConsoleTestData& operator >> (int& val);
	ConsoleTestData& operator >> (unsigned int& val);
	ConsoleTestData& operator >> (long& val);
	ConsoleTestData& operator >> (unsigned long& val);
	ConsoleTestData& operator >> (long long& val);
	ConsoleTestData& operator >> (unsigned long long& val);
	ConsoleTestData& operator >> (float& val);
	ConsoleTestData& operator >> (double& val);
};

class Result
{
public:
	Result(); //Console run
	Result(const std::string& fileName, unsigned run);
	~Result();

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