#pragma once
#include <fstream>
#include <string>
#include <vector>

struct FileTestData : public std::ifstream
{
	explicit FileTestData(const std::string& fileName);
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
	explicit Result(const std::string& fileName);
	~Result();

	template<typename T>
	Result& operator << (const T& data)
	{
		m_received.push_back(std::to_string(data));
		return *this;
	}

private:
	std::vector<std::string> m_expected;
	std::vector<std::string> m_received;
};