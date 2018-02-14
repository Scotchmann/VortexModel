//
// Created by vortex on 13.05.16.
//

#ifndef VORTEXMODEL_LINUX_INERTIALVECTOR_H
#define VORTEXMODEL_LINUX_INERTIALVECTOR_H


class InertialVector
{
//--------------------------------------------------------------------------------------------------
public://  ПУБЛИЧНАЯ СЕКЦИЯ
//--------------------------------------------------------------------------------------------------

//__Конструкторы____________________________________________________________________________________

	InertialVector();

//__Публичные_методы________________________________________________________________________________

	// получает значение
    double getValue() const;

	// устанавливает значение
    void setValue(double value);

    // получает надежность
	double getReliability() const;

	// устанавливает надежность
    void setReliability(double reliability);

    // получает дистанцию
    int getDistance() const;

	// устанавливает дистанцию
    void setDistance(int distance);

    // получает вариативность
	int getVariability() const;

	// устанавливает вариативность
    void setVariability(int variability);

//--------------------------------------------------------------------------------------------------
private://  ПРИВАТНАЯ СЕКЦИЯ
//--------------------------------------------------------------------------------------------------

//__Приватные поля__________________________________________________________________________________

    double  d_value;          // значение инерции
    double  d_reliability;    // надежность инерции
    int     i_distance;       // дистанция инерции
    int		i_variability;    // вариативность
};


#endif //VORTEXMODEL_LINUX_INERTIALVECTOR_H
