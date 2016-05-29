#ifndef VORTEXMODEL_LINUX_AGENT_H
#define VORTEXMODEL_LINUX_AGENT_H

class Agent
{

public:

	///--
	///--Конструкторы
	///--
	
    Agent();
	
//_______________________________________________________________________________________________
	
	///--
	///--Деструкторы
	///--
	
    ~Agent();


//_______________________________________________________________________________________________
	
	///--
	///--Публичные поля
	///--
	
    double value;					//
    double differential;			//
    double previous_differential;	//
    double reliability;				//
    Agent * InnerAgent;				//
    double ReceivedForecast;		//

private:

};

#endif //VORTEXMODEL_LINUX_AGENT_H