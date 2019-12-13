#pragma once
#include "GameObject.h"

class Bomb : public GameObject
{
public:
	Bomb();
	Bomb(ivec2 position, GameObjectType type);
	~Bomb();
	void Update(int milliseconds);
	void SetCallbackExplodeEvent(void (*event)(Bomb* bomb));
	float GetFuseRate();
	static int fuseTime;
private:
	void Explode();
	int currentFuse;
	void (*ExplodeEvent)(Bomb* thisBomb);
};