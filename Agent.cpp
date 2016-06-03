#include "Agent.h"


Agent::Agent()
{
    ReceivedForecast	= 0;
    d_differential = 0;
}


Agent::~Agent()
{
}

double Agent::getValue() const
{
    return d_value;
}

void Agent::setValue(double value)
{
    Agent::d_value = value;
}

double Agent::getDifferential() const
{
    return d_differential;
}

void Agent::setDifferential(double differential)
{
    Agent::d_differential = differential;
}

double Agent::getReceivedForecast() const
{
    return ReceivedForecast;
}

void Agent::setReceivedForecast(double ReceivedForecast)
{
    Agent::ReceivedForecast = ReceivedForecast;
}