#pragma once
#include "Simulation.h"

void Simulation()
{
	int elapsedTime = framesTime.ElapsedMiliseconds();
	counter.Update(elapsedTime);
	HandleInput(elapsedTime);
	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
		{
			if (gameObjects[i][j] != nullptr)
			{
				gameObjects[i][j]->update(elapsedTime * 1.0f / 1000);
			}
		}
	}
	if (player != nullptr)
		player->update(elapsedTime * 1.0f / 1000);
	if (currentBomb != nullptr)
		currentBomb->Update(elapsedTime);

	if (player != nullptr)
		light[1].setPosition(player->GetGraphicPosition());

	//	устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();

	// Вызов функции Simulation через 0.0s
	glutIdleFunc(Simulation);
};

void HandleInput(float milliseconds)
{
	// Camera section
	if (GetAsyncKeyState(VK_RIGHT))
		camera.rotateLeftRight(milliseconds);
	if (GetAsyncKeyState(VK_LEFT))
		camera.rotateLeftRight(-milliseconds);
	if (GetAsyncKeyState(VK_UP))
		camera.rotateUpDown(milliseconds);
	if (GetAsyncKeyState(VK_DOWN))
		camera.rotateUpDown(-milliseconds);

	static bool one_unpressed = true;
	if (one_unpressed && GetAsyncKeyState(0x31))
	{
		multisampling = !multisampling;
		if (multisampling)
			multisamplingString = "MSAA [On]";
		else
			multisamplingString = "MSAA [Off]";
		one_unpressed = false;
	}
	else if (!GetAsyncKeyState(0x31))
		one_unpressed = true;

	static bool SpacePressed = true;

	if (SpacePressed && GetAsyncKeyState(0x20) && player != nullptr)
	{
		if (currentBomb == nullptr)
		{
			ivec2 playerPos = player->getPosition();
			SpawnBomb(playerPos.x, playerPos.y);
		}
		SpacePressed = false;
	}
	else if (!GetAsyncKeyState(0x20))
		SpacePressed = true;

	static bool TwoPressed = true;
	if (TwoPressed && GetAsyncKeyState(0x32))
	{
		Texture::texFilterMode = (Texture::texFilterMode + 1) % 9;
		switch (Texture::texFilterMode)
		{
		case 0:
			filterMode = "1)Точечная фильтрация";
			break;
		case 1:
			filterMode = "2)Билинейная фильтрация";
			break;
		case 2:
			filterMode = "3)Билинейная фильтрация с использованием mipmap’ов";
			break;
		case 3:
			filterMode = "4)Трилинейная фильтрация";
			break;
		case 4:
			filterMode = "5)Анизотропная фильтрация х2";
			break;
		case 5:
			filterMode = "6)Анизотропная фильтрация х4";
			break;
		case 6:
			filterMode = "7)Анизотропная фильтрация х8";
			break;
		case 7:
			filterMode = "8)Анизотропная фильтрация х16";
			break;
		case 8:
			filterMode = "9)Анизотропная фильтрация х32";
			break;
		}
		TwoPressed = false;
	}
	else if (!GetAsyncKeyState(0x32))
		TwoPressed = true;

	if (player == nullptr)
		return;

	ivec2 direction(0, 0);
	if (GetAsyncKeyState(0x57)) // W
	{
		direction.y--;
	}
	if (GetAsyncKeyState(0x53)) // S
	{
		direction.y++;
	}
	if (GetAsyncKeyState(0x44)) // D
	{
		direction.x++;
	}
	if (GetAsyncKeyState(0x41)) // A
	{
		direction.x--;
	}
	MovePlayer(direction);
}

void SpawnBomb(int x, int y)
{
	gameObjects[x][y] = gameObjectFactory.create(GameObjectType::BOMB_OBJECT, x, y);
	currentBomb = std::dynamic_pointer_cast<Bomb>(gameObjects[x][y]);
	currentBomb->SetCallbackExplodeEvent(OnBombExplosion);
}

void MovePlayer(ivec2 direction)
{
	ivec2 playerPosition = player->getPosition();
	if (player->isMoving())
		return;

	ivec2 destinationIndex;
	ivec2 doubleDestinationIndex;
	if (direction.x != 0)
	{
		int destination = playerPosition.x + direction.x;
		if (destination < 0 || destination >= mapSize)
			return;
		destinationIndex = ivec2(destination, playerPosition.y);
		doubleDestinationIndex = ivec2(destination + direction.x, playerPosition.y);
	}
	else if (direction.y != 0)
	{
		int destination = playerPosition.y + direction.y;
		if (destination < 0 || destination >= mapSize)
			return;
		destinationIndex = ivec2(playerPosition.x, destination);
		doubleDestinationIndex = ivec2(playerPosition.x, destination + direction.y);
	}
	else
		return;

	if (gameObjects[destinationIndex.x][destinationIndex.y] == nullptr
		|| gameObjects[destinationIndex.x][destinationIndex.y]->GetType() == GameObjectType::PORTAL_1_OBJECT
		|| gameObjects[destinationIndex.x][destinationIndex.y]->GetType() == GameObjectType::PORTAL_2_OBJECT)
	{
		player->move(GetDirection(direction));
	}
	else
	{
		GameObjectType type = gameObjects[destinationIndex.x][destinationIndex.y]->GetType();
		if (type == GameObjectType::BORDER_OBJECT || type == GameObjectType::HEAVY_OBJECT)
		{
			return;
		}

		if (type == GameObjectType::LIGHT_OBJECT || type == GameObjectType::BOMB_OBJECT)
		{
			// std::cout << "Found light objects\n";
			if (doubleDestinationIndex.x < 0 || doubleDestinationIndex.x >= mapSize || doubleDestinationIndex.y < 0 || doubleDestinationIndex.y >= mapSize)
				return;
			if (gameObjects[doubleDestinationIndex.x][doubleDestinationIndex.y] != nullptr)
				return;

			MoveObject(gameObjects[destinationIndex.x][destinationIndex.y], direction);
			player->move(GetDirection(direction));
			return;
		}
		std::cout << "I dunno what found\n";
	}
}

void OnPlayerStop(GameObject* object, ivec2)
{
	ivec2 playerPos = player->getPosition();
	if (gameObjects[playerPos.x][playerPos.y] == nullptr)
		return;
	GameObjectType type = gameObjects[playerPos.x][playerPos.y]->GetType();
	if (type == GameObjectType::PORTAL_1_OBJECT || type == GameObjectType::PORTAL_2_OBJECT)
	{
		std::shared_ptr<Portal> currentPortal = std::dynamic_pointer_cast<Portal>(gameObjects[playerPos.x][playerPos.y]);
		std::shared_ptr<Portal> nextPortal = currentPortal->nextPortal;
		if (nextPortal != nullptr)
			player->setPosition(nextPortal->getPosition());
	}
}

void OnBombExplosion(Bomb* bomb)
{
	// throw new std::exception("Unimplemented method");
	ivec2 pos = bomb->getPosition();
	ivec2 horizontal(pos.x, pos.x);
	ivec2 vertical(pos.y, pos.y);

	// Search edge positions without objects
	for (int i = pos.x + 1; i < mapSize; i++) // right
	{
		if (gameObjects[i][pos.y] != nullptr)
			break;
		horizontal.y = i;
	}
	for (int i = pos.y + 1; i < mapSize; i++) // down
	{
		if (gameObjects[pos.x][i] != nullptr)
			break;
		vertical.y = i;
	}
	for (int i = pos.x - 1; i > 0; i--) // left
	{
		if (gameObjects[i][pos.y] != nullptr)
			break;
		horizontal.x = i;
	}
	for (int i = pos.y - 1; i > 0; i--) // up
	{
		if (gameObjects[pos.x][i] != nullptr)
			break;
		vertical.x = i;
	}

	if (IsKillable(horizontal.x - 1, pos.y))
	{
		gameObjects[horizontal.x - 1][pos.y].reset();
	}
	if (IsKillable(horizontal.y + 1, pos.y))
	{
		gameObjects[horizontal.y + 1][pos.y].reset();
	}
	if (IsKillable(pos.x, vertical.x - 1))
	{
		gameObjects[pos.x][vertical.x - 1].reset();
	}
	if (IsKillable(pos.x, vertical.y + 1))
	{
		gameObjects[pos.x][vertical.y + 1].reset();
	}

	ivec2 playerPos = player->getPosition();
	if (player != nullptr && (playerPos.y == pos.y && playerPos.x >= horizontal.x && playerPos.x <= horizontal.y) || (playerPos.x == pos.x && playerPos.y >= vertical.x && playerPos.y <= vertical.y))
		player.reset();
	//delete(currentBomb.get());
	gameObjects[pos.x][pos.y].reset();
	currentBomb.reset();
}

bool IsKillable(int x, int y)
{
	return gameObjects[x][y] == nullptr
		|| gameObjects[x][y]->GetType() == GameObjectType::LIGHT_OBJECT
		|| gameObjects[x][y]->GetType() == GameObjectType::MONSTER_OBJECT;
}

void OnMonsterStop(GameObject* object, ivec2 previousPos)
{
	ivec2 monsterPos = object->getPosition();
	gameObjects[previousPos.x][previousPos.y].swap(gameObjects[monsterPos.x][monsterPos.y]);
	if (player == nullptr)
		return;
	ivec2 playerPos = player->getPosition();
	ivec2 difference = ivec2(abs(playerPos.x - monsterPos.x), abs(playerPos.y - monsterPos.y));
	if (difference.x + difference.y < 2)
	{
		player.reset();
	}
}

// Use only in MovePlayer
void MoveObject(std::shared_ptr<GameObject> obj, ivec2 direction)
{
	ivec2 objPosition = obj->getPosition();
	ivec2 destinationPos(objPosition.x, objPosition.y);
	if (direction.x > 0)
	{
		obj->move(MoveDirection::right);
		destinationPos = ivec2(objPosition.x + direction.x, objPosition.y);
	}
	else if (direction.x < 0)
	{
		obj->move(MoveDirection::left);
		destinationPos = ivec2(objPosition.x + direction.x, objPosition.y);
	}
	else if (direction.y > 0)
	{
		obj->move(MoveDirection::up);
		destinationPos = ivec2(objPosition.x, objPosition.y + direction.y);
	}
	else if (direction.y < 0)
	{
		obj->move(MoveDirection::down);
		destinationPos = ivec2(objPosition.x, objPosition.y + direction.y);
	}

	gameObjects[objPosition.x][objPosition.y].swap(gameObjects[destinationPos.x][destinationPos.y]);
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_UP) // Disregard redundant GLUT_UP events
		return;
	if (button == 3) // Up
		camera.zoomInOut(true); // Closer
	else if (button == 4)
		camera.zoomInOut(false); // Further
}

// Функция обработки нажатия клавиш
void KeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", (unsigned int)key);
}

void SimulationInit()
{
	// Устанавливаем функцию, обрабатывающую сообщения от комп. мыши
	glutMouseFunc(mouse);
	// устанавливаем функцию которая будет вызвана через 20 мс
	glutIdleFunc(Simulation);
	// основной цикл обработки сообщений ОС
	glutMainLoop();
};