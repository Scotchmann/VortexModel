#pragma once

class Agent
{
public:
    Agent();
    ~Agent();

    double value;
    double differential;
    double previous_differential;
    double reliability;
    Agent * InnerAgent;

    double ReceivedForecast;

private:

};

