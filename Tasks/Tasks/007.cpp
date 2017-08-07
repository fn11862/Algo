#include "Headers.h"
#include <algorithm>

// https://www.hackerrank.com/challenges/queries-with-fixed-length/problem

namespace {

	unsigned findMaxOnRange(unsigned d, const unsigned* data)
	{
		unsigned maximum = 0;
		for (unsigned i = 0; i < d; ++i)
		{
			maximum = std::max(maximum, *(data + i));
		}
		return maximum;
	}

	unsigned solve(unsigned d, const std::vector<unsigned>& data)
	{
		unsigned rangeMax = findMaxOnRange(d, &data[0]);

		unsigned minimum = rangeMax;

		for (int i = 1; i <= data.size() - d; ++i)
		{
			//Leaving element is the maximum. Recalculate entire range
			if (data[i - 1] == rangeMax)
			{
				rangeMax = findMaxOnRange(d, &data[i]);
			}
			
			//Update for new element
			rangeMax = std::max(rangeMax, data[i + d - 1]);

			minimum = std::min(rangeMax, minimum);
		}

		return minimum;
	}

} // unnamed namespace


void t007(unsigned run)
{
	FileTestData cin (__FUNCTION__, run);
	Result       cout(__FUNCTION__, run);
	PerfTimer    perf;

	unsigned N, Q;
	cin >> N >> Q;
	std::vector<unsigned> data(N);
	for (unsigned i = 0; i < N; ++i)
	{
		cin >> data[i];
	}

	for (unsigned q = 0; q < Q; ++q)
	{
		unsigned d;
		cin >> d;
		unsigned minimum = solve(d, data);
		cout << minimum << '\n';
	}

	perf.PrintResult();
}