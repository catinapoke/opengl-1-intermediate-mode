#include "GameObject.h"

GameObject::GameObject(Type type): GameObject(ivec2(0.0f), type)
{
	condition = MoveDirection::stop;
	objectType = type;
}

GameObject::GameObject(ivec2 position, Type type) : progress(0.0f), speed(0.0f), destination(ivec2(0, 0))
{
	condition = MoveDirection::stop;
	objectType = type;
	setPosition(position);
}

void GameObject::setGraphicObject(const GraphicObject& _graphicObject)
{
	graphicObject = _graphicObject;
	graphicObject.setPosition(graphicPositionToGame(ivec2(position.x, position.y)));
}

void GameObject::setPosition(int x, int y)
{
	setPosition(ivec2(x, y));
}

void GameObject::setPosition(ivec2 position)
{
	if (position.x > 20)
		position.x = 20;
	else if (position.x < 0)
		position.x = 0;
	if (position.y > 20)
		position.y = 20;
	else if (position.y < 0)
		position.y = 0;
	this->position = position;
	graphicObject.setPosition(graphicPositionToGame(ivec2(position.x, position.y)));
}

ivec2 GameObject::getPosition()
{
	return position;
}

GameObject::Type GameObject::GetType()
{
	return objectType;
}

void GameObject::move(MoveDirection direction, float speed)
{
	if (isMoving())
		return;
	this->speed = speed;
	condition = direction;
	switch (condition) {
	case MoveDirection::up:
		destination = ivec2(position.x, position.y + 1);
		break;
	case MoveDirection::down:
		destination = ivec2(position.x, position.y - 1);
		break;
	case MoveDirection::right:
		destination = ivec2(position.x + 1, position.y);
		break;
	case MoveDirection::left:
		destination = ivec2(position.x - 1, position.y);
		break;
	default:
		throw std::exception("Undefined direction to move");
	}
	progress = 0.0f;
}

bool GameObject::isMoving()
{
	return condition!=MoveDirection::stop;
}

void GameObject::update(float sec)
{
	if (condition != MoveDirection::stop)
	{
		progress += speed * sec;
		if (progress > 1)
			progress = 1;
		graphicObject.setPosition(Lerp::Vec3(graphicPositionToGame(position), graphicPositionToGame(destination), progress));
		if (progress == 1)
		{
			condition = MoveDirection::stop;
			position = destination;
		}
	}
	
}

vec3 GameObject::GetGraphicPosition()
{
	return graphicObject.getPosition();
}

vec3 GameObject::graphicPositionToGame(ivec2 pos)
{
	return vec3(pos.x - 10.0f, 0.5, pos.y - 10.0f);
}

void GameObject::draw(void)
{
	graphicObject.draw();
}