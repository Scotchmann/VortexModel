#pragma once
#include "vector"
#include "map"


using namespace std;
class Pole;

class Bond
{
public:

    ///--
    ///--Конструкторы
    ///--
    Bond	();
    Bond	(Pole * source_Pole, Pole * target_Pole, double easing_Ratio, double stengthen_step = 1);

    ///--
    ///--Деструкторы
    ///--
    ~Bond	();

    ///--
    ///--Публичные поля
    ///--
    Pole * ptr_source_Pole = nullptr;	// Полюс источник
    Pole * ptr_target_Pole = nullptr;	// Целевой полюс
    double d_value;						// Значение


    ///--
    ///--Публичные методы
    ///--
    bool Strengthen	        (double Step = 0);  // Укрепить связь
    bool Ease		        ();                 // Ослабить связь
    double GetReliability   () const;           // Получить надежность


private:



    ///--
    ///--Приватные поля
    ///--
    double d_strengthen_Step;									// Шаг укрепления
    double d_easing_Ratio;										// Коэффициент ослабления
    double d_reliability;				                        // Надежность
    double d_maxDouble;											// Максимальное значение типа

};

