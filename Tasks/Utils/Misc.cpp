#include "Utils\Misc.h"

#define WIN32_LEAN_AND_MEAN
#include <crtdbg.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi")

bool Is64Bit()
{
	return sizeof(int*) == 8;
}

void StartMemLeakDetection()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
}

bool IsFileExists(const char* const pStr)
{
	return !!PathFileExistsA(pStr);
}