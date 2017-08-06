#include "Utils\Check.h"
#include "Utils\TestData.h"
#include <fstream>
#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace {

	//Full EXE path is "W:\!AlgoTasks\!out\out_Win32\Debug\Tasks.exe"
	//"!out" is defined in project properties, so cut the full path to this symbol
	std::string GetSoluctionFolder()
	{
		const int buffSize = 4096;
		wchar_t buffer[buffSize] = { 0 };
		_check_GLE(GetModuleFileName(NULL, buffer, buffSize)) << "Can't Get full path";

		std::wstring wstr{ buffer };
		std::string fullPath{ wstr.cbegin(), wstr.cend() };

		auto pos = fullPath.rfind('!');
		return fullPath.substr(0, pos);
	}

} // unnamed namespace

std::string GetTestCasePath(const std::string& testCaseName, unsigned run, bool input)
{
	static const std::string testCaseRoot = GetSoluctionFolder() + "TestData\\";
	std::string path = testCaseRoot;
	path += testCaseName + '.' + std::to_string(run);
	path += input ? ".in" : ".out";
	return path;
}

FileTestData::FileTestData(const std::string& file, unsigned run)
	: std::ifstream{ GetTestCasePath(file, run, true)}
{
	_check(good()) << "Failed to open" << GetTestCasePath(file, run, true);
}

Result::Result(const std::string& fileName, unsigned run)
	: m_consoleRun{ false }
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "Test case: " << GetTestCasePath(fileName, run, true) << '\n';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	std::ifstream ifs{ GetTestCasePath(fileName, run, false) };
	_check(ifs.good());

	std::string line;
	while (std::getline(ifs, line))
	{
		m_expected.push_back(line);
	}
}

Result::Result()
	: m_consoleRun{ true }
{}

Result::~Result()
{
	if (m_consoleRun)
	{
		//No results available
		return;
	}

	if (m_received.size() != m_expected.size())
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		std::cout << "Invalid result count:\n";
		std::cout << "Received = " << m_received.size() << " Expected = " << m_expected.size() << '\n';
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << "Correct!!!\n\n";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		return;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << "Invalid result:\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	for (size_t i = 0; i < m_received.size(); ++i)
	{
		std::cout << "Expected[" << i << "]  " << m_expected[i] << '\n';
		std::cout << "Received[" << i << "]  " << m_received[i] << '\n';
	}
	std::cout << "\n\n";
}