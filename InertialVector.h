//
// Created by vortex on 13.05.16.
//

#ifndef VORTEXMODEL_LINUX_INERTIALVECTOR_H
#define VORTEXMODEL_LINUX_INERTIALVECTOR_H


class InertialVector
{
public:

    double  getValue() const;
    void    setValue(double value);

    double  getReliability() const;
    void    setReliability(double reliability);

    int     getDistance() const;
    void    setDistance(int distance);

private:

    double  value;		    // Значение инерции
    double  reliability;    // Надежность инерции
    int     distance;	    // Дистанция инерции

};


#endif //VORTEXMODEL_LINUX_INERTIALVECTOR_H
