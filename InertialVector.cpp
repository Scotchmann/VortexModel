//
// Created by vortex on 13.05.16.
//

#include "InertialVector.h"

InertialVector::InertialVector()
{
	d_value 		= 0;
	d_reliability 	= 0;
	i_distance 		= 0;
	i_variability 	= 0;
}

double InertialVector::getValue() const
{
    return d_value;
}

void InertialVector::setValue(double value)
{
    d_value = value;
}

double InertialVector::getReliability() const
{
    return d_reliability;
}

void InertialVector::setReliability(double reliability)
{
    d_reliability = reliability;
}

int InertialVector::getDistance() const
{
    return i_distance;
}

void InertialVector::setDistance(int distance)
{
    i_distance = distance;
}

int InertialVector::getVariability() const
{
    return i_variability;
}

void InertialVector::setVariability(int variability)
{
    i_variability = variability;
}