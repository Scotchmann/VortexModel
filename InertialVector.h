//
// Created by vortex on 13.05.16.
//

#ifndef VORTEXMODEL_LINUX_INERTIALVECTOR_H
#define VORTEXMODEL_LINUX_INERTIALVECTOR_H


class InertialVector
{

public:

//_______________________________________________________________________________________________

	//--
	//--Публичные методы
	//--
	
    double  getValue		() const;               // получает значение
    void    setValue		(double value);         // устанавливает значение

    double  getReliability	() const;               // получает надежность
    void    setReliability	(double reliability);   // устанавливает надежность

    int     getDistance		() const;               // получает дистанцию
    void    setDistance		(int distance);         // устанавливает дистанцию

private:

//_______________________________________________________________________________________________

	//--
	//--Приватные поля
	//--
	
    double  d_value;        // значение инерции
    double  d_reliability;  // надежность инерции
    int     i_distance;	    // дистанция инерции
};


#endif //VORTEXMODEL_LINUX_INERTIALVECTOR_H
