#pragma once
#include <windows.h>
#include <stdio.h>
#include <exception>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"
using namespace glm;
// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ОДНОГО ГРАФИЧЕСКОГО ОБЪЕКТА
class GraphicObject {
public:// Конструктор по умолчанию
	GraphicObject();
	GraphicObject(vec3& _position, float _angle, vec3& _color);
	// Установка и получение позиции объекта
	void setPosition(vec3& position);// Установка и получения угла поворота в градусах
	vec3 getPosition();// поворот осуществляется в горизонтальной плоскости вокруг оси Y по часовой стрелке

	void setAngle(float grad);
	float getAngle();// Установка текущего цвета объекта
	void setСolor(vec3& color);
	vec3 getColor();// Вывести объект на экран (матрица камеры уже должна быть установлена)
	void draw();
private:// Позиция объекта в глобальной системе координат
	vec3 position;// Угол поворота в горизонтальной плоскости (в градусах)
	float angle;// Цвет моделиvec3color;// Матрица модели (расположение объекта) ‐ чтоб не вычислять каждый раз
	vec3 color;
	mat4 modelMatrix;
	//GLfloat modelMatrix[16];
private:// расчет матрицы modelMatrix на основе position и angle
	void recalculateModelMatrix();
};