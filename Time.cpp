#include "Time.h"

Time::Time()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&time_start);
}

void Time::Reset()
{
	QueryPerformanceCounter(&time_start);
}

int Time::ElapsedMiliseconds()
{
	LARGE_INTEGER time_end;
	QueryPerformanceCounter(&time_end);
	int msElapsed = ((time_end.QuadPart - time_start.QuadPart) * 1000 / frequency.QuadPart);
	time_start = time_end;
	return msElapsed;
}