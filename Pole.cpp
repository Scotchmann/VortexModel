#include "Pole.h"
#include <algorithm>


Pole::Pole()
{
}

///--
///--Конструктор полюса
///--
Pole::Pole(double value)
{
    d_value = value;
}

///--
///--Деструктор полюса
///--
Pole::~Pole()
{
    ///--
    ///--Удаляем все связи в удаляемом полюсе
    ///--
    I_hate_Cpp:
    for (auto it = Connections.begin(); it != Connections.end(); ++it)
    {
        delete *it;
        Connections.erase(it);  // удаляем элемент из контейнера
        goto I_hate_Cpp;
    }
}

///--
///--Сортирует связи полюса
///--
bool Pole::sortSourceConnections()
{
    sort(Connections.begin(), Connections.end(), BondComparatorObject);
    return true;
}

///--
///--Ослабляет все связи в полюсе
///--
bool Pole::easeAllBonds()
{
    ///--
    ///--1. Собственно ослабляем все связи
    ///--
    for (auto it = Connections.begin(); it != Connections.end(); ++it)
    {
        (*it)->Ease();
    }

    ///--
    ///--2. Удаляем отмершие связи у полюса
    ///--
    I_hate_Cpp:
    for (auto it = Connections.begin(); it != Connections.end(); ++it)
    {
        if ((*it)->getReliability() <= 0)
        {
            delete *it;
            Connections.erase(it);
            goto I_hate_Cpp;
        }
    }

    return false;

}

double Pole::getValue() const
{
    return d_value;
}


