#pragma once
#include "Utils\Check.h"
#include "Utils\PerfTimer.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <iostream>

PerfTimer::PerfTimer()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	m_startTime = li.QuadPart;
}

double PerfTimer::GetMs() const
{
	LARGE_INTEGER currTime;
	QueryPerformanceCounter(&currTime);

	LARGE_INTEGER freq;
	_check(QueryPerformanceFrequency(&freq));

	double dtMcs = static_cast<double>(currTime.QuadPart - m_startTime) * 1000 / freq.QuadPart;
	return dtMcs;
}

double PerfTimer::GetMcs() const
{
	LARGE_INTEGER currTime;
	QueryPerformanceCounter(&currTime);

	LARGE_INTEGER freq;
	_check(QueryPerformanceFrequency(&freq));

	double dtMcs = static_cast<double>(currTime.QuadPart - m_startTime) * 1'000'000 / freq.QuadPart;
	return dtMcs;
}

void PerfTimer::PrintResult() const
{
	double mcs = GetMcs();
	std::cout << "Running time = " << mcs << " mcs\n";
}