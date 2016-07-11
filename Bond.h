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
    
	bool 	Strengthen	   	(double Step = 0);  // укрепить связь
    bool 	Ease		   	();                 // ослабить связь
    double 	getReliability	() const;           // получить надежность
    Pole * 	getTargetPole	();                 // получить целевой полюс

private:

//_______________________________________________________________________________________________

    //--
    //--Приватные поля
    //--
	//Pole * ptr_source_Pole = nullptr;			// полюс источник
    double d_strengthen_Step;					// шаг укрепления
    double d_easing_Ratio;						// коэффициент ослабления
    double d_reliability;				       	// надежность
    double d_maxDouble;							// максимальное значение типа
    Pole * ptr_target_Pole = nullptr;	       	// целевой полюс
};

#endif //VORTEXMODEL_LINUX_BOND_H
