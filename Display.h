#pragma once
#include "basicOpengl.h"
#include "Data.h"
#include "Simulation.h"

extern void Reshape(int w, int h);
extern void Display(void);

extern void drawOpaque();
extern void drawTransparent();
extern void drawBombFuse();

extern void DispalyInit();