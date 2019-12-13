#include "Monster.h"

//PathFinder Monster::finder;

Monster::Monster():GameObject()
{
	objectType = GameObjectType::MONSTER_OBJECT;
}

Monster::Monster(ivec2 position, std::pair<ivec2, ivec2> points):GameObject(position, GameObjectType::MONSTER_OBJECT), pointsPair(points)
{
	currentPathPoint = 0;
	path.clear();
}

void Monster::update(float sec)
{
	
	if (!isMoving() || path.empty())
		ContinuePath();
	else
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
				ivec2 previousPos = position;
				position = destination;
				if (OnObjectStop != nullptr)
					OnObjectStop(this, previousPos);
				ContinuePath();
			}
		}
	}
}

void Monster::SetUpNewPath()
{
	ivec2 nextPoint = GetRandomEmptyPos();
	path = PathFinder::findPath(position, nextPoint);
	currentPathPoint = 0;
	printf("Update monster path\n");
}

void Monster::ContinuePath()
{
	const auto IsValidMove = [](ivec2 pos) {return gameObjects[pos.x][pos.y] == nullptr || gameObjects[pos.x][pos.y]->GetType() == GameObjectType::MAIN_HERO_OBJECT; };
	//printf("Damn monster path tracing\n");
	currentPathPoint++;
	if (currentPathPoint > path.size() || path.empty())
	{
		SetUpNewPath();
		return;
	}

	ivec2 monsterPos = this->getPosition();
	int difference = path[currentPathPoint].x - monsterPos.x;
	if (difference == 0)
	{
		printf("Y is %i\n", difference);
		difference = path[currentPathPoint].y - monsterPos.y;
		if (abs(difference) != 1)
			return;
		if (difference == 1)
		{
			if(IsValidMove(ivec2(monsterPos.x, monsterPos.y + 1)))
				move(MoveDirection::up);
			else
			{
				SetUpNewPath();
				return;
			}
				
		}
		else if (difference == -1)
		{
			if (IsValidMove(ivec2(monsterPos.x, monsterPos.y - 1)))
				move(MoveDirection::down);
			else
			{
				SetUpNewPath();
				return;
			}
		}
	}
	else
	{
		if (abs(difference) != 1)
			return;
		printf("X is %i\n",difference);
		if (difference == 1)
		{
			if (IsValidMove(ivec2(monsterPos.x + 1, monsterPos.y)))
				move(MoveDirection::right);
			else
			{
				SetUpNewPath();
				return;
			}
		}
		else if (difference == -1)
		{
			if (IsValidMove(ivec2(monsterPos.x - 1, monsterPos.y)))
				move(MoveDirection::left);
			else
			{
				SetUpNewPath();
				return;
			}
		}
	}
}