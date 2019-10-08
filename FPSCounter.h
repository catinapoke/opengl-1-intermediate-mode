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
	std::string title;
public:
	FPSCounter();
	FPSCounter(std::string TitleName);
	void Update(int _time);
	void AddFrame();
private:
	void UpdateFPS(int fps);
};