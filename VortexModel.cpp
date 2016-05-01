// TestDLL.cpp : Defines the exported functions for the DLL application.
//

#include "Vortex.h"

using namespace std;

Vortex * ptr_UpVortex;
Vortex * ptr_DownVortex;

const int 	ArraySize 	= 130;	// Размер массива
int 		counter 	= 1;	// Счетчик

///--
///--Инициализация вихря
///--
void InitializeVortex()
{
    ptr_UpVortex 	= new Vortex(ArraySize, 1);
    //ptr_DownVortex 	= new Vortex(ArraySize, 1);
}

///--
///--Заводит значение в вихрь
///--
double pushAgent(double value, bool Up)
{
    Vortex * ptr_PrimalVortex = nullptr;

    Up ? ptr_PrimalVortex = ptr_UpVortex : ptr_PrimalVortex = ptr_DownVortex;

    return ptr_PrimalVortex->pushAgent(value);
}


double getAgent(int i, int j, bool Up)
{
    double size = 0;

    //Up ? size = AgentsUpTrend[i][j].InnerAgent->mutation_percentage : size = AgentsDownTrend[i][j].InnerAgent->mutation_percentage;

    size = ptr_UpVortex->GetAgent(i, j);

    return size;
}

int GetDistance()
{
    int i = 0;
    i = ptr_UpVortex->GetDistance();

    return i;
}

double GetBuf()
{
    double i = 0;
    i = ptr_UpVortex->GetBuf();

    return i;
}
