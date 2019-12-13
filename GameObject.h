#pragma once
#include "basicOpengl.h"
#include "GraphicObject.h"
#include "Lerp.h"
using ivec2 = glm::ivec2;
using vec3 = glm::vec3;

enum class MoveDirection
{
	stop, left, right, up, down
};

enum class GameObjectType
{
	LIGHT_OBJECT = 0,
	HEAVY_OBJECT = 1,
	BORDER_OBJECT,
	MAIN_HERO_OBJECT,
	PORTAL_1_OBJECT,
	PORTAL_2_OBJECT,
	MONSTER_OBJECT,
	BOMB_OBJECT,
	MAX_OBJECT_COUNT
};

class GameObject
{
public:
	GameObject();
	GameObject(ivec2 position, GameObjectType type);
	virtual ~GameObject() {};

	// Copy graphicObject
	void setGraphicObject(const GraphicObject& graphicObject);

	// Set position
	void setPosition(int x, int y);
	void setPosition(ivec2 position);
	void Rotate(int deltaDegree);

	// Get position
	ivec2 getPosition(); // Logical position
	vec3 GetGraphicPosition();

	// Game object type
	GameObjectType GetType();

	// Move in particular direction
	void move(MoveDirection direction, float speed = 3.0f);
	bool isMoving();
	bool isTransparent();

	// Object simulation
	virtual void update(float sec);
	void draw(void);

	void SetOnStopCallback(void (*callbackFunction)(GameObject*, ivec2));
	void UnsetOnStopCallback();

protected:
	ivec2 position;
	ivec2 destination;
	float progress;
	float speed;
	MoveDirection condition;

	GameObjectType objectType;
	GraphicObject graphicObject;
	void (*OnObjectStop)(GameObject*, ivec2) = nullptr;

	vec3 graphicPositionToGame(ivec2 pos);
};