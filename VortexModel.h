#pragma once

#include "Vortex.h"
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;



///--
///--Инициализирует вихрь
///--
void InitializeVortex();

///--
///--Заводит значение в вихрь
///--
double pushAgent(double value, bool Up);


double getAgent(int i, int j, bool Up);

int GetDistance();

double GetBuf();

void display();

int DrawChart();
