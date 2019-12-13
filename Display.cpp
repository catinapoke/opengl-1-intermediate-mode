#pragma once
#include "Display.h"

extern const int mapSize;

// функция, вызываемая при изменении размеров окна
void Reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void Display(void)
{
	counter.AddFrame();
	if (multisampling)// включаем режим сглаживания
		glEnable(GL_MULTISAMPLE);
	// отчищаем буфер цвета
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);

	// устанавливаем камеру
	camera.apply();
	// устанавливаем источник света (сразу после установки камеры)
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	light[0].apply(GL_LIGHT0);
	light[1].apply(GL_LIGHT1);

	drawOpaque();
	drawTransparent();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	studentSign.draw(10, 10);
	drawBombFuse();
	glDisable(GL_BLEND);

	// смена переднего и заднего буферов
	glutSwapBuffers();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);

	if (multisampling)// включаем режим сглаживания
		glDisable(GL_MULTISAMPLE);
}

void drawOpaque()
{
	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
			if (gameObjects[i][j] != nullptr && !gameObjects[i][j]->isTransparent())
				gameObjects[i][j]->draw();
	};
	if (!planeGraphicObject.isTransparent())
	{
		//glActiveTexture(GL_TEXTURE0); // выбираем активный текстурный блок
		//glEnable(GL_TEXTURE_2D); // разрешаем текстурирование
		//planeTexture.apply(GL_TEXTURE0); // привязываем текстуру
		//glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE); // указываем режим наложения текстуры (GL_MODULATE)
		planeGraphicObject.draw();
	}
		
	if (player != nullptr && !player->isTransparent())
		player->draw();
}

void drawTransparent()
{
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
	glDepthMask(false);
	glEnable(GL_CULL_FACE);

	// Front face
	glCullFace(GL_FRONT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (planeGraphicObject.isTransparent())
	{
		//glActiveTexture(GL_TEXTURE0); // выбираем активный текстурный блок
		//glEnable(GL_TEXTURE_2D); // разрешаем текстурирование
		//planeTexture.apply(GL_TEXTURE0); // привязываем текстуру
		//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // указываем режим наложения текстуры (GL_MODULATE)
		planeGraphicObject.draw();
	}
	if (player != nullptr && player->isTransparent())
		player->draw();
	for (std::shared_ptr<GameObject> obj : transparent)
	{
		obj->draw();
	}

	//  Back face
	glCullFace(GL_BACK);
	if (planeGraphicObject.isTransparent())
		planeGraphicObject.draw();
	if (player != nullptr && player->isTransparent())
		player->draw();
	for (std::shared_ptr<GameObject> obj : transparent)
	{
		obj->draw();
	}

	glCullFace(GL_FRONT);
	glDepthMask(true);
	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
}

void drawBombFuse()
{
	if (currentBomb == nullptr)
		return;

	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	int offset = 10;
	int drawHeight = height - bombBar.GetHeight() - offset;
	int drawWidth = offset;
	bombIcon.draw(drawWidth, drawHeight);
	drawWidth += bombIcon.GetWidth();
	int fuse = round(currentBomb->GetFuseRate() * 5);
	for (int i = 0; i < fuse; i++)
	{
		drawWidth += offset;
		bombBar.draw(drawWidth, drawHeight);
		drawWidth += bombBar.GetWidth();
	}
}

void DispalyInit()
{
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(Display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(Reshape);
};