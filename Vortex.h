#ifndef VORTEXMODEL_LINUX_VORTEX_H
#define VORTEXMODEL_LINUX_VORTEX_H

#include "Agent.h"
#include "Bond.h"
#include "Pole.h"
#include "InertialVector.h"
#include "VortexModel.h"
#include "DifferentialSet.h"
#include <vector>
#include <math.h>
#include <algorithm>


using namespace std;

typedef vector<InertialVector * > CumulativeVector;	// алиас для куммулятивного вектора

class Vortex;

typedef vector< vector< Agent > > AgentsArray;		// алиас для массива агентов

class Vortex
{

public:

//_______________________________________________________________________________________________

	//--
	//--Публичные методы
	//--
    
	Vortex	();
    
	Vortex	(	
				int 	ArraySize 		= 0, 		// количество колец
				double 	Step 			= 0.000, 	// шаг в процентах между полюсами
				int 	MaxSizeOfRing 	= 500000, 	// максимальный размер кольца
				double 	EasingRatio 	= 0.00001, 	// коэффициент ослабления
				double 	strengthen_step = 1.0		// шаг укрепления связи
			);
	
    ~Vortex	();		// Деструктор
	
    double 	pushAgent		(double, CumulativeVector *);   // заведение значения в матрицу
    double 	getAgent        (int i, int j);			        // получение поколения агента
    double  getBuf          ();
    int		getDistance		();

//_______________________________________________________________________________________________

	//--
	//--Публичные поля
	//--
	
    AgentsArray 	_Agents;								// агенты матрицы

private:

//_______________________________________________________________________________________________

	//--
	//--Приватные поля
	//--

    int 		int_ArraySize;								// размер матрицы
    double		int_Step;									// шаг между полюсами кольца
    double 		d_Easing_ratio;								// коэффициент ослабления связи
    int			int_MaxSizeOfRing;							// максимальный размер кольца
    double		d_strengthen_step;                      	// шаг укрепления связи


    vector< vector<Pole *> > 	PolesRingsStack;        	// стопка колец

//_______________________________________________________________________________________________

	//--
	//--Приватные методы
	//--
	
    void 		        RecalculationOfMainPool	(int, int, AgentsArray *, int, CumulativeVector *);				// пересчет основного пула треугольной матрицы
    InertialVector *	PushToPolesRing			(int level, Agent * CurrenAgent, Agent * prev_Agent = nullptr);	// заведение значения в кольцо
    InertialVector *	ProcessPole				(Pole *_pole, double value, int level, Agent* CurrenAgent);		// обработка полюса
    void				AddNewPoleToPolesRing	(int level, Pole * _pole, bool isToPush, int index = 0);		// заведение нового полюса в кольцо


    //--
    //--Компаратор полюсов
    //--
    struct PoleComparator 
	{
        bool operator() (const Pole * left, const Pole * right)
		{
			return (left->getCumulativeReliability() < right->getCumulativeReliability());
		}
    
	} PoleComparatorObject;

};

#endif //VORTEXMODEL_LINUX_VORTEX_H
