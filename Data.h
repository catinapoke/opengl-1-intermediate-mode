#pragma once
#include <string>
#include "basicOpengl.h"
#include "Mesh.h"
#include "GraphicObject.h"
#include "Light.h"
#include "Camera.h"
#include "GameObject.h"
#include "Time.h"
#include "FPSCounter.h"

// Window title
extern std::string TitleName;

extern const int mapSize;
extern int passabilityMap[21][21];

// Mesh and materials
extern Material materials[5];
extern Mesh  meshes[5];

// Game objects
extern GameObject* gameObjects[21][21];
extern GameObject* player;
extern GraphicObject planeGraphicObject;

extern MoveDirection GetDirection(ivec2 dir);

// Camera, light and other
extern Camera camera;
const int lightCount = 2;
extern Light light[lightCount];

// Time 
extern Time time;
extern FPSCounter counter;

// Data initialisation
void DataInit();