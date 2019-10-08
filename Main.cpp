#include <windows.h>
#include <cstdio>
#include <string>
#include <exception>
#include "GraphicObject.h"
#include "Camera.h"
#include "Time.h"
#include "FPSCounter.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"

using namespace glm;

template<size_t SIZE, class T> inline size_t array_size(T(&arr)[SIZE]) {
	return SIZE;
}

std::string TitleName = "Algorithms of processing computer graphics";

// ��������� ����������� ��������
const int graphicObjectCount = 4;
GraphicObject graphicObjects[graphicObjectCount];
Time time;
FPSCounter counter;
Camera camera;

// �������, ���������� ��� ��������� �������� ����
void Reshape(int w, int h)
{
	// ���������� ����� ������� ���������, ������ ���� ������� ����
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// ���������� ������� �������� � ���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay
void Display(void)
{
	counter.AddFrame();
	// �������� ����� �����
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);

	// ������������� ������
	camera.apply();
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(15, 15, 10, 0, 0, 0, 0, 1, 0);

	// ������� �������
	for (int i = 0; i < graphicObjectCount; i++)
	{
		//printf(graphicObjects[i].getPosition().x);
		graphicObjects[i].draw();
	};
	// ����� ��������� � ������� �������
	glutSwapBuffers();
};

void HandleInput(float milliseconds)
{
	//printf("Handle %f miliseconds\n",milliseconds);
	if (GetAsyncKeyState(VK_RIGHT))
		camera.rotateLeftRight(milliseconds);
	if (GetAsyncKeyState(VK_LEFT))
		camera.rotateLeftRight(-milliseconds);
	if (GetAsyncKeyState(VK_UP))
		camera.rotateUpDown(milliseconds);
	if (GetAsyncKeyState(VK_DOWN))
		camera.rotateUpDown(-milliseconds);
}
// ������� ���������� ������ 20 ��
void Simulation()
{
	//	������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();
	int elapsedTime = time.ElapsedMiliseconds();
	counter.Update(elapsedTime);
	HandleInput(elapsedTime);
	//GetAsyncKeyState(VK_LEFT);
	// ��� �� ������� ����� ������� ��� ��� ����� 20 ��
	glutIdleFunc(Simulation);
};

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_UP)// Disregard redundant GLUT_UP events
		return;
	if (button == 3) // Up
		camera.zoomInOut(true); // Closer
	else if (button == 4)
		camera.zoomInOut(false); // Further
}

// ������� ��������� ������� ������
void KeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", (unsigned int)key);
};

void main(int argc, char** argv)
{
	// ������������� ���������� GLUT
	glutInit(&argc, argv);
	// ������������� ������� (������ ������)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// �������� ����:
	// 1. ������������� ������� ����� ���� ����
	glutInitWindowPosition(200, 200);
	// 2. ������������� ������ ����
	glutInitWindowSize(800, 600);
	// 3. ������� ����
	glutCreateWindow(TitleName.c_str());
	//glutSetWindowTitle
	// ������������� �������, ������� ����� ���������� ��� ����������� ����
	glutDisplayFunc(Display);
	// ������������� �������, ������� ����� ���������� ��� ��������� �������� ����
	glutReshapeFunc(Reshape);
	glutMouseFunc(mouse);

	time = Time();
	counter = FPSCounter(TitleName);
	camera = Camera(15, 15, 10);
	// ������������� ������� ������� ����� ������� ����� 20 ��
	glutIdleFunc(Simulation);
	// ������������� �������, ������� ����� ���������� ��� ������� �� �������
	//glutKeyboardFunc(KeyboardFunc);

	// ������������� ��������
	graphicObjects[0] = GraphicObject(vec3(5, 0, 0), 180, vec3(1.0f, 0.0f, 0.0f));
	graphicObjects[1] = GraphicObject(vec3(-5, 0, 0), 0, vec3(0.0f, 0.0f, 1.0f));
	graphicObjects[2] = GraphicObject(vec3(0, 0, 5), 90, vec3(0.0f, 0.0f, 0.0f));
	graphicObjects[3] = GraphicObject(vec3(0, 0, -5), 270, vec3(0.0f, 1.0f, 0.0f));

	// �������� ���� ��������� ��������� ��
	glutMainLoop();
	return;
};