#include "Bomb.h"

int Bomb::fuseTime = 5000;

Bomb::Bomb():currentFuse(fuseTime)
{
	
}

Bomb::Bomb(ivec2 position, GameObjectType type):GameObject(position, type), currentFuse(fuseTime)
{
}

Bomb::~Bomb()
{
	glm::ivec2 pos = this->getPosition();
	printf("Bomb exploded in position %i %i", pos.x, pos.y);
}

void Bomb::Update(int milliseconds)
{
	currentFuse -= milliseconds;
	if (currentFuse <= 0)
	{
		Explode();
		currentFuse = 0;
	}
	//printf("Fuse is %i\n Rate is %f\n", currentFuse, GetFuseRate());
}

void Bomb::SetCallbackExplodeEvent(void(*eventMethod)(Bomb* bomb))
{
	ExplodeEvent = eventMethod;
}

float Bomb::GetFuseRate()
{
	float rate = (currentFuse * 1.0f) / fuseTime;
	return rate;
}

void Bomb::Explode()
{
	ExplodeEvent(this);
}