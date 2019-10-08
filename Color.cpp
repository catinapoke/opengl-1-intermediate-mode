#include "Color.h"

Color::Color() :Color(0, 0, 0)
{
}

Color::Color(GLfloat _red, GLfloat _green, GLfloat _blue) : red(_red), green(_green), blue(_blue)
{
}

Color Color::Lerp(Color a, Color b, float percent)
{
	if (percent > 1)
		percent = 1;
	if (percent < 0)
		percent = 0;
	Color newColor(NumberLerp(a.red, b.red, percent), NumberLerp(a.green, b.green, percent), NumberLerp(a.blue, b.blue, percent));
	return newColor;
}

GLfloat Color::NumberLerp(GLfloat a, GLfloat b, float percent)
{
	if (a > b)
		return a - (a - b) * percent;
	else
		return a + (b - a) * percent;
}