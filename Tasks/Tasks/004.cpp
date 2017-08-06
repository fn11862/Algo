#include "Headers.h"

// https://www.hackerrank.com/challenges/reduced-string/problem

void t004(unsigned run)
{
	FileTestData cin (__FUNCTION__, run);
	Result       cout(__FUNCTION__, run);
	PerfTimer    perf;

	std::string str;
	cin >> str;

	bool duplicatesFound = true;
	while (duplicatesFound)
	{
		if (str.size() < 2)
		{
			break;
		}
		duplicatesFound = false;

		for (int i = 1; i < str.size(); ++i)
		{
			if (str[i - 1] == str[i])
			{
				str.erase(i - 1, 2);
				duplicatesFound = true;
			}
		}
	}

	if (str.empty())
	{
		cout << "Empty String";
	}
	else
	{
		cout << str;
	}

	perf.PrintResult();
}