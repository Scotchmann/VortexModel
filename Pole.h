#pragma once
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
    bool SortSourceConnections	();
    bool EaseAllBonds			();
    double GetValue             () const;

private:

    ///--
    ///--Приватные поля
    ///--
    struct BondComparator
    {
        bool operator() (const Bond * left, const Bond * right)
        {
            return (left->GetReliability() > right->GetReliability());
        }
    } BondComparatorObject;

    double  d_value;    //Значение
};

