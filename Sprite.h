#pragma once
#include <string>
#include "basicOpengl.h"
#include "IL\il.h"
#include "IL\ilu.h"
#include "IL\ilut.h"
class Sprite
{
public:
	Sprite();
	Sprite(std::string filename);
	void load(std::string filename);
	void draw(int x, int y);
	unsigned int GetWidth();
	unsigned int GetHeight();
private:
	GLuint spriteBufferId;
	unsigned int width;
	unsigned int height;
};