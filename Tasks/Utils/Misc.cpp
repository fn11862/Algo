#define WIN32_LEAN_AND_MEAN
#include <crtdbg.h>


void StartMemLeakDetection()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
}