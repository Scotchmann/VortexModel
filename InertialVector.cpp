//
// Created by vortex on 13.05.16.
//

#include "InertialVector.h"

double InertialVector::getValue() const
{
    return value;
}

void InertialVector::setValue(double value)
{
    InertialVector::value = value;
}

double InertialVector::getReliability() const
{
    return reliability;
}

void InertialVector::setReliability(double reliability)
{
    InertialVector::reliability = reliability;
}

int InertialVector::getDistance() const
{
    return distance;
}

void InertialVector::setDistance(int distance)
{
    InertialVector::distance = distance;
}