#pragma once
#include "basicOpengl.h"
using namespace glm;
// ����� ��� ������ � �������
class Camera
{
public:
	// ������������
	Camera(vec2 _speed = vec2(180.0f, 1.0f));
	Camera(vec3 position, vec2 _speed = vec2(180.0f, 1.0f));
	Camera(float x, float y, float z, float degrees = 180.0f, float zoom = 1.0f);

	// ���������� � ��������� ������� ������
	void setPosition(vec3 position);
	vec3 getPosition();

	// ������� ��� ����������� ������
	void rotateLeftRight(float miliseconds = 1000);
	void rotateUpDown(float miliseconds = 1000);
	void zoomInOut(bool closer);

	// ������� ��� ��������� ������� ������
	void apply();
private:
	// ����������� ���� ������
	vec3 degree; // (horizontal, vertical, radius)
	vec3 position; // (x, y, z)
	vec2 speed; // speed.x - radians, speed.y - zoom
private:
	vec3 cartesianToSpherical(vec3 decartes);
	vec3 sphericalToCartesian(vec3 polar);
	// �������������� ��������������� ������ ������
};