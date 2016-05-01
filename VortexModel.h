#pragma once

#include "Vortex.h"

using namespace std;

void InitializeVortex();

///--
///--Заводит значение в вихрь
///--
double pushAgent(double value, bool Up);


double getAgent(int i, int j, bool Up);

int GetDistance();

double GetBuf();

