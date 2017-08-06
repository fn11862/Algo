#include "Headers.h"
#include <array>

// https://www.hackerrank.com/challenges/two-characters/problem

void t005(unsigned run)
{
	FileTestData cin (__FUNCTION__, run);
	Result       cout(__FUNCTION__, run);
	PerfTimer    perf;

	unsigned N;
	cin >> N;
	std::string inputString;
	cin >> inputString;

	// Create an alphabet of present chars
	std::array<bool, 26> alphabet{ 0 };
	for (char ch : inputString)
	{
		alphabet[ch - 'a'] = true;
	}

	std::string tmp;
	tmp.reserve(N);

	size_t maxResult = 0;
	for (char ch0 = 'a'; ch0 <= 'z'; ++ch0)
	{
		for (char ch1 = 'a'; ch1 <= 'z'; ++ch1)
		{
			//Check if the pair is valid
			if ((ch0 == ch1) || !alphabet[ch0 - 'a'] || !alphabet[ch1 - 'a'])
				continue;

			tmp.clear();
			for (char ch : inputString)
			{
				if (ch == ch0 || ch == ch1)
				{
					tmp.push_back(ch);
				}
			}

			//This string should be at least 2 chars long (ch0 & ch1 are present in tmp)
			bool validString = true;
			for (size_t i = 1; i < tmp.size(); ++i)
			{
				if (tmp[i - 1] == tmp[i])
				{
					validString = false;
					break;
				}
			}

			//Update maximum
			if (validString && tmp.size() > maxResult)
			{
				maxResult = tmp.size();
			}
		}
	}

	cout << maxResult;

	perf.PrintResult();
}