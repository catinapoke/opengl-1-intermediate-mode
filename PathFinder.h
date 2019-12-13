#pragma once
#include <queue>
#include <vector>
#include <GLM/glm.hpp>
#include <memory>
#include "Data.h"
//#include "Data.h"
using glm::ivec2;
static class PathFinder
{
public:
	// Constructors
	PathFinder();
	PathFinder(const std::vector<ivec2>& moves);

	// Find shortest path using Lee algorithm
	static std::vector<ivec2> findPath(ivec2 start, ivec2 end);
	~PathFinder() = default;
private:
	// Clear wave
	static void clearWave();
	// Set costs
	static bool propagateWave(ivec2 start, ivec2 end);
	// Checks if cell visited
	static bool isVisited(ivec2 cur);

	static bool pointIsValid(ivec2 pos);

	static std::vector<ivec2> path;
	static std::vector<ivec2> visited;
	static std::vector<ivec2> moves; // set of moves
	static int wave[21][21];
};