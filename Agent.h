#ifndef VORTEXMODEL_LINUX_AGENT_H
#define VORTEXMODEL_LINUX_AGENT_H

#include "DifferentialSet.h"
#include "Pole.h"


class Agent
{
//--------------------------------------------------------------------------------------------------
public://  ПУБЛИЧНАЯ СЕКЦИЯ
//--------------------------------------------------------------------------------------------------

//__Конструкторы____________________________________________________________________________________

    Agent();

//__Деструкторы_____________________________________________________________________________________

	~Agent();

//__Публичные_методы________________________________________________________________________________

    double getValue() const;

    //  Устанавливает значение агента
    void setValue(double value);

    //  Получает дифференциал
    DifferentialSet getDifferential() const;

    //  Устанавливает дифференциал
    void setDifferential(DifferentialSet differential);

//__Публичные_поля__________________________________________________________________________________

    Pole  * CorrespondingPole;
	Agent * B_Agent;

//--------------------------------------------------------------------------------------------------
private://  ПРИВАТНАЯ СЕКЦИЯ
//--------------------------------------------------------------------------------------------------

//__Приватные_поля__________________________________________________________________________________

    double          d_value;            //
    DifferentialSet d_differential;     //
    Agent *         InnerAgent;         //
};

#endif //VORTEXMODEL_LINUX_AGENT_H
