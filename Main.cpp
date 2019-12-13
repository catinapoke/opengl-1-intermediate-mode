#pragma once
#include <string>
#include "basicOpengl.h"
#include "Data.h"
#include "Simulation.h"
#include "Display.h"

using namespace glm;

template<size_t SIZE, class T> inline size_t array_size(T(&arr)[SIZE]) {
	return SIZE;
}

void OpenGLInit(int argc, char** argv)
{
	// GLUT library initialisation
	glutInit(&argc, argv);
	// Display initialisation
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// Set up window
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(800, 600);
	glutCreateWindow(TitleName.c_str());

	glewInit();

	// OpenGL information
	printf("GLEW version - %s\n", glewGetString(GLEW_VERSION));
	printf("OpenGL version - %s\n", glGetString(GL_VERSION));
	printf("Vendor - %s\n", glGetString(GL_VENDOR));
}

void main(int argc, char** argv)
{
	OpenGLInit(argc, argv);
	DataInit();
	DispalyInit();
	SimulationInit();
	return;
};