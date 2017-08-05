#include "Headers.h"

// https://www.hackerrank.com/challenges/bitset-1/problem

//Fastest algorithm because of memory zeroing by vector<bool> constructor
void t003(unsigned run)
{
	FileTestData cin (__FUNCTION__, run);
	Result       cout(__FUNCTION__, run);
	PerfTimer    perf;

	int N, S, P, Q;
	cin >> N >> S >> P >> Q;

	const int64_t mask = 0x7FFFFFFF;

	std::vector<bool> values(mask + 1, false);
	perf.PrintResult();
	perf.Reset();

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


//Works slower because all memory zeroing implementations take longer, than vector<bool>'s ctor
//But the HR's task is about bit manipulation
void t003_manual_bit_manipulation(unsigned run)
{
	FileTestData cin (__FUNCTION__, run);
	Result       cout(__FUNCTION__, run);
	PerfTimer    perf;

	int N, S, P, Q;
	cin >> N >> S >> P >> Q;

	const int64_t mask = 0x7FFFFFFF;

	std::unique_ptr<unsigned[]> spData{ std::make_unique<unsigned[]>(1 << 26) };

	memset(spData.get(), 0, 1 << 28);  //Slowest implementation

//Optimization1: use loop: it is faster than memset(): 0.24 vs 0.26 sec on average
// 	for (int i = 0; i < 1 << 26; ++i)
// 	{
// 		spData[i] = 0;
// 	}

//Optimization2 (for x64): 2%: use rxx-registers
// 	int64_t* pData = (int64_t*)spData.get();
// 	for (int i = 0; i < 1 << 25; ++i)
// 	{
// 		*(pData+i) = 0;
// 	}

	perf.PrintResult();
	perf.Reset();

	int64_t a = S & mask;
	unsigned uint = static_cast<unsigned>(a / 32);
	unsigned uintMask = 1 << (a & 0x3FF);
	spData[uint] |= uintMask;

	int count = 1;

	for (int i = 1; i < N; ++i)
	{
		a = (a*P + Q) & mask;
		uint = static_cast<unsigned>(a / 32);
		uintMask = 1 << (a & 0x3FF);
		if (spData[uint] & uintMask)
			break;

		spData[uint] |= uintMask;
		++count;
	}

	cout << count;

	perf.PrintResult();
}