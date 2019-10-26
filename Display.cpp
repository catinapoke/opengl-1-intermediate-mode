#pragma once
#include "Display.h"

extern const int mapSize;

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// Redisplay loop
void Display(void)
{
	counter.AddFrame();

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	camera.apply();

	glEnable(GL_LIGHTING);
	light[0].apply(GL_LIGHT0);
	light[1].apply(GL_LIGHT1);

	planeGraphicObject.draw();

	// Display graphic objects
	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
		{
			if (gameObjects[i][j] != nullptr)
				gameObjects[i][j]->draw();
		}	
	};

	player->draw();

	glutSwapBuffers();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}

void DispalyInit()
{
	// Set redisplay func
	glutDisplayFunc(Display);
	// Set reshape func
	glutReshapeFunc(Reshape);
};