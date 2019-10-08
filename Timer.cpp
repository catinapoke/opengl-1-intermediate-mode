#include "Timer.h"

Timer::Timer() :isWorking(false), time(0)
{
}

Timer::Timer(int _time) : isWorking(true), time(_time), timeSpent(0)
{
}

void Timer::SetTimer(int _time)
{
	if (_time <= 0)
		return;
	isWorking = true;
	timeSpent = 0;
	time = _time;
}

bool Timer::EstimateTime(int _time)
{
	if (!isWorking)
		return false;
	timeSpent += _time;
	if (time <= timeSpent)
	{
		isWorking = false;
		time = 0;
		return true;
	}
	return false;
}

bool Timer::isActive()
{
	return isWorking;
}

float Timer::EstimatedPart()
{
	if (!isWorking || timeSpent > time)
		return 1.0f;

	float percent = (timeSpent * 1.0 / time);
	printf("=> %d : %d \n", timeSpent, time);
	printf("%f\n", percent);
	return percent;
}