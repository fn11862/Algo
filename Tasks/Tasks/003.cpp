#include "Headers.h"
#include <unordered_set>

// https://www.hackerrank.com/challenges/bitset-1/problem
//using std::cin;
//using std::cout;

void t003(unsigned run)
{
	FileTestData cin (__FUNCTION__, run);
	Result       cout(__FUNCTION__, run);
	PerfTimer    perf;

	int N, S, P, Q;
	cin >> N >> S >> P >> Q;

	const int64_t mask = 0x7FFFFFFF;

	std::vector<bool> values(mask, false);

	int64_t a = S & mask;
	values[(int)a] = true;
	int count = 1;
	for (int i = 1; i < N; ++i)
	{
		a = (a*P + Q) & mask;
		if (values[(int)a])
			break;

		values[(int)a] = true;
		++count;
	}

	cout << count;

	perf.PrintResult();
}