#pragma once
#include "Simulation.h"

void Simulation()
{
	int elapsedTime = time.ElapsedMiliseconds();
	counter.Update(elapsedTime); // FPS counter

	HandleInput(elapsedTime);

	// Update game objects
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

	player->update(elapsedTime * 1.0f / 1000);
	light[1].setPosition(player->GetGraphicPosition()); // Light of player

	//	Display()
	glutPostRedisplay();
	// Simulation loop
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
		
	// Move input
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

	if (gameObjects[destinationIndex.x][destinationIndex.y] == nullptr)
	{
		printf("No block on a way\n");
		player->move(GetDirection(direction));
	}
	else
	{
		GameObject::Type type = gameObjects[destinationIndex.x][destinationIndex.y]->GetType();
		if (type == GameObject::Type::Border || type == GameObject::Type::HeavyCube)
			return;
		if(type == GameObject::Type::LightCube)
		{
			if (doubleDestinationIndex.x < 0 || doubleDestinationIndex.x >= mapSize || doubleDestinationIndex.y < 0 || doubleDestinationIndex.y >= mapSize)
				return;
			if (gameObjects[doubleDestinationIndex.x][doubleDestinationIndex.y] != nullptr)
				return;

			MoveObject(gameObjects[destinationIndex.x][destinationIndex.y], direction);
			player->move(GetDirection(direction));
		}
	}
}

// Use only in MovePlayer
void MoveObject(GameObject* obj, ivec2 direction)
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
	

	GameObject* temp = gameObjects[objPosition.x][objPosition.y];
	gameObjects[objPosition.x][objPosition.y] = gameObjects[destinationPos.x][destinationPos.y];
	gameObjects[destinationPos.x][destinationPos.y] = temp;
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

// Freeglut keyboard handler
void KeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", (unsigned int)key);
}

void SimulationInit()
{
	// GLUT mouse events handler
	glutMouseFunc(mouse);
	// Simulation loop
	glutIdleFunc(Simulation);
	// OS events handler
	glutMainLoop();
};