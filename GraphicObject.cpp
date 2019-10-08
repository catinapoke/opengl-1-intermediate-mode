#pragma once
#include "GraphicObject.h"

GraphicObject::GraphicObject() :position(0), angle(0), color(0), modelMatrix(1)
{
};

GraphicObject::GraphicObject(vec3& _position, float _angle, vec3& _color = vec3(0)) : modelMatrix(1)
{
	position = _position;
	angle = _angle;
	color = _color;
	recalculateModelMatrix();
};

void GraphicObject::setPosition(vec3& _position)
{
	position = _position;
	recalculateModelMatrix();
};

vec3 GraphicObject::getPosition()
{
	return position;
};

void GraphicObject::setAngle(float grad)
{
	angle = grad;
	recalculateModelMatrix();
};

float GraphicObject::getAngle()
{
	return angle;
};

void GraphicObject::setСolor(vec3& _color)
{
	color = _color;
};

vec3 GraphicObject::getColor()
{
	return color;
};

void GraphicObject::draw()
{
	glPushMatrix();//кладем в стек
	glColor3fv(value_ptr(color));
	glMultMatrixf(value_ptr(modelMatrix));
	glutWireTeapot(1.0f);
	glPopMatrix();
};

void GraphicObject::recalculateModelMatrix()
{
	modelMatrix = translate(modelMatrix, position) * rotate(modelMatrix, radians(angle), vec3(0, 1, 0));
};