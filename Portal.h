#pragma once
#include "GameObject.h"

class Portal : public GameObject
{
public:
	std::shared_ptr<Portal> nextPortal = nullptr;
	Portal();
	Portal(ivec2 pos, GameObjectType type);
};