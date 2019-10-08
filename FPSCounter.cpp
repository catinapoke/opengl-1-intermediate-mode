#include "FPSCounter.h"
FPSCounter::FPSCounter() : FPSCounter("DefaultName")
{
}

FPSCounter::FPSCounter(std::string TitleName) : time(0), frames(0), title(TitleName)
{
}

void FPSCounter::Update(int _time)
{
	time += _time;
	if (time > 1000)
	{
		UpdateFPS(frames / (time / 1000));
		time = 0;
		frames = 0;
	}
}

void FPSCounter::AddFrame()
{
	frames++;
}

void FPSCounter::UpdateFPS(int fps)
{
	std::string _title;
	char* buffer = new char[10];
	_itoa_s(fps, buffer, 10, 10);
	_title = title + " [" + buffer + "] FPS";
	glutSetWindowTitle(_title.c_str());
}