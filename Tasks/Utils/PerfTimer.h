#pragma once

class PerfTimer
{
public:
	PerfTimer();

	double GetMs() const;  //Milliseconds (1/1.000)
	double GetMcs() const; //Microseconds (1/1.000.000)

	void PrintResult() const;

private:
	__int64 m_startTime;
};