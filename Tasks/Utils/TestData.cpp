#include "Utils\Check.h"
#include "Utils\TestData.h"
#include <fstream>
#include <iostream>

namespace {

	std::string GetFileName(const std::string& file, const char* const extention)
	{
		std::string path = "W:\\!AlgoTasks\\TestData\\"; //#TODO: get this right
		path += file + extention;
		return path;
	}

} // unnamed namespace

FileTestData::FileTestData(const std::string& file)
	: std::ifstream{GetFileName(file, ".in")}
{
	_check(good()) << "Failed to open" << GetFileName(file, ".in");
}

ConsoleTestData& ConsoleTestData::operator >> (bool& val)               { std::cin >> val; return *this; }
ConsoleTestData& ConsoleTestData::operator >> (short& val)              { std::cin >> val; return *this; }
ConsoleTestData& ConsoleTestData::operator >> (unsigned short& val)     { std::cin >> val; return *this; }
ConsoleTestData& ConsoleTestData::operator >> (int& val)                { std::cin >> val; return *this; }
ConsoleTestData& ConsoleTestData::operator >> (unsigned int& val)       { std::cin >> val; return *this; }
ConsoleTestData& ConsoleTestData::operator >> (long& val)               { std::cin >> val; return *this; }
ConsoleTestData& ConsoleTestData::operator >> (unsigned long& val)      { std::cin >> val; return *this; }
ConsoleTestData& ConsoleTestData::operator >> (long long& val)          { std::cin >> val; return *this; }
ConsoleTestData& ConsoleTestData::operator >> (unsigned long long& val) { std::cin >> val; return *this; }
ConsoleTestData& ConsoleTestData::operator >> (float& val)              { std::cin >> val; return *this; }
ConsoleTestData& ConsoleTestData::operator >> (double& val)             { std::cin >> val; return *this; }


Result::Result(const std::string& fileName)
{
	std::ifstream ifs{ GetFileName(fileName, ".out") };
	std::string line;
	while (std::getline(ifs, line))
	{
		m_expected.push_back(line);
	}
}
Result::~Result()
{
	if (m_received.size() != m_expected.size())
	{
		std::cout << "Invalid result count: received/expected = " << m_received.size() << ' ' << m_expected.size() << '\n';
		return;
	}

	bool ok = true;
	for (size_t i = 0; i < m_received.size(); ++i)
	{
		if (m_received[i] != m_expected[i])
		{
			ok = false;
			break;
		}
	}
	if (ok)
	{
		std::cout << "Correct!!!\n";
		return;
	}

	std::cout << "Expected       Received\n";
	for (size_t i = 0; i < m_received.size(); ++i)
	{
		std::cout << m_expected[i] << "              " << m_received[i] << "\n\n";
	}
}
