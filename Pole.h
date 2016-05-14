#ifndef VORTEXMODEL_LINUX_POLE_H
#define VORTEXMODEL_LINUX_POLE_H
#include <vector>
#include "Bond.h"

using namespace std;

class Bond;
class Pole
{
public:

    ///--
    ///--Конструкторы
    ///--
    Pole	();
    Pole	(double value);

    ///--
    ///--Деструкторы
    ///--
    ~Pole	();

    ///--
    ///--Публичные поля
    ///--
    vector<Bond*> 	Connections;


    ///--
    ///--Публичные методы
    ///--
    bool sortSourceConnections();
    bool easeAllBonds();
    double getValue             () const;


private:

    ///--
    ///--Приватные поля
    ///--
    struct BondComparator
    {
        bool operator() (const Bond * left, const Bond * right)
        {
            return (left->getReliability() > right->getReliability());
        }
    } BondComparatorObject;

    double  d_value;    //Значение
};

#endif //VORTEXMODEL_LINUX_POLE_H