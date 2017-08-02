#pragma once

bool Is64Bit()
{
	return sizeof(int*) == 8;
}