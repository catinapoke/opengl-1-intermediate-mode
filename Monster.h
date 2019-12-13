#pragma once
#include "PathFinder.h"
#include "GameObject.h"

class Monster : public GameObject
{
public:
	Monster();
	Monster(ivec2 position, std::pair<ivec2, ivec2> points);
	void update(float sec);
	
private:
	void SetUpNewPath();
	void ContinuePath();
	std::vector<ivec2> path;
	int currentPathPoint;
	std::pair<ivec2, ivec2> pointsPair;
};