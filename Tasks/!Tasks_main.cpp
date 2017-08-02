#include "Utils\Misc.h"
#include "Utils\TestData.h"
#include <exception>
#include <iostream>


//#TODO: "t001" is taken 3 times in this file, each time I need to change it. 
// Is there a better solution?

void t001(unsigned run);

void main()
try
{
	StartMemLeakDetection();

	for (unsigned run = 0; run < 10; ++run)
	{
		const auto inputData = GetTestCasePath("t001", run, true);
		if (!IsFileExists(inputData.c_str()))
		{
			break;
		}

		t001(run);
	}
}

catch (std::exception& e)
{
	std::cout << "Exception: " << e.what() << '\n';
}