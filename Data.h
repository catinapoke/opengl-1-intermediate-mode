#pragma once
#include <string>
#include <memory>
#include <algorithm>
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */
#include "basicOpengl.h"
#include "IL\il.h"
#include "IL\ilu.h"
#include "IL\ilut.h"
#include "Mesh.h"
#include "Texture.h"
#include "GraphicObject.h"
#include "Light.h"
#include "Camera.h"
#include "GameObject.h"
#include "Time.h"
#include "FPSCounter.h"
#include "GameObjectFactory.h"
#include "Portal.h"
#include "Bomb.h"
#include "Sprite.h"
#include "Simulation.h"
//#include "Monster.h"


class GameObjectFactory;
class PathFinder;

// Window title
extern std::string TitleName;
extern std::string fpsString;
extern std::string multisamplingString;
extern std::string filterMode;
extern bool multisampling;

extern void UpdateTitle();

// Sprites
extern Sprite studentSign;
extern Sprite bombIcon;
extern Sprite bombBar;

extern const int mapSize;
extern int passabilityMap[21][21];

// Mesh and materials
//extern Material materials[5];
//extern Mesh  meshes[5];
//extern Texture planeTexture;
extern void HandleNewPortal(std::shared_ptr<Portal> currentPortal, std::vector<std::shared_ptr<Portal>>& portalVector);
GameObjectType ParseObjectType(std::string typeName);

// Game objects
extern std::shared_ptr<GameObject> gameObjects[21][21];
extern std::vector<std::shared_ptr<GameObject>> transparent;
extern std::shared_ptr<GameObject> player;
extern GameObjectFactory gameObjectFactory;
extern GraphicObject planeGraphicObject;
extern std::shared_ptr<Bomb> currentBomb;

extern MoveDirection GetDirection(ivec2 dir);
extern ivec2 GetRandomEmptyPos();

// Camera, light and other
extern Camera camera;
const int lightCount = 2;
extern Light light[lightCount];

// Time
extern Time framesTime;
extern FPSCounter counter;

// Data initialisation
void DataInit();