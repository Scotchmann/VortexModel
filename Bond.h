#ifndef VORTEXMODEL_LINUX_BOND_H
#define VORTEXMODEL_LINUX_BOND_H

#include <vector>
#include "map"


using namespace std;
class Pole;

class Bond
{
	
public:

    //--
    //--Конструкторы
    //--
	
    Bond	();
    Bond	(Pole * source_Pole, Pole * target_Pole, double easing_Ratio, double strengthen_step = 1.1);

//_______________________________________________________________________________________________	
    
	//--
    //--Деструкторы
    //--
    
	~Bond	();

//_______________________________________________________________________________________________
	
    //--
    //--Публичные методы
    //--
    
	bool 	Strengthen	   	(double Step = 0);  // Укрепить связь
    bool 	Ease		   	();                 // Ослабить связь
    double 	getReliability	() const;           // Получить надежность
    Pole * 	getTargetPole	();                 // Получить целевой полюс

private:

//_______________________________________________________________________________________________

    //--
    //--Приватные поля
    //--
	//Pole * ptr_source_Pole = nullptr;			// Полюс источник
    double d_strengthen_Step;					// Шаг укрепления
    double d_easing_Ratio;						// Коэффициент ослабления
    double d_reliability;				       	// Надежность
    double d_maxDouble;							// Максимальное значение типа
    Pole * ptr_target_Pole = nullptr;	       	// Целевой полюс
};

#endif //VORTEXMODEL_LINUX_BOND_H
