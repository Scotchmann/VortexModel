#pragma once
#include "vector"
#include "Agent.h"
#include "algorithm"
#include "Bond.h"
#include "Pole.h"
#include <math.h>

using namespace std;

class Vortex;

typedef vector< vector< Agent > > AgentsArray;	// Алиас для массива агентов
typedef vector< Vortex* > VortexArray;			// Алиас для массива вихря

///--
///--Структура прогноза
///--
struct Forecast
{
    double value;		// Значение прогноза
    double reliability;	// Надежность прогноза
    int distance;		// Дистанция прогноза
};

class Vortex
{
public:
    Vortex	();
    Vortex	(int ArraySize = 0, int Generation = 0, double Step = 0.00006, int MaxSizeOfRing = 5000, double EasingRatio = 0.001);
    ~Vortex	();
    double 	pushAgent		(double);				// Заведение значения в матрицу
    double 	GetAgent		(int i, int j);			// Получение поколения агента
    void 	SetGeneration	(int);					// Установка поколения агента
    double  GetBuf			();
    int		GetDistance		();

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

    vector<Forecast*> ForecastVector;


    void 		RecalculationOfMainPool		(int, int, AgentsArray *, int);				// Пересчет основного пула треугольной матрицы
    Forecast *	PushToPolesRing				(double value, double prev_value = 0);		// Заведение значения в кольцо
    Forecast *	PushToDenominatorsRing		(double value, double prev_value = 0);		// Заведение деноминатора в кольцо деноминаторов
    Forecast *	ProcessPole					(Pole * _pole, double value); 				// Обработка полюса
    void		AddNewPoleToPolesRing		(Pole * _pole, bool isPush, int index = 0);	// Заведение нового полюса в кольцо

    ///--
    ///--Компаратор полюсов
    ///--
    struct PoleComparator {
        bool operator() (const Pole * left, const Pole * right) { return (left->d_value < right->d_value); }
    } PoleComparatorObject;

    struct ForecastComparator {
        bool operator() (const Forecast * left, const Forecast * right) { return (left->reliability > right->reliability); }
    } ForecastComparatorObject;

};