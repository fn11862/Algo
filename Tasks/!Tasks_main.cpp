#include "Utils\Misc.h"
#include <exception>
#include <iostream>

void t001();

void main()
try
{
	StartMemLeakDetection();

	t001();
}
catch (std::exception& e)
{
	std::cout << "Exception: " << e.what() << '\n';
}