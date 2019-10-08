#pragma once
#include <windows.h>
class Time {
	LARGE_INTEGER time_start;
	LARGE_INTEGER frequency;
public:
	Time();
	void Reset();
	int ElapsedMiliseconds();
};