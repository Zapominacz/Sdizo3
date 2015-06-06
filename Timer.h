#pragma once
#include "stdafx.h"
/** Klasa mierz�ca czasy wykonania algorytm�w*/
class Timer {
private:
	LARGE_INTEGER performanceCountStart;
	LARGE_INTEGER performanceCountEnd;
	LARGE_INTEGER cumulativeSum;
	int count;
	double freq;
	void setFreq();
public:
	Timer(void);
	~Timer(void);
	void startTimer(void);
	void stopTimer(void);
	void nextMeasure(void);
	void printAvgTime(void);
	double getAvgTime(void);
};