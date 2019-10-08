#pragma once
#include <cstdio>
class Timer
{
	int time;
	int timeSpent{ 0 };
	bool isWorking;
public:
	Timer();
	Timer(int _time);
	void SetTimer(int _time);
	bool EstimateTime(int _time);
	bool isActive();
	float EstimatedPart();
};