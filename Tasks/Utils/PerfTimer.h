#pragma once

class PerfTimer
{
public:
	PerfTimer();

	double GetMs() const;  //Milliseconds (1/1.000)
	double GetMcs() const; //Microseconds (1/1.000.000)

	void PrintResult() const;
	void Reset();

private:
	__int64 m_startTime;
};