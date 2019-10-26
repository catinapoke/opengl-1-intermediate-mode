#pragma once
#include "basicOpengl.h"
#include "Time.h"
#include "Data.h"

extern void Simulation();
extern void HandleInput(float milliseconds);
// Freeglut mouse handler
extern void mouse(int button, int state, int x, int y);
// Freeglut keyboard handler
extern void KeyboardFunc(unsigned char key, int x, int y);
// Simulation part initialisation
extern void SimulationInit();

// Move player using the rules
extern void MovePlayer(ivec2 direction);
// Move object without rules
extern void MoveObject(GameObject* obj, ivec2 direction);
