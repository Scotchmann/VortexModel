#include "Agent.h"


Agent::Agent()
{

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

DifferentialSet Agent::getDifferential() const
{
    return d_differential;
}

void Agent::setDifferential(DifferentialSet differential)
{
    Agent::d_differential = differential;
}
