#ifndef VORTEXMODEL_LINUX_POLE_H
#define VORTEXMODEL_LINUX_POLE_H

#include <vector>
#include "Bond.h"
#include "DifferentialSet.h"

using namespace std;

class Bond;

class Pole
{

public:

//_______________________________________________________________________________________________

    //--
    //--Конструкторы
    //--
	
    Pole	();
    Pole	(double value, DifferentialSet differential);

//_______________________________________________________________________________________________
    
	//--
    //--Деструкторы
    //--
	
    ~Pole	();

//_______________________________________________________________________________________________
    
	//--
    //--Публичные поля
    //--
	
    vector<Bond*> 	Connections;

//_______________________________________________________________________________________________
	
    //--
    //--Публичные методы
    //--
	
    bool            sortSourceConnections      	();
    bool            easeAllBonds               	();
    double          getValue                 	() const;
    double          getCumulativeReliability	() const;
    void            setDifferential             (DifferentialSet differential);
    DifferentialSet getDifferential             () const;
    double          get_b_forecast              ();
    double          get_c_forecast              ();


private:

//_______________________________________________________________________________________________

    //--
    //--Приватные поля
    //--
	
    double  d_value;                    // Значение
    DifferentialSet  d_differential; 	// Дифференциал
	
//_______________________________________________________________________________________________

	//--
	//--Компаратор связей
	//--
    struct BondComparator
    {
		bool operator() (const Bond * left, const Bond * right)
        {
            return (left->getReliability() > right->getReliability());
        }

    } BondComparatorObject;
	
};

#endif //VORTEXMODEL_LINUX_POLE_H
