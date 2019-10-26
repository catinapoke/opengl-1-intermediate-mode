#include "Lerp.h"

vec3 Lerp::Vec3(vec3 a, vec3 b, float percent)
{
	return vec3(Float(a.x, b.x, percent), Float(a.y, b.y, percent), Float(a.z, b.z, percent));
}

float Lerp::Float(float a, float b, float percent)
{
	return (1.0 - percent) * a + b * percent;
}

GLfloat Lerp::Number(GLfloat a, GLfloat b, float percent)
{
	if (a > b)
		return a - (a - b) * percent;
	else
		return a + (b - a) * percent;
}