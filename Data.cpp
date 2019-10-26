#pragma once
#include "Data.h"

std::string TitleName = "Algorithms of processing computer graphics";

const int mapSize = 21;

// 0 - Empty cell
// 1 - Light object
// 2 - Heavy object
// 3 - Border object
// 4 - Player

int passabilityMap[21][21] = {
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
  3,4,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,3,
  3,0,2,1,2,0,2,0,2,2,2,1,2,0,2,0,2,0,2,2,3,
  3,0,2,0,2,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,3,
  3,0,1,0,2,2,1,2,2,0,2,0,2,2,2,1,2,0,2,0,3,
  3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,3,
  3,0,2,2,1,1,2,0,2,0,2,2,2,2,2,0,2,2,2,0,3,
  3,0,2,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,0,0,3,
  3,0,2,0,2,2,2,0,2,0,2,2,1,2,2,2,1,2,2,0,3,
  3,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,0,0,1,0,3,
  3,2,2,2,2,0,2,2,2,0,2,0,2,2,2,2,2,2,2,0,3,
  3,0,0,0,2,0,0,0,1,0,2,0,0,0,2,0,0,0,0,0,3,
  3,0,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,2,2,2,3,
  3,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,3,
  3,2,2,2,2,0,2,2,2,0,2,2,2,0,1,0,2,2,2,0,3,
  3,0,0,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,2,0,3,
  3,0,2,0,2,1,2,0,2,0,2,2,2,0,2,2,2,0,2,0,3,
  3,0,1,0,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,3,
  3,0,2,1,2,0,2,2,2,2,2,0,2,0,2,0,2,2,2,2,3,
  3,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,3,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
};

// Mesh and materials
Material materials[5];
Mesh meshes[5];

// Game objects
GameObject* gameObjects[21][21];
GameObject* player;
GraphicObject planeGraphicObject;

MoveDirection GetDirection(ivec2 dir)
{
	if (dir.x > 0)
		return MoveDirection::right;
	else if (dir.x < 0)
		return MoveDirection::left;
	else if (dir.y > 0)
		return MoveDirection::up;
	else if (dir.y < 0)
		return MoveDirection::down;
}

// Camera, light and other
Camera camera;
Light light[lightCount];

// Time 
Time time;
FPSCounter counter;

// Data initialisation
void dataInit()
{
	camera = Camera(15, 15, 10);
	light[0] = Light("material/light.json");
	light[1] = Light("material/light_1.json");

	materials[0] = Material("material/material_2.json"); // Light object
	materials[1] = Material("material/material_1.json"); // Heavy object
	materials[2] = Material("material/material_3.json"); // Border
	materials[3] = Material("material/material_4.json"); // Player
	materials[4] = Material("material/material_5.json"); // Floor

	meshes[0] = Mesh("meshes/Box.obj");
	meshes[1] = Mesh("meshes/ChamferBox.obj");
	meshes[2] = Mesh("meshes/simple_plane.obj");
	meshes[3] = Mesh("meshes/Sphere.obj");

	GraphicObject* graphicObjects = new GraphicObject[5];
	graphicObjects[0] = GraphicObject(vec3(0), 0, vec3(0), &materials[0], &meshes[1]); // Light cube
	graphicObjects[1] = GraphicObject(vec3(0), 0, vec3(0), &materials[1], &meshes[1]); // Heavy cube
	graphicObjects[2] = GraphicObject(vec3(0), 0, vec3(0), &materials[2], &meshes[0]); // Dark cube
	graphicObjects[3] = GraphicObject(vec3(0), 0, vec3(0), &materials[4], &meshes[3]); // Player
	graphicObjects[4] = GraphicObject(vec3(0), 0, vec3(0), &materials[3], &meshes[2]); // plane

	planeGraphicObject = graphicObjects[4];

	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (passabilityMap[i][j] > 0 && passabilityMap[i][j] < 4) // 1, 2, 3
			{
				switch (passabilityMap[i][j])
				{
				case 1:
					gameObjects[i][j] = new GameObject(ivec2(i, j), GameObject::Type::LightCube);
					break;
				case 2:
					gameObjects[i][j] = new GameObject(ivec2(i, j), GameObject::Type::HeavyCube);
					break;
				default:
					gameObjects[i][j] = new GameObject(ivec2(i, j), GameObject::Type::Border);
					break;
				}
				gameObjects[i][j]->setGraphicObject(graphicObjects[passabilityMap[i][j] - 1]);
			}
			else if (passabilityMap[i][j] == 4)
			{
				player = new GameObject(ivec2(i, j), GameObject::Type::Player);
				player->setGraphicObject(graphicObjects[3]);
			}
		}
	}

	time = Time();
	counter = FPSCounter(TitleName);
}