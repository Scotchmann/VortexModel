#ifndef VORTEXMODEL_LINUX_VORTEX_H
#define VORTEXMODEL_LINUX_VORTEX_H


#include "Agent.h"
#include "Bond.h"
#include "Pole.h"
#include "InertialVector.h"
#include "VortexModel.h"
#include "differentialset.h"
#include <vector>
#include <math.h>
#include <algorithm>
#include <thread>
#include <mutex>

using namespace std;


typedef vector<InertialVector * > CumulativeVector;
typedef vector< vector<Pole *> >  OrRing;

class Vortex;

typedef vector< vector< Agent > > AgentsArray;	// Алиас для массива агентов
typedef vector< Vortex* > VortexArray;			// Алиас для массива вихря


class Vortex
{

public:
    
	Vortex	();
    
	Vortex	(	
				int 	ArraySize 		= 0, 		// Количество колец
				double 	Step 			= 0.0005, 	// Шаг в процентах между полюсами
				int 	MaxSizeOfRing 	= 500000, 	// Максимальный размер кольца
				double 	EasingRatio 	= 0.00001, 	// Коэффициент ослабления
				double 	strengthen_step = 1.0		// Шаг укрепления связи
			);
	
    ~Vortex	();		// Деструктор
	
    double 	pushAgent		(double, CumulativeVector *);   // Заведение значения в матрицу
    double 	getAgent        (int i, int j);			        // Получение поколения агента
    double  getBuf          ();
    int		getDistance		();

    AgentsArray 	_Agents;							// Агенты матрицы

private:

    int 		int_ArraySize;							// Размер матрицы
    double		int_Step;								// Шаг между полюсами кольца
    double 		d_Easing_ratio;							// Коэффициент ослабления связи
    int			int_MaxSizeOfRing;						// Максимальный размер кольца
    double		d_strengthen_step;                      // Шаг укрепления связи




    vector< vector<Pole *> > 	PolesRingsStack;        // Стопка колец
    OrRing 	OrderedPolesRing;							// Упорядоченное кольцо полюсов

	
    void 		        RecalculationOfMainPool		(int, int, AgentsArray *, int, CumulativeVector *);					// Пересчет основного пула треугольной матрицы
    InertialVector *	PushToPolesRing				(int level, Agent * CurrenAgent, Agent * prev_Agent = nullptr);	// Заведение значения в кольцо
    InertialVector *	ProcessPole					(Pole *_pole, double value, int level);								// Обработка полюса
    void				AddNewPoleToPolesRing		(int level, Pole * _pole, bool isToPush, int index = 0);			// Заведение нового полюса в кольцо


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

	
    static void         SortOrderedRing             (int level, OrRing * O_R, PoleComparator * PC);                                                         // Сортировка упорядоченного кольца

	//--
	//--Компаратор инерциальных векторов
	//--
    struct ForecastComparator
	{
        bool operator() (const InertialVector * left, const InertialVector * right)
		{
			return (left->getReliability() > right->getReliability());
		}
		
    } ForecastComparatorObject;

};

#endif //VORTEXMODEL_LINUX_VORTEX_H
