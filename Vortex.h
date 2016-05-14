#ifndef VORTEXMODEL_LINUX_VORTEX_H
#define VORTEXMODEL_LINUX_VORTEX_H

#include "vector"
#include "Agent.h"
#include "algorithm"
#include "Bond.h"
#include "Pole.h"
#include "InertialVector.h"
#include <math.h>

using namespace std;

class Vortex;

typedef vector< vector< Agent > > AgentsArray;	// Алиас для массива агентов
typedef vector< Vortex* > VortexArray;			// Алиас для массива вихря

class Vortex
{
public:
    Vortex	();
    Vortex	(int ArraySize = 0, int Generation = 0, double Step = 0.00006, int MaxSizeOfRing = 5000, double EasingRatio = 0.001);
    ~Vortex	();
    double 	pushAgent		(double);				// Заведение значения в матрицу
    double 	getAgent        (int i, int j);			// Получение поколения агента
    void 	setGeneration   (int);					// Установка поколения агента
    double  getBuf          ();
    int		getDistance();

    AgentsArray 	_Agents;			// Агенты матрицы

private:

    //VortexArray 	_Vortexes;			//
    int 			int_ArraySize;		// Размер матрицы
    int 			int_Generation;		// Поколение
    double 			int_Step;			// Шаг между полюсами кольца
    double 			d_Easing_ratio;		// Коэффициент ослабления связи
    int				int_MaxSizeOfRing;	// Максимальный размер кольца
    double			d_distributionStep;	// Шаг распределения укрепления между полюсами

    vector<Pole	*> 	PolesRing;			// Кольцо полюсов
    vector<Pole *>	DenominatorsRing;	// Кольцо деноминаторов
    vector<Pole *>  OrderedPolesRing;	// Упорядоченное кольцо полюсов

    vector<InertialVector*> CumulativeInertialVector;   // Куммулятивная инерция по диагонали


    void 		        RecalculationOfMainPool		(int, int, AgentsArray *, int);				// Пересчет основного пула треугольной матрицы
    InertialVector *	PushToPolesRing				(double value, double prev_value = 0);		// Заведение значения в кольцо
    InertialVector *	PushToDenominatorsRing		(double value, double prev_value = 0);		// Заведение деноминатора в кольцо деноминаторов
    InertialVector *	ProcessPole					(Pole * _pole, double value); 				// Обработка полюса
    void		AddNewPoleToPolesRing		(Pole * _pole, bool isPush, int index = 0);	// Заведение нового полюса в кольцо

    ///--
    ///--Компаратор полюсов
    ///--
    struct PoleComparator {
        bool operator() (const Pole * left, const Pole * right) { return (left->getValue() < right->getValue()); }
    } PoleComparatorObject;

    struct ForecastComparator {
        bool operator() (const InertialVector * left, const InertialVector * right) { return (left->getReliability() > right->getReliability()); }
    } ForecastComparatorObject;

};

#endif //VORTEXMODEL_LINUX_VORTEX_H