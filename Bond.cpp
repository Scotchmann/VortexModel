
#include "Bond.h"
#include <limits>

Bond::Bond()
{
    d_maxDouble = std::numeric_limits<double>::max();
}

Bond::Bond(Pole * source_Pole, Pole * target_Pole, double easing_Ratio, double strengthen_step )
{
    ptr_source_Pole = source_Pole;
    ptr_target_Pole = target_Pole;
    d_easing_Ratio = easing_Ratio;
    d_reliability = 1;
    d_strengthen_Step = strengthen_step;
    d_maxDouble = std::numeric_limits<double>::max();
}

Bond::~Bond()
{
}

///--
///--Укрепляет связь
///--
bool Bond::Strengthen(double Step)
{
    ///--
    ///--Укрепляем пока значение мешьне максимального размера типа
    ///--
    double _Step = d_strengthen_Step;
    if (Step > 0)
    {
        _Step = Step;
    }

//    if(d_reliability < d_maxDouble)
//    {
//        d_reliability = d_reliability + _Step;
//    }

    d_reliability = 1;

    return false;
}

///--
///--Ослабляет связь на коэффициент ослабления
///--
bool Bond::Ease()
{

    d_reliability = d_reliability - ((double)d_strengthen_Step * d_easing_Ratio);

    return false;

}

double Bond::getReliability() const
{
    return d_reliability;
}

Pole * Bond::getTargetPole()
{
    return ptr_target_Pole;
}





