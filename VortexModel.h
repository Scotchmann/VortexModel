#ifndef VORTEXMODEL_LINUX_VORTEXMODEL_H
#define VORTEXMODEL_LINUX_VORTEXMODEL_H

#include "Vortex.h"
#include "InertialVector.h"
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>

using namespace std;

typedef vector<InertialVector * > CumulativeVector;



///--
///--Инициализирует вихрь
///--
void InitializeVortex();

///--
///--Заводит значение в вихрь
///--
double pushAgent(double value, bool Up);

///--
///--Получает значение агента
///--
double getAgent(int i, int j, bool Up);

int GetDistance();

double GetBuf();

void DisplayChart();

int DrawChart(CumulativeVector *);

#endif //VORTEXMODEL_LINUX_VORTEXMODEL_H