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
    double 			d_value;

    ///--
    ///--Публичные методы
    ///--
    bool SortSourceConnections	();
    bool EaseAllBonds			();

private:

    ///--
    ///--Приватные поля
    ///--
    struct BondComparator
    {
        bool operator() (const Bond * left, const Bond * right)
        {
            return (left->d_reliability > right->d_reliability);
        }
    } BondComparatorObject;
};

