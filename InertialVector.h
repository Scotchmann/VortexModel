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
	
    double  getValue		() const;               // Получает значение
    void    setValue		(double value);         // Устанавливает значение

    double  getReliability	() const;               // Получает надежность
    void    setReliability	(double reliability);   // Устанавливает надежность

    int     getDistance		() const;               // Получает дистанцию
    void    setDistance		(int distance);         // Устанавливает дистанцию

private:

	//--
	//--Приватные поля
	//--
	
    double  d_value;        // Значение инерции
    double  d_reliability;  // Надежность инерции
    int     i_distance;	    // Дистанция инерции
};


#endif //VORTEXMODEL_LINUX_INERTIALVECTOR_H
