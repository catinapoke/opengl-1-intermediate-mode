#pragma once
#include "basicOpengl.h"
#include "Time.h"
#include "Data.h"

extern void Simulation();
extern void HandleInput(float milliseconds);
extern void mouse(int button, int state, int x, int y);
extern void KeyboardFunc(unsigned char key, int x, int y);

extern void SimulationInit();

extern void MovePlayer(ivec2 direction);
extern void OnPlayerStop(GameObject*, ivec2);
extern void OnBombExplosion(Bomb* bomb);
bool IsKillable(int x, int y);
extern void OnMonsterStop(GameObject*, ivec2);
extern void SpawnBomb(int x, int y);
extern void MoveObject(std::shared_ptr<GameObject> obj, ivec2 direction);