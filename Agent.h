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

    double getValue() const;

    void setValue(double value);

    double getDifferential() const;

    void setDifferential(double differential);

    double getReceivedForecast() const;

    void setReceivedForecast(double ReceivedForecast);


private:

    double d_value;					//
    double d_differential;
    //double previous_differential;	//
    double reliability;				//
    Agent * InnerAgent;				//
    double ReceivedForecast;		//

};

#endif //VORTEXMODEL_LINUX_AGENT_H