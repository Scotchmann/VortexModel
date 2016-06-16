#ifndef VORTEXMODEL_LINUX_AGENT_H
#define VORTEXMODEL_LINUX_AGENT_H

#include "differentialset.h"


class Agent
{

public:

	//--
	//--Конструкторы
	//--
	
    Agent();
	
//_______________________________________________________________________________________________
	
	//--
	//--Деструкторы
	//--
    
	~Agent();

//_______________________________________________________________________________________________
	
	//--
	//--Публичные поля
	//--

    double getValue() const;

    //--
    //--Устанавливает значение агента
    //--
    void setValue(double value);

    //--
    //--Получает дифференциал
    //--
    DifferentialSet getDifferential() const;

    //--
    //--Устанавливает дифференциал
    //--
    void setDifferential(DifferentialSet differential);

    //--
	//--Получает принятый прогноз
    //--
    double getReceivedForecast() const;

    //--
	//--Устанавливает принятый прогноз
    //--
    void setReceivedForecast(double ReceivedForecast);


private:

    double          d_value;            //
    DifferentialSet d_differential;     //
    Agent *         InnerAgent;         //

};

#endif //VORTEXMODEL_LINUX_AGENT_H
