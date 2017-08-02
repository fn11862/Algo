#include "Headers.h"
#include <queue>

//https://www.hackerrank.com/challenges/equal-stacks/problem
void t001(unsigned run)
{
	FileTestData cin (__FUNCTION__, run);
	Result       cout(__FUNCTION__, run);
	PerfTimer    perf;

	int sz0, sz1, sz2;
	cin >> sz0 >> sz1 >> sz2;

	int sum0 = 0, sum1 = 0, sum2 = 0;
	std::queue<int> q0, q1, q2;
	int tmp;
	for (int i = 0; i < sz0; ++i)
	{
		cin >> tmp;
		q0.push(tmp);
		sum0 += tmp;
	}
	for (int i = 0; i < sz1; ++i)
	{
		cin >> tmp;
		q1.push(tmp);
		sum1 += tmp;
	}

	for (int i = 0; i < sz2; ++i)
	{
		cin >> tmp;
		q2.push(tmp);
		sum2 += tmp;
	}

	while ((sum0 != sum1) || (sum1 != sum2))
	{
		if (sum0 > sum1)
		{
			sum0 -= q0.front();
			q0.pop();
		}
		if (sum0 < sum1)
		{
			sum1 -= q1.front();
			q1.pop();
		}
		if (sum0 > sum2)
		{
			sum0 -= q0.front();
			q0.pop();
		}
		if (sum0 < sum2)
		{
			sum2 -= q2.front();
			q2.pop();
		}
	}

	perf.PrintResult();
	cout << sum0;
}