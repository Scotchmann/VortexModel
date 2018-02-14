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

struct ForecastedValue
{
    double  value;
    double  reliability;
    double  distance;
};

//  Инициализирует вихрь
void InitializeVortex(
						int 	ArrSize 		= 0, 	// количество колец
						double 	Step 			= 0, 	// шаг в процентах между полюсами
						int 	MaxSizeOfRing 	= 0, 	// максимальный размер кольца
						double 	EasingRatio 	= 0, 	// коэффициент ослабления
						double 	strengthen_step	= 0		// шаг укрепления связи
                     );

//  Заводит значение в вихрь
ForecastedValue pushAgent(double value, bool Up);

//  Получает значение агента
double getAgent(int i, int j, bool Up);

int GetDistance();

double GetBuf();

void DisplayChart();

int DrawChart(CumulativeVector *);

#endif //VORTEXMODEL_LINUX_VORTEXMODEL_H
