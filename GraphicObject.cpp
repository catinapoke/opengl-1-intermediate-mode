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

GraphicObject::GraphicObject(vec3& _position, float _angle, vec3& _color, Material* material) : GraphicObject(_position, _angle, _color)
{
	this->material = new Material(material);
}
GraphicObject::GraphicObject(vec3& _position, float _angle, vec3& _color, Material* material, Mesh* mesh) : GraphicObject(_position, _angle, _color, material)
{
	this->mesh = new Mesh(mesh);
}

void GraphicObject::setPosition(vec3& _position)
{
	position = _position;
	recalculateModelMatrix();
};

vec3 GraphicObject::getPosition()
{
	return position;
};

void GraphicObject::setMaterial(Material* material)
{
	this->material = new Material(material);
}

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
	glPushMatrix();
	glColor3fv(value_ptr(color));
	glMultMatrixf(glm::value_ptr(modelMatrix));

	if (material != nullptr)
	{
		material->apply();
	}

	if (mesh != nullptr)
	{
		mesh->draw();
	}
	else
		glutSolidSphere(1, 50, 50);

	glPopMatrix();
};

void GraphicObject::recalculateModelMatrix()
{
	modelMatrix = glm::translate(mat4(1), position) * glm::rotate(mat4(1), glm::radians(angle), vec3(0, 1, 0));
};