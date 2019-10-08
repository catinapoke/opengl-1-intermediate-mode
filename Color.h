#pragma 
#include <windows.h>
#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/freeglut.h"
struct Color
{
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	Color();
	Color(GLfloat _red, GLfloat _green, GLfloat _blue);
	static Color Lerp(Color a, Color b, float percent);
private:
	static GLfloat NumberLerp(GLfloat a, GLfloat b, float percent);
};