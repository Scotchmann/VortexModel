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

typedef vector<InertialVector * > CumulativeVector;    // алиас для куммулятивного вектора
class Vortex;
typedef vector< vector< Agent > > AgentsArray;         // алиас для массива агентов
typedef vector< vector< double > > AnswerArray;        // алиас для массива ответов

class Vortex
{

//--------------------------------------------------------------------------------------------------
public://  ПУБЛИЧНАЯ СЕКЦИЯ
//--------------------------------------------------------------------------------------------------

//__Конструкторы____________________________________________________________________________________
	Vortex	();

	Vortex	(
				int 	ArraySize 		= 0,          // количество колец
				double 	Step 			= 0.000,      // шаг в процентах между полюсами
				int 	MaxSizeOfRing 	= 500000,     // максимальный размер кольца
				double 	EasingRatio 	= 0.00001,    // коэффициент ослабления
				double 	strengthen_step = 1.0         // шаг укрепления связи
			);

//__Деструкторы_____________________________________________________________________________________

    ~Vortex	();

//__Публичные_методы________________________________________________________________________________

    double 	pushAgent(double, CumulativeVector *);    // заведение значения в матрицу

//__Публичные_поля__________________________________________________________________________________

    AgentsArray 	_Agents;                         // агенты матрицы
	AnswerArray     _Answers;                        // ответы

//--------------------------------------------------------------------------------------------------
private://  ПРИВАТНАЯ СЕКЦИЯ
//--------------------------------------------------------------------------------------------------

//__Приватные_поля__________________________________________________________________________________

    int 		int_ArraySize;                      // размер матрицы
    double		int_Step;                           // шаг между полюсами кольца
    double 		d_Easing_ratio;                     // коэффициент ослабления связи
    int			int_MaxSizeOfRing;                  // максимальный размер кольца
    double		d_strengthen_step;                  // шаг укрепления связи
    vector< vector<Pole *> > 	PolesRingsStack;    // стопка колец

//__Приватные_методы________________________________________________________________________________

    // пересчет основного пула треугольной матрицы
    void RecalculationOfMainPool(int, int, AgentsArray *, int, CumulativeVector *);

    // заведение значения в кольцо
    InertialVector * PushToPolesRing(
		                              int level,
		                              int string_number,
									  Agent * CurrenAgent,
									  Agent * prev_Agent = nullptr
								    );

	// обработка полюса
	InertialVector * ProcessPole(
		                          Pole *_pole,
								  double value,
								  int level,
								  int string_number,
								  Agent* CurrenAgent
							    );

    // заведение нового полюса в кольцо
	void AddNewPoleToPolesRing (int level, Pole * _pole, bool isToPush, int index = 0);

    //  Компаратор полюсов
    struct PoleComparator
	{
        bool operator() (const Pole * left, const Pole * right)
		{
			return (left->getCumulativeReliability() < right->getCumulativeReliability());
		}
	} PoleComparatorObject;

};

#endif //VORTEXMODEL_LINUX_VORTEX_H
