#include "Camera.h"

vec3 Camera::cartesianToSpherical(vec3 cartesian)
{
	vec3 polar;
	if (cartesian.z == 0)
	{
		if (cartesian.x > 0)
			polar.x = 1.570796;// 90 deg = 1.570796 rad
		else
			polar.x = 4.712389;// 270 degree
	}
	else
		polar.x = atan(cartesian.x / cartesian.z);

	double OM = sqrt(cartesian.x * cartesian.x + cartesian.z * cartesian.z);

	if (OM == 0)
	{
		if (cartesian.y > 0)
			polar.y = 1.570796;// 90 deg = 1.570796 rad
		else
			polar.y = 4.712389;// 270 degree
	}
	else
		polar.y = atan(cartesian.y / OM);

	polar.z = sqrt(cartesian.y * cartesian.y + OM * OM);

	return polar;
}

vec3 Camera::sphericalToCartesian(vec3 polar)
{
	vec3 cartesian;
	cartesian.y = polar.z * sin(polar.y);
	float OM = polar.z * cos(polar.y);
	cartesian.z = OM * cos(polar.x);
	cartesian.x = OM * sin(polar.x);
	return cartesian;
}

Camera::Camera(vec2 _speed) :Camera(vec3(0), _speed)
{
}

Camera::Camera(vec3 position, vec2 _speed)
{
	setPosition(position);
	speed = _speed;
	speed.x = radians(speed.x);
}

Camera::Camera(float x, float y, float z, float degrees, float zoom) : Camera(vec3(x, y, z), vec2(degrees, zoom))
{
}

void Camera::setPosition(vec3 _position)
{
	position = _position;
	degree = cartesianToSpherical(position);
}

vec3 Camera::getPosition()
{
	return position;
}

void Camera::rotateLeftRight(float miliseconds)
{
	degree.x += (miliseconds / 1000) * speed.x;
	float radian360 = 6.283185; // 360 degrees = 6.283185 radians
	if (degree.x > radian360)
		degree.x -= radian360;
	else if (degree.x < 0)
		degree.x += radian360;

	position = sphericalToCartesian(degree);
}

void Camera::rotateUpDown(float miliseconds)
{
	degree.y += (miliseconds / 1000) * speed.x;
	float radian85 = 1.48353;
	if (degree.y > radian85)
		degree.y = radian85;
	else
	{
		float radian5 = 0.087266;// 5 degrees = 0.087266 radians
		if (degree.y < radian5)
			degree.y = radian5;
	}

	position = sphericalToCartesian(degree);
}

void Camera::zoomInOut(bool closer)
{
	degree.z += (closer ? -1 : 1) * speed.y;

	if (degree.z < 1)
		degree.z = 1;
	else if (degree.z > 50)
		degree.z = 50;

	position = sphericalToCartesian(degree);
}

void Camera::apply()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position.x, position.y, position.z, 0, 0, 0, 0, 1, 0);
}