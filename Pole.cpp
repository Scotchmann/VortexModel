
#include "Pole.h"
#include <algorithm>


Pole::Pole()
{

}

//  Конструктор полюса
Pole::Pole(double value, DifferentialSet differential)
{
    d_value 		= value;
    d_differential = differential;
}

//  Деструктор полюса
Pole::~Pole()
{
    //  Удаляем все связи в удаляемом полюсе
	mark_1:
	for (auto it = Connections.begin(); it !=  Connections.end(); ++it)
	{
		delete *it;
		Connections.erase(it);  // удаляем элемент из контейнера
		goto mark_1;
	}
}

//  Сортирует связи полюса
bool Pole::sortSourceConnections()
{
	sort(Connections.begin(), Connections.end(), BondComparatorObject);
    return true;
}

//  Ослабляет все связи в полюсе
bool Pole::easeAllBonds()
{
    //  1. Собственно ослабляем все связи
	for (auto it : Connections)
	{
		it->Ease();
	}

    //  2. Удаляем отмершие связи у полюса
	mark_2:
	for (auto it = Connections.begin(); it != Connections.end(); ++it)
	{
		if ((*it)->getReliability() <= 0)
		{
			delete *it;
			Connections.erase(it);
			goto mark_2;
		}
	}

    return false;
}

double Pole::getValue() const
{
    return d_value;
}

double Pole::getCumulativeReliability() const
{
    double cumulative_reliability = 0;	// куммулятивная надежность полюса

	//  Собираем куммулятивную надежность
	for(const auto it : Connections)
	{
		cumulative_reliability = cumulative_reliability + it->getReliability();
	}

    return cumulative_reliability;
}

void Pole::setDifferential(DifferentialSet differential)
{

}

DifferentialSet Pole::getDifferential() const
{
    return d_differential;
}

double Pole::get_b_forecast()
{
    return d_value - d_differential.c;
}

double Pole::get_c_forecast()
{
    return d_value - d_differential.b;
}

double Pole::get_b()
{
    return d_differential.b;
}

double Pole::get_c()
{
    return d_differential.c;
}
