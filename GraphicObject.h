#pragma once
#include "basicOpengl.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"
using vec3 = glm::vec3;
using vec4 = glm::vec4;
using mat4 = glm::mat4;

// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ОДНОГО ГРАФИЧЕСКОГО ОБЪЕКТА
class GraphicObject {
public:// Конструктор по умолчанию
	GraphicObject();
	GraphicObject(vec3& _position, float _angle, vec3& _color);
	GraphicObject(vec3& _position, float _angle, vec3& _color, Material* material);
	GraphicObject(vec3& _position, float _angle, vec3& _color, Material* material, Mesh* mesh);
	GraphicObject(Material* material, Mesh* mesh);
	// Установка и получение позиции объекта
	void setPosition(vec3& position);// Установка и получения угла поворота в градусах
	vec3 getPosition();// поворот осуществляется в горизонтальной плоскости вокруг оси Y по часовой стрелке

	// Установка используемого материала
	void setMaterial(Material* material);

	void setAngle(float grad);
	float getAngle();// Установка текущего цвета объекта

	void setСolor(vec3& color);
	vec3 getColor();// Вывести объект на экран (матрица камеры уже должна быть установлена)

	bool isTransparent();
	void draw();
private:// Позиция объекта в глобальной системе координат
	vec3 position;// Угол поворота в горизонтальной плоскости (в градусах)
	float angle;
	vec3 color; // Цвет модели
	mat4 modelMatrix; // Матрица модели (расположение объекта) ‐ чтоб не вычислять каждый раз
	Material* material;
	Mesh* mesh;
	//GLfloat modelMatrix[16];
private:// расчет матрицы modelMatrix на основе position и angle
	void recalculateModelMatrix();
};