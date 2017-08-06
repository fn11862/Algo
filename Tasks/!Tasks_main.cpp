#include "Utils\Misc.h"
#include "Utils\TestData.h"
#include <exception>
#include <iostream>

#define TEST_CASE t006
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
//#TODO: replace macro with more elegant solution

void TEST_CASE(unsigned run);

void main()
try
{
	StartMemLeakDetection();

	for (unsigned run = 0; run < 50; ++run)
	{
		const auto inputData = GetTestCasePath(TOSTRING(TEST_CASE), run, true);
		if (IsFileExists(inputData.c_str()))
		{
			//Test cases might be in not continues order: 0, 5, 10 ...
			TEST_CASE(run);
		}
	}
}

catch (std::exception& e)
{
	std::cout << "Exception: " << e.what() << '\n';
}