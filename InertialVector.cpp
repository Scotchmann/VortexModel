//
// Created by vortex on 13.05.16.
//

#include "InertialVector.h"

double InertialVector::getValue() const
{
    return d_value;
}

void InertialVector::setValue(double value)
{
    InertialVector::d_value = value;
}

double InertialVector::getReliability() const
{
    return d_reliability;
}

void InertialVector::setReliability(double reliability)
{
    InertialVector::d_reliability = reliability;
}

int InertialVector::getDistance() const
{
    return i_distance;
}

void InertialVector::setDistance(int distance)
{
    InertialVector::i_distance = distance;
}