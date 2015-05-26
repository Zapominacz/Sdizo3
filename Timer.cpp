#pragma once
#include "stdafx.h"
#include "Timer.h"

Timer::Timer(void) {
	count = 0;
	cumulativeSum.QuadPart = 0;
}
Timer::~Timer(void) {

}
void Timer::startTimer(void) {
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&performanceCountStart);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
}
void Timer::stopTimer(void) {
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&performanceCountEnd);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
}

void Timer::nextMeasure(void) {
	cumulativeSum.QuadPart += performanceCountEnd.QuadPart - performanceCountStart.QuadPart;
	count++;
}

void Timer::printAvgTime(void) {
	using namespace std;
	double tm = cumulativeSum.QuadPart / (double) count;
	cout <<endl<<"Time:"<<tm <<endl;
}

double Timer::getAvgTime(void) {
	return cumulativeSum.QuadPart / (double)count;
}