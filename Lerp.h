#pragma
#include <windows.h>
#include "basicOpengl.h"
using vec3 = glm::vec3;
struct Lerp
{
	static vec3 Vec3(vec3 a, vec3 b, float percent);
	static float Float(float a, float b, float percent);
	static GLfloat Number(GLfloat a, GLfloat b, float percent);
};