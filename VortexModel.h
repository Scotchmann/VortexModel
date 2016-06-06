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
	int value;
	double reliability;
};

///--
///--Инициализирует вихрь
///--
void InitializeVortex( int 	ArrSize 		    = 0, 	// Количество колец
                       int 	Generation 		    = 0, 	// Поколение
                       double 	Step 			= 0, 	// Шаг в процентах между полюсами
                       int 	MaxSizeOfRing 	    = 0, 	// Максимальный размер кольца
                       double 	EasingRatio 	= 0, 	// Коэффициент ослабления
                       double 	strengthen_step = 0		// Шаг укрепления связи
                     );

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