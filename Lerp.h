#pragma 
#include <windows.h>
#include "basicOpengl.h"
using vec3 = glm::vec3;
struct Lerp
{
	static vec3 Vec3(vec3 a, vec3 b, float percent); // Lerp for vec3
	static float Float(float a, float b, float percent); // Optimised lerp
	static GLfloat Number(GLfloat a, GLfloat b, float percent); // Old lerp method
};