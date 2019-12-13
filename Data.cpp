#pragma once
#include "Data.h"

std::string TitleName = "Algorithms of processing computer graphics";
std::string fpsString = "[0] FPS";
std::string multisamplingString = "MSAA [On]";
std::string filterMode = "1)Точечная фильтрация";
bool multisampling = false;

const int mapSize = 21;

// 0 - Empty cell
// 1 - Light object
// 2 - Heavy object
// 3 - Border object
// 4 - Player

int passabilityMap[21][21] = {
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
  3,4,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,5,3,
  3,0,2,1,2,0,2,0,2,2,2,1,2,0,2,0,2,0,2,2,3,
  3,0,2,6,2,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,3,
  3,7,1,0,2,2,1,2,2,0,2,0,2,2,2,1,2,0,2,0,3,
  3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,6,2,0,3,
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
  3,0,1,5,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,3,
  3,2,2,1,2,0,2,2,2,2,2,0,2,0,2,0,2,2,2,2,3,
  3,0,2,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,6,3,
  3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
};

// Sprites
Sprite studentSign;
Sprite bombIcon;
Sprite bombBar;

// Game objects
GameObjectFactory gameObjectFactory;
std::shared_ptr<GameObject> gameObjects[21][21];
std::vector<std::shared_ptr<GameObject>> transparent;
std::shared_ptr<GameObject> player;
GraphicObject planeGraphicObject;
std::shared_ptr<Bomb> currentBomb;

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
Time framesTime;
FPSCounter counter(UpdateTitle, fpsString);

void UpdateTitle()
{
	glutSetWindowTitle((TitleName + " " + fpsString + " " + multisamplingString + " " + filterMode).c_str());
}

// Data initialisation
void DataInit()
{
	srand(std::time(0));
	// инициализация библиотеки DevIL для загрузки изображений      
	ilInit();       
	iluInit(); 
	ilutInit();

	studentSign = Sprite("sprites/sign75.png");
	bombIcon = Sprite("sprites/Bomb.png");
	bombBar = Sprite("sprites/BombTick.tga");

	camera = Camera(15, 15, 10);
	light[0] = Light("material/light.json");
	light[1] = Light("material/light_1.json");

	//planeTexture = Texture("textures/plane.jpg");

	planeGraphicObject = GraphicObject(vec3(0), 0, vec3(0), new PhongMaterialWithTexture("material/simple_plane.json"), new Mesh("meshes/simple_plane.obj"));
	gameObjectFactory.init("scenes/scene.json");

	std::vector<std::shared_ptr<Portal>> portals_1;
	std::vector<std::shared_ptr<Portal>> portals_2;

	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			switch (passabilityMap[i][j] - 1) {
			case static_cast<int>(GameObjectType::LIGHT_OBJECT):		// 1
				gameObjects[i][j] = gameObjectFactory.create(GameObjectType::LIGHT_OBJECT, i, j);
				break;
			case static_cast<int>(GameObjectType::HEAVY_OBJECT):		// 2
				gameObjects[i][j] = gameObjectFactory.create(GameObjectType::HEAVY_OBJECT, i, j);
				break;
			case static_cast<int>(GameObjectType::BORDER_OBJECT):		// 3
				gameObjects[i][j] = gameObjectFactory.create(GameObjectType::BORDER_OBJECT, i, j);
				break;
			case static_cast<int>(GameObjectType::MAIN_HERO_OBJECT):	// 4
				player = gameObjectFactory.create(GameObjectType::MAIN_HERO_OBJECT, i, j);
				player->SetOnStopCallback(OnPlayerStop);
				break;
			case static_cast<int>(GameObjectType::PORTAL_1_OBJECT):		// 5
				gameObjects[i][j] = gameObjectFactory.create(GameObjectType::PORTAL_1_OBJECT, i, j);
				HandleNewPortal(std::dynamic_pointer_cast<Portal>(gameObjects[i][j]), portals_1);
				break;
			case static_cast<int>(GameObjectType::PORTAL_2_OBJECT):		// 6
				gameObjects[i][j] = gameObjectFactory.create(GameObjectType::PORTAL_2_OBJECT, i, j);
				HandleNewPortal(std::dynamic_pointer_cast<Portal>(gameObjects[i][j]), portals_2);
				break;
			case static_cast<int>(GameObjectType::MONSTER_OBJECT) :		// 6
				gameObjects[i][j] = gameObjectFactory.create(GameObjectType::MONSTER_OBJECT, i, j);
				gameObjects[i][j]->SetOnStopCallback(OnMonsterStop);
				break;
			default:
				gameObjects[i][j] = nullptr;
				break;
			}
			if (gameObjects[i][j]!=nullptr && gameObjects[i][j]->isTransparent())
				transparent.push_back(gameObjects[i][j]);
		}
	}

	portals_1.clear();
	portals_2.clear();
	framesTime = Time();
}

ivec2 GetRandomEmptyPos()
{
	int x = rand()%21, y = rand() % 21;
	while (gameObjects[x][y] != nullptr)
	{
		x = rand() % 21;
		y = rand() % 21;
	}
	return ivec2(x, y);
}

ivec2 GetPosByDirection(ivec2 currentPos, MoveDirection direction)
{
	if (direction == MoveDirection::stop)
		return currentPos;
	if (direction == MoveDirection::up)
		return ivec2(currentPos.x, currentPos.y + 1);
	else if (direction == MoveDirection::down)
		return ivec2(currentPos.x, currentPos.y - 1);
	else if (direction == MoveDirection::right)
		return ivec2(currentPos.x + 1, currentPos.y);
	else if(direction == MoveDirection::left)
		return ivec2(currentPos.x - 1, currentPos.y);
	return currentPos;
}

void HandleNewPortal(std::shared_ptr<Portal> currentPortal, std::vector<std::shared_ptr<Portal>> &portalVector)
{
	if (portalVector.size() == 0)
	{
		portalVector.push_back(currentPortal);
		return;
	}
	std::shared_ptr<Portal> backPortal = portalVector.back();
	backPortal->nextPortal = currentPortal;
	currentPortal->nextPortal = portalVector.front();
	portalVector.push_back(currentPortal);
}

GameObjectType ParseObjectType(std::string typeName)
{
	if (typeName == "LightObject")
		return GameObjectType::LIGHT_OBJECT;
	if (typeName == "HeavyObject")
		return GameObjectType::HEAVY_OBJECT;
	if (typeName == "BorderObject")
		return GameObjectType::BORDER_OBJECT;
	if (typeName == "PlayerObject")
		return GameObjectType::MAIN_HERO_OBJECT;
	if (typeName == "BombObject")
		return GameObjectType::BOMB_OBJECT;
	if (typeName == "Portal_1_Object")
		return GameObjectType::PORTAL_1_OBJECT;
	if (typeName == "Portal_2_Object")
		return GameObjectType::PORTAL_2_OBJECT;
	if (typeName == "MonsterObject")
		return GameObjectType::MONSTER_OBJECT;

	std::string error= "Unhandled string: ";
	error += typeName;
	std::cout << error << "\n";
	throw new std::exception(error.c_str());
	return GameObjectType::MAX_OBJECT_COUNT;
}