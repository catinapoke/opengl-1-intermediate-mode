#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <string>
class FPSCounter
{
private:
	int frames;
	int time;
	void (*updateFps)();
	std::string& fpsStr;
public:
	// FPSCounter();
	FPSCounter(void (*updateFps)(), std::string& fpsStr);
	void Update(int _time);
	void AddFrame();
private:
	void UpdateFPS(int fps);
};