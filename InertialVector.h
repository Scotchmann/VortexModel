//
// Created by vortex on 13.05.16.
//

#ifndef VORTEXMODEL_LINUX_INERTIALVECTOR_H
#define VORTEXMODEL_LINUX_INERTIALVECTOR_H


class InertialVector
{

public:

	//--
	//--Публичные методы
	//--
	
    double  getValue		() const;
    void    setValue		(double value);

    double  getReliability	() const;
    void    setReliability	(double reliability);

    int     getDistance		() const;
    void    setDistance		(int distance);

private:

	//--
	//--Приватные поля
	//--
	
    double  d_value;        // Значение инерции
    double  d_reliability;  // Надежность инерции
    int     i_distance;	    // Дистанция инерции

};


#endif //VORTEXMODEL_LINUX_INERTIALVECTOR_H
