#pragma once
#include "basicOpengl.h"
using namespace glm;

class Camera
{
public:
	// Constructors
	Camera(vec2 _speed = vec2(180.0f, 1.0f));
	Camera(vec3 position, vec2 _speed = vec2(180.0f, 1.0f));
	Camera(float x, float y, float z, float degrees = 180.0f, float zoom = 1.0f);

	// Position
	void setPosition(vec3 position);
	vec3 getPosition();

	// Camera moving 
	void rotateLeftRight(float miliseconds = 1000);
	void rotateUpDown(float miliseconds = 1000);
	void zoomInOut(bool closer);

	// Apply camera
	void apply();
private:
	// Transform
	vec3 degree; // (horizontal, vertical, radius)
	vec3 position; // (x, y, z)
	vec2 speed; // speed.x - radians, speed.y - zoom

private: 
	// Convert methods
	vec3 cartesianToSpherical(vec3 decartes);
	vec3 sphericalToCartesian(vec3 polar);
};