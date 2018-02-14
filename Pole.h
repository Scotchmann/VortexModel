#ifndef VORTEXMODEL_LINUX_POLE_H
#define VORTEXMODEL_LINUX_POLE_H

#include <vector>
#include <queue>
#include "Bond.h"
#include "DifferentialSet.h"

using namespace std;

class Bond;

class Pole
{

//--------------------------------------------------------------------------------------------------
public://  ПУБЛИЧНАЯ СЕКЦИЯ
//--------------------------------------------------------------------------------------------------

//__Конструкторы____________________________________________________________________________________

    Pole();
    Pole(double value, DifferentialSet differential);

//__Деструкторы_____________________________________________________________________________________

    ~Pole();

//__Публичные_поля__________________________________________________________________________________

    vector<Bond*> Connections;
	queue<Bond*>  BondsQueue;
	double TotalRepeatsCounter;
	int TotalConnectionCounter;

//__Публичные_методы________________________________________________________________________________

    bool sortSourceConnections();
    bool easeAllBonds();
    double getValue() const;
    double getCumulativeReliability() const;
    void setDifferential(DifferentialSet differential);
    DifferentialSet getDifferential() const;
    double get_b_forecast();
    double get_c_forecast();
	double get_b();
    double get_c();


//--------------------------------------------------------------------------------------------------
private://  ПРИВАТНАЯ СЕКЦИЯ
//--------------------------------------------------------------------------------------------------

//__Приватные поля__________________________________________________________________________________

    double  d_value;                    // значение
    DifferentialSet d_differential; 	// дифференциал

	//  Компаратор связей
    struct BondComparator
    {
		bool operator() (const Bond * left, const Bond * right)
        {
            return (left->getReliability() > right->getReliability());
        }
    } BondComparatorObject;

};

#endif //VORTEXMODEL_LINUX_POLE_H
