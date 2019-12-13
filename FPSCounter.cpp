#include "FPSCounter.h"

FPSCounter::FPSCounter(void (*_updateFps)(), std::string& _fpsStr) : time(0), frames(0), updateFps(_updateFps), fpsStr(_fpsStr)
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
	char* buffer = new char[10];
	_itoa_s(fps, buffer, 10, 10);
	fpsStr = "[" + std::string(buffer) + "] FPS";
	updateFps();
}