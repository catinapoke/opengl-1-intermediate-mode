#include "PathFinder.h"

PathFinder::PathFinder()
{
	// Default set of possible moves
	moves =
	{
		// x y
		ivec2(0,1),		// up
		ivec2(1,0),		// right
		ivec2(0,-1),	// down
		ivec2(-1,0)		// left
	};
}

std::vector<ivec2> PathFinder::moves =
{
	// x y
	ivec2(0,1),		// up
	ivec2(1,0),		// right
	ivec2(0,-1),	// down
	ivec2(-1,0)		// left
};

std::vector<ivec2> PathFinder::visited;
std::vector<ivec2> PathFinder::path;
int PathFinder::wave[21][21];

PathFinder::PathFinder(const std::vector<ivec2>& moves)
{
	this->moves = moves;
}

void PathFinder::clearWave()
{
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 21; j++)
			wave[i][j] = -1;
}


bool PathFinder::isVisited(ivec2 cur)
{
	for (auto it : visited)
		if (it == cur)
			return true;
	return false;
}

bool PathFinder::pointIsValid(ivec2 pos)
{
	return gameObjects[pos.x][pos.y] == nullptr || gameObjects[pos.x][pos.y]->GetType() == GameObjectType::MAIN_HERO_OBJECT || gameObjects[pos.x][pos.y]->GetType() == GameObjectType::MONSTER_OBJECT;
}

bool PathFinder::propagateWave(ivec2 start, ivec2 end)
{
	std::queue<ivec2> q;
	q.push(start);
	// When start or end isn't empty cell
	// We can't find the path
	if (!(pointIsValid(start)) || !(pointIsValid(end))) // (gameObjects[start.x][start.y] != nullptr && gameObjects[start.x][start.y]->GetType() != GameObjectType::MAIN_HERO_OBJECT) || (gameObjects[end.x][end.y] != nullptr && gameObjects[start.x][start.y]->GetType() != GameObjectType::MAIN_HERO_OBJECT))
		return false;

	if (end == start)
		return false;

	// Wave source
	wave[start.x][start.y] = 0;

	// Propagate wave
	while (!q.empty())
	{
		ivec2 cur = q.front();
		q.pop();

		if (isVisited(cur))
			continue;
		visited.push_back(cur);

		// If we find end point - propagation will stop
		if (cur == end)
			break;
		// Go through possible moves
		for (auto move : moves)
		{
			int x = cur.x + move.x,
				y = cur.y + move.y;
			// When cell is not visited and it is empty cell
			if (y >= 0 && y < 21 && x >= 0 && x < 21 && gameObjects[x][y] == nullptr && !isVisited(ivec2(x, y)))
			{
				// Add to queue and set the cost
				q.push(ivec2(x, y));
				wave[x][y] = wave[cur.x][cur.y] + 1;
			}
		}
	}
	return true; // wave was propagated
}

std::vector<ivec2> PathFinder::findPath(ivec2 start, ivec2 end)
{
	clearWave();
	path.clear();
	visited.clear();
	// If wave was not propagated
	// then there are no possible paths
	printf("Wave is in a process\n");
	if (!propagateWave(start, end))
		return path;
	printf("Wave has done\n");
	ivec2 cur = end;
	// If end was not reached, move to nearest
	if (wave[end.x][end.y] < 0)
	{
		ivec2 min = start;
		ivec2 dif = end - min;
		float distance = sqrt((float)dif.x * dif.x + (float)dif.y * dif.y); // euclidean distance
		for (int i = 0; i < 21; i++)
		{
			for (int j = 0; j < 21; j++)
				if (wave[i][j] >= 0)
				{
					ivec2 cur = ivec2(j, i);
					dif = end - cur;
					float curDistance = sqrt((float)dif.x * dif.x + (float)dif.y * dif.y);
					if (distance > curDistance)
					{
						distance = curDistance;
						min = cur;
					}
				}
		}
		cur = min;
	}

	if (start == cur)
		return path;

	path.push_back(cur);
	while (cur != start)
	{
		ivec2 pathBack = path.back();
		for (auto move : moves)
		{
			int x = cur.x + move.x,
				y = cur.y + move.y;
			printf("Tryin to find next step\n");
			// Find a cell with cost = cur.cost - 1
			if (y >= 0 && y < 21 && x >= 0 && x < 21 && wave[x][y] == (wave[cur.x][cur.y] - 1) && wave[x][y] != -1)
			{
				cur = ivec2(x, y);
				path.push_back(cur);
				printf("Found a next step\n");
				break;
			}
		}
		if (pathBack == path.back())
		{
			printf("Gay shit here\n");
			return path;
		}			
	}
		
	reverse(path.begin(), path.end());
	return path;
}