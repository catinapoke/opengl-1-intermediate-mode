#pragma once
#include "basicOpengl.h"
#include "GraphicObject.h"
#include "Lerp.h"
using ivec2 = glm::ivec2;
using vec3 = glm::vec3;

// класс‐перечисление для указания направления перемещения
enum class MoveDirection
{
	stop, left, right, up, down
};

// КЛАСС ДЛЯ ПРЕДСТАВЛЕНИЯ ИГРОВОГО ОБЪЕКТА
class GameObject
{
public:
	enum class Type
	{
		LightCube,
		HeavyCube,
		Border,
		Player,
		Empty
	};
	// конструктор
	GameObject(Type type = Type::Empty);

	GameObject(ivec2 position, Type type);

	// установка используемого графического объекта
	// происходит копирование переданного объекта для последующего использования
	void setGraphicObject(const GraphicObject& graphicObject);

	// установка логических координат
	// (два перегруженных метода для удобства)
	void setPosition(int x, int y);
	void setPosition(ivec2 position);

	// получение текущих логических координат
	ivec2 getPosition();
	vec3 GetGraphicPosition();

	Type GetType();

	// начать движение в выбранном направлении с указанной скоростью (клеток в секунду)
	void move(MoveDirection direction, float speed = 3.0f);
	// проверка на то, что объект движется
	bool isMoving();// симуляция игрового объекта (перемещение при необходимости)
	// метод вызывается непрерывно в функции simulation
	void update(float sec);

	

	// вывод игрового объекта на экран
	void draw(void);

private:
	// логические координаты игрового объекта
	ivec2 position;
	ivec2 destination;
	// состояние объекта (заданное направление перемещения)
	MoveDirection condition;
	// прогресс в перемещении (от 0.0 до 1.0)
	float progress;
	// скорость перемещения
	float speed;
	GameObject::Type objectType;

	// графический объект (для вывода на экран)
	GraphicObject graphicObject;

	vec3 graphicPositionToGame(ivec2 pos);
};