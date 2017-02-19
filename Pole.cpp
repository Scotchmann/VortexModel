
#include "Pole.h"
#include <algorithm>


Pole::Pole()
{
	
}

//--
//--Конструктор полюса
//--
Pole::Pole(double value, DifferentialSet differential)
{
    d_value 		= value;
	d_differential 	= differential;
}

//--
//--Деструктор полюса
//--
Pole::~Pole()
{
    //--
    //--Удаляем все связи в удаляемом полюсе
    //--
	
	mark_1:
	for(auto it_i = Contexts.begin(); it_i != Contexts.end(); ++it_i)
	{
		mark_2:
        for (auto it_j = (*it_i)->Connections.begin(); it_j !=  (*it_i)->Connections.end(); ++it_j)
		{
			delete *it_j;
            ((Context*)(*it_i))->Connections.erase(it_j);  // удаляем элемент из контейнера
			goto mark_2;
		}
		
		delete *it_i;
	    Contexts.erase(it_i);
		goto mark_1;
	}
}

//--
//--Сортирует связи полюса
//--
bool Pole::sortSourceConnections(Context * PassedContext)
{
	sort(PassedContext->Connections.begin(), PassedContext->Connections.end(), BondComparatorObject);
    return true;
}

//--
//--Ослабляет все связи в полюсе
//--
bool Pole::easeAllBonds()
{
    //--
    //--1. Собственно ослабляем все связи
    //--
	
	for(auto it_i = Contexts.begin(); it_i != Contexts.end(); ++it_i)
	{
        for (auto it_j = (*it_i)->Connections.begin(); it_j != (*it_i)->Connections.end(); ++it_j)
		{
			(*it_j)->Ease();
		}
	}

    //--
    //--2. Удаляем отмершие связи у полюса
    //--
	
	mark_3:
	for(auto it_i = Contexts.begin(); it_i != Contexts.end(); ++it_i)
	{
	
		mark_4:
        for (auto it_j = (*it_i)->Connections.begin(); it_j != (*it_i)->Connections.end(); ++it_j)
		{
			if ((*it_j)->getReliability() <= 0)
			{
				delete *it_j;
                (*it_i)->Connections.erase(it_j);
				goto mark_4;
			}
		}

		delete *it_i;
		Contexts.erase(it_i);
        goto mark_3;
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
    
	//--
	//--Собираем куммулятивную надежность
	//--
	
	for(auto it_i = Contexts.begin(); it_i != Contexts.end(); ++it_i)
	{
        for(auto it_j = (*it_i)->Connections.begin(); it_j != (*it_i)->Connections.end(); ++it_j)
		{
			cumulative_reliability = cumulative_reliability + (*it_j)->getReliability();
		}
	}
	
    return cumulative_reliability;
}

void Pole::setDifferential(DifferentialSet differential)
{
    d_differential = differential;
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




