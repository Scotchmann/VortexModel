
#include "Vortex.h"
#include "VortexModel.h"

using namespace std;

Vortex::Vortex()
{
    int_ArraySize = 0;
    int_Generation = 0;
    //_Vortexes = VortexArray(300);
}

///--
///--Конструктор класса
///--	ArraySize 	- Глубина треугольной матрицы
///--	Generation 	- Поколение
///--	Step		- Шаг расстановки полюсов в кольце, по умолчанию - 2%
///--
Vortex::Vortex(int ArraySize, int Generation, double Step, int MaxSizeOfRing, double EasingRatio)
{
    ///--
    ///--Заполняем внутренние переменные
    ///--
    int_ArraySize 		= ArraySize;
    int_Generation		= Generation;
    int_Step			= Step;
    int_MaxSizeOfRing	= MaxSizeOfRing;
    d_Easing_ratio		= EasingRatio;
}

///--
///--Деструктор класса
///--
Vortex::~Vortex()
{

}

///--
///--Заведение агента в вихрь
///--	value 	-	следующее значение
///--
double Vortex::pushAgent(double value)
{



    ///--
    ///--Проверяем очередь на полноту
    ///--И если очередь полна, то удаляем первый элемент в очереди
    ///--
    if (_Agents.size() == int_ArraySize + 1)
    {
        _Agents.begin()->clear();
        _Agents.erase(_Agents.begin());
    }

    ///--
    ///--Добавляем горизонтальную струну
    ///--
    _Agents.push_back(vector<Agent>((unsigned long)int_ArraySize));

    ///--
    ///--Определяем текущий размер массива
    ///--
    int vecSize = (int)_Agents.size();

    ///--
    ///--Присваем значение агенту в струне
    ///--
    _Agents[vecSize - 1][0].value = value;

    if (vecSize > 1)
    {
        ///--
        ///--Рекурсивно пересчитываем струны в треугольной матрице
        ///--
        RecalculationOfMainPool(vecSize - 1, 0, &_Agents, 2);
    }

    ///--
    ///--Возращаем размер массива
    ///--

    //if (ForecastVector.size() > 0)
    //{
    //	//sort(ForecastVector.begin(), ForecastVector.end(), ForecastComparatorObject);
    //	return ForecastVector[0].value;
    //}

    double fvecsize = 0;
    fvecsize = (double)ForecastVector.size();


    CheckIfForecastIsEmty:
    for (auto it = ForecastVector.begin(); it != ForecastVector.end(); ++it)
    {
        delete *it;
        ForecastVector.erase(it);
        goto CheckIfForecastIsEmty;
    }


    //return fvecsize;
    return (double)vecSize;

}

double Vortex::GetAgent(int i, int j)
{
    return (double)PolesRing.size();
}

double Vortex::GetBuf()
{
    return 0;
}

///--
///--Получение дистанции прогноза
///--
int Vortex::GetDistance()
{
    if (ForecastVector.size() > 0)
    {
        sort(ForecastVector.begin(), ForecastVector.end(), ForecastComparatorObject);
        return ForecastVector[0]->distance;
    }
    return 0;
}



///--
///--Рекурсивно пересчитывает вихрь
///--	i 			- координата строки в треугольной матрице
///--	j 			- координата столбца в треугольной матрице
///--	ptr_array 	- указатель на треугольную матрицу
///--	level		- глубина цикла
///--
void Vortex::RecalculationOfMainPool(int i, int j, AgentsArray * ptr_array, int level)
{

    //Agent * ptr_currentInnerAgent = (*ptr_array)[i - 1][j + 1].InnerAgent;

    Forecast * fcst = new Forecast();

    ///--
    ///--Выстраиваем треугольную суммирующую матрицу
    ///--

    /*

                                                               22

                                                    21       (0.2)        17

                                        19       (0.400)       16      (0.250)        13

                             12       (1.400)       14      (0.500)       12       (0.333)      10

                   9       (0.600)       7       (1.750)       10      (0.666)         9      (0.142)       3

        5       (0.800)       4       (0.750)        3      (2.333)        7       (0.285)       2       (0.500)       1



    */



    ///--
    ///--В начале пересчета столбец является нулевым, поэтому
    ///--расчитываем по схеме без вычитаемого узла
    ///--
    if (j == 0)
    {
        ///--
        ///--Если мы еще не дошли до нулевой строки
        ///--тогда расчитываем узлы по схеме:
        ///--
        if (i > 0)
        {
            ///--
            ///-- предыдущий________________рассчитываемый
            ///--                  |
            ///-- текущий__________|
            ///--

            /*расчитываемый*/(*ptr_array)[i - 1][j + 1].value =		/*текущий*/(*ptr_array)[i][j].value		+	/*предыдущий*/(*ptr_array)[i - 1][j].value;

        }
    }

        ///--
        ///--Если текущий столбец не нулевой и меньше конечного индекса столбца в струне
        ///--тогда:
        ///--
    else if (j > 0 && j < int_ArraySize - 1)
    {
        ///--
        ///--Если мы еще не дошли до нулевой строки
        ///--тогда расчитываем узлы по схеме:
        ///--
        if (i > 0)
        {
            ///--
            ///--                  _______предыдущий _______________рассчитываемый
            ///--				  |						   	|
            ///-- вычитаемый______|_______текущий___________|
            ///--

            /*расчитываемый*/	(*ptr_array)[i - 1][j + 1].value	=	/*текущий*/		(*ptr_array)[i][j].value	+	/*предыдущий*/(*ptr_array)[i - 1][j].value	-
                                                                        /*вычитаемый*/	(*ptr_array)[i][j - 1].value;

            ///--
            ///--Заводим значение в кольцо полюсов (PolesRing)
            ///--
            if (level > 0)
            {
                ///--
                ///--При заведении значения в колцо полюсов определяем, возможно ли
                ///--взять предыдущее значение
                ///--
                /*

                      |      |      |      |
                      |   L  |   L  |   L  |
                ______|______|______|______|
                      |      |      |      |
                   i  |   1  |   2  |   3  |
                ______|______|______|______|
                      |      |      |      |
                   i  |   2  |      |      |
                ______|______|______|______|
                      |      |      |      |
                   i  |   3  |      |      |
                ______|______|______|______|


                */

                ///--
                ///--Если мы не дошли до равенства строки и уровня цикла
                ///--то берем текущее и предыщущее значение по циклу и заводим их в кольцо
                ///--
                if (i - 1 >= level )
                {
                    //if ((*ptr_array)[i - 1 - level][j + 1].ReceivedForecast > 0)
                    //{
                    //	fcst =	PushToPolesRing (	(	(
                    //										(*ptr_array)[i - 1][j + 1].value +	(*ptr_array)[i - 1 - level][j + 1].ReceivedForecast
                    //									) / 2															// получаем среднее арифметическое между фактическим и спрогнозированным значением
                    //								) / level,															// текущее значение по циклу
                    //									(*ptr_array)[i - 1 - level][j + 1].value / level				// предыдущее значение по циклу
                    //							);
                    //}
                    //else
                    //{
                    fcst =	PushToPolesRing(
                            (*ptr_array)[i - 1][j + 1].value / level,				// текущее значение по циклу
                            (*ptr_array)[i - 1 - level][j + 1].value / level		// предыдущее значение по циклу
                    );
                    //}


                    //--
                    //--Формируем и заводим деноминатор в кольцо деноминаторов
                    //--

                    /*

                    				A




                    		B				C
                    	  (i-1)			   (i)

                    */

                    //--	Denominator = (A-B)/(A-C)

                    /*
                        double Denominator     	= 	((*ptr_array)[i - 1][j + 1].value - (*ptr_array)[i][j - 1].value)
                                                 /	((*ptr_array)[i - 1][j + 1].value - (*ptr_array)[i][j].value);

                        double prev_Denominator	= 	((*ptr_array)[i - 1 - level][j + 1].value - (*ptr_array)[i - level][j - 1].value)
                                                 /	((*ptr_array)[i - 1 - level][j + 1].value - (*ptr_array)[i - level][j].value);


                        Forecast * fcst_denom = PushToDenominatorsRing(Denominator, prev_Denominator);
                    */


                    if(fcst != nullptr)
                    {
                        fcst->value = fcst->value * level;
                        fcst->distance = level;
                        ForecastVector.push_back(fcst);
                        (*ptr_array)[i - 1][j + 1].ReceivedForecast = fcst->value;
                    }
                }
                    //--
                    //--Если значение уровня больше номера строки то заводим в кольцо только текущее значение
                    //--
                else
                {
                    fcst = PushToPolesRing((*ptr_array)[i - 1][j + 1].value / level);

                    if (fcst != nullptr)
                    {
                        fcst->value = fcst->value * level;
                        fcst->distance = level;
                        ForecastVector.push_back(fcst);
                        (*ptr_array)[i - 1][j + 1].ReceivedForecast = fcst->value;
                    }
                }
            }
        }
    }

    ///--
    ///--Если мы не дошли до нулевой строки и не превзошли
    ///--максимальный индекс для столбцов в строке, то
    ///--продолжаем рекурсию по схеме:
    ///--        |             |             |
    ///--        |      j      |     j+1     |
    ///-- _______|_____________|_____________|
    ///--        |
    ///--   i-1  |              _> текущий'
    ///-- _______|             |
    ///--        |             |
    ///--    i   |  текущий >__|
    ///-- _______|
    ///--
    if (i > 0 && j < int_ArraySize - 1)
    {
        RecalculationOfMainPool(i - 1, j + 1, ptr_array, level + 1);
    }
    else
    {
        return; // вектор прогноза
    }
}

///--
///--Заводит значение треугольной матрицы в кольцо
///--	value	- текущее заводимое значение
///--
Forecast * Vortex::PushToPolesRing(	double value,		// заводимое в кольцо значение
                                    double prev_value	// предыщущее значение в цикле для которого подходящий полюс уже есть
)
{

    ///--
    ///--Переменная для хранения имеющегося prev_value полюса
    ///--
    Pole * ptr_SourcePole = nullptr;


    ///--
    ///--Переменная для хранения добавленного полюса (или имеющегося) полюса
    ///--для последующей привязки в connections для имеющегося prev_value полюса
    ///--
    Pole * ptr_TargetPole = nullptr;

    Forecast * Answer = nullptr;


    ///--
    ///--Сортируем кольцо полюсов (PolesRing)
    ///--
    //sort(PolesRing.begin(), PolesRing.end(), PoleComparatorObject);


    /////////////
    //         //
    // 1  ЭТАП //
    //         //
    /////////////

    ///--
    ///--Перебираем кольцо полюсов
    /*                                                       1
    |                                              28        *        2
    |                                           27   *               *   3
    |                                        26   *                     *   4
    |                                           *    \       |       /    *
    |                                      25 *                             * 5
    |                                     24 *                               * 6
    |                                    23 *               \ /               * 7
    |                                    22 *    -   -     - + -     -   -    * 8
    |                                    21 *               / \               * 9
    |                                     20 *                               * 10
    |                                      19 *                             * 11
    |                                        18 *    /       |       \    * 12
    |                                           17*                     *13
    |                                             16 *               * 14
    |                                                        *
    |                                                        15
    */
    ///--


    ///--
    ///--Если кольцо пустое, то добавим сразу полюс в кольцо
    ///--с текущим значением
    ///--

    if (PolesRing.size() == 0)
    {
        Pole * ptr_NewPole = new Pole(value);
        AddNewPoleToPolesRing(ptr_NewPole, true);

        ptr_TargetPole = ptr_NewPole;	// связываем целевой полюс с новым
    }
        ///--
        ///--Если в кольце есть одно значение
        ///--то сравниваем это значение со входящим
        ///--
    else if (PolesRing.size() == 1)
    {
        ///--
        ///--Выясняем больше ли вводимое значение текущего перебираемого полюса
        ///--чем на _Step процентов
        ///--
        double bias = 0;

        if (value > PolesRing[0]->GetValue())
        {
            bias = 100 - PolesRing[0]->GetValue() / (value / 100);
        }
        else
        {
            bias = 100 - value / (PolesRing[0]->GetValue() / 100);
        }

        ///--
        ///--Если больше, то создаем новый полюс в кольце
        ///--
        if (bias > int_Step)
        {
            Pole * ptr_NewPole = new Pole(value);

            ///--
            ///--Если заводимое значение больше нулевого полюса
            ///--то:
            ///--
            if (value > PolesRing[0]->GetValue())
            {
                //добавляем в конец
                AddNewPoleToPolesRing(ptr_NewPole, true);
            }
                ///--
                ///--В другом случае
                ///--
            else
            {
                ///--
                ///--добавляем в начало
                ///--тем самым сохраняя упорядоченность кольца по возрастанию
                ///--
                AddNewPoleToPolesRing(ptr_NewPole, false, 0);
            }

            ptr_TargetPole = ptr_NewPole;	// связываем целевой полюс с новым
        }
        else
        {
            ptr_TargetPole = PolesRing[0];	// связываем целевой полюс с новым
        }

    }
        ///--
        ///--Определяем нужно ли добавить новый полюс или работать с уже существующим
        ///--Полюса вероятностей создаются с шагом в _Step процентов
        ///--
    else if (PolesRing.size() > 1)
    {

        for (int i = 0; i != PolesRing.size(); ++i)	// Цикл перебора кольца
        {

            if (value == PolesRing[i]->GetValue())
            {
                Answer = ProcessPole(PolesRing[i], value);	// формируем ответ
                ptr_TargetPole = PolesRing[i];				// связываем целевой полюс с новым
                break;
            }

            else if (i == 0 && value > PolesRing[i]->GetValue())
            {
                continue;
            }
                ///--
                ///--Если мы находимся в начале перебора кольца и
                ///--значение уже меньше текущего и предыдущего полюсов
                ///--то выясняем нужно ли добавлять в начало новый полюс
                ///--или работать с первым
                ///--
            else if ((i == 0 && value < PolesRing[i]->GetValue()) || (i == 1 && value < PolesRing[i]->GetValue() && value < PolesRing[i - 1]->GetValue()))
            {

                ///--
                ///--Выясняем больше ли вводимое значение текущего перебираемого полюса
                ///--чем на _Step процентов
                ///--
                double bias = 0;

                bias = 100 - value / (PolesRing[0]->GetValue() / 100);

                ///--
                ///--Если больше, то создаем новый полюс в кольце
                ///--
                if (bias > int_Step)
                {
                    Pole * ptr_NewPole = new Pole(value);
                    AddNewPoleToPolesRing(ptr_NewPole, false, 0);

                    ptr_TargetPole = ptr_NewPole;				// связываем целевой полюс с новым
                }
                    ///--
                    ///--В противном случае работаем с имеющимся полюсом
                    ///--
                else
                {
                    Answer = ProcessPole(PolesRing[0], value);	// формируем ответ
                    ptr_TargetPole = PolesRing[0];				// связываем целевой полюс с новым
                }
                break;
            }
                ///--
                ///--Если заводимое значение меньше текущего перебираемого полюса и больше предыдущего
                ///--перебранного полюса, то пытаемся втиснуть заводимое значение между ними.
                ///--
            else if (i > 0 && value < PolesRing[i]->GetValue() && value > PolesRing[i - 1]->GetValue())
            {
                ///--
                ///--Для этого:
                ///--	из текущего перебираемого полюса вычитаем заводимое значение
                ///--	из заводимого значения вычитаем предыдущий перебранный полюс
                ///--
                double a = PolesRing[i]->GetValue() - value;		// разность между текущим перебираемым полюсом и заводимым значением
                double b = value - PolesRing[i - 1]->GetValue();	// разность между заводимым значением и предыдущим перебранным
                double bias = 0;								    // переменная для хранения смещения в процентах
                Pole * ptr_PoleToWorkWith = nullptr;			    // переменная для записи рабочего полюса

                ///--
                ///--Затем вычисляем смещение в процентах относительно наименьшей разности
                ///--Для этого оцениваем какая из разностей меньше
                ///--Если разница текущего полюса меньше, берем за его 100 процентов
                ///--Если меньше разница предыдущего полюса, берем вводимое значение за 100 процентов
                ///--Затем вычисляем смещение в процентах между полюсом и вводимым значением
                ///--
                if (a < b)
                {
                    bias = 100 - value / (PolesRing[i]->GetValue() / 100);
                    ptr_PoleToWorkWith = PolesRing[i];						// Назначаем рабочий полюс
                }
                else
                {
                    bias = 100 - PolesRing[i - 1]->GetValue() / (value / 100);
                    ptr_PoleToWorkWith = PolesRing[i - 1];					// --
                }

                ///--
                ///--Если это смещение больше _Step процентов, тогда создаем новый полюс
                ///--
                if (bias > int_Step)
                {
                    Pole * ptr_NewPole = new Pole(value);

                    ///--
                    ///--Вставляем новый полюс между двумя перебираемыми полюсами
                    ///--
                    AddNewPoleToPolesRing(ptr_NewPole, false, i);

                    ptr_TargetPole = ptr_NewPole;	// связываем целевой полюс с новым

                }
                    ///--
                    ///--Если смещение меньше _Step процентов, тогда считаем рабочий полюс
                    ///--Пересчитываем значения и связи
                    ///--
                else
                {
                    Answer = ProcessPole(ptr_PoleToWorkWith, value);
                    ptr_TargetPole = ptr_PoleToWorkWith;
                }

                break;
            }

            else if (i > 0 && (i < PolesRing.size() - 1) && value > PolesRing[i]->GetValue() && value > PolesRing[i - 1]->GetValue())
            {
                continue;
            }
                ///--
                ///--Если же перешли к конечному полюсу
                ///--и заводимое значение всё ещё больше текущего перебираемого полюса
                ///--и предыдущего перебранного полюса
                ///--то:
                ///--
            else if ((i == PolesRing.size() - 1) && value > PolesRing[i]->GetValue() && value > PolesRing[i - 1]->GetValue())
            {
                ///--
                ///--Выясняем больше ли вводимое значение текущего перебираемого полюса
                ///--чем на _Step процентов
                ///--
                double bias = 0;
                bias = 100 - PolesRing[i]->GetValue() / (value / 100);

                ///--
                ///--Если больше, то создаем новый полюс в кольце
                ///--
                if (bias > int_Step)
                {
                    Pole * ptr_NewPole = new Pole(value);
                    AddNewPoleToPolesRing(ptr_NewPole, true, i);

                    ptr_TargetPole = ptr_NewPole;
                }
                    ///--
                    ///--Если меньше, то работаем с текущим перебираемым полюсом
                    ///--
                else
                {
                    Answer = ProcessPole(PolesRing[i], value);
                    ptr_TargetPole = PolesRing[i];
                }

                break;
            }
                ///--
                ///--Отладочная ветвь
                ///--
            else
            {
                int check = 0;
            }
        }
    }

    /////////////
    //         //
    // 2  ЭТАП //
    //         //
    /////////////

    ///--
    ///--Если передано предыдущее значение (не равно нулю)
    ///--то найдем полюс, соотвествующий предыдущему значению
    ///--

    if(prev_value != 0)
    {
        for (int i = 0; i != PolesRing.size(); ++i)
        {
            double d_max = max(prev_value, PolesRing[i]->GetValue());	// максимальное значение
            double d_min = min(prev_value, PolesRing[i]->GetValue());	// минимальное значение
            double bias = 100 - d_min / (d_max / 100);				// смещение в процентах между максимальным
                                                                    // и минимальным значением относительно максимального

            if(bias < int_Step)
            {
                ///--
                ///--Если смещение менее _Step процентов значит
                ///--полюс найден
                ///--
                ptr_SourcePole = PolesRing[i];	// найденный полюс

                ///--
                ///--Далее перебираем связи в найденном полюсе
                ///--и если в связях мы обнаружили связь которая
                ///--указывает на текущее переданное значение
                ///--то укрепляем её
                ///--если нет - создаем новую связь
                ///--

                int _ConnectionsSize = (int)(PolesRing[i]->Connections.size());	// количество связей
                bool IsBondFound = false;										// флаг для записи признака найдена ли связь

                ///--
                ///--Цикл перебора связей
                ///--
                for (int j = 0; j != _ConnectionsSize; ++j)
                {
                    ///--
                    ///--Если указатели соотвествуют
                    ///--то укрепляем связь
                    ///--
                    if (ptr_SourcePole->Connections[j]->GetTargetPole() == ptr_TargetPole)
                    {
                        IsBondFound = true;								// взводим флаг, так как связь найдена
                        ptr_SourcePole->Connections[j]->Strengthen(); 	// укрепляем связь
                    }
                }

                ///--
                ///--Если связь не найдена
                ///--Создадим новую
                ///--
                if (!IsBondFound)
                {
                    Bond * NewBond = new Bond(ptr_SourcePole, ptr_TargetPole, d_Easing_ratio);	// новая связь
                    ptr_SourcePole->Connections.push_back(NewBond);								// заводим связь

                    ///--
                    ///--После добавления сортируем связи в полюсе
                    ///--
                    ptr_SourcePole->SortSourceConnections();
                }
            }
        }
    }

    ///--
    ///--Ослабляем все связи
    ///--
    for (int i = 0; i != PolesRing.size(); ++i)
    {
        PolesRing[i]->EaseAllBonds();
    }

    return Answer;
}

Forecast * Vortex::PushToDenominatorsRing( double denominator,			// заводимый деноминатор в кольцо деноминаторов
                                           double prev_denominator		// предыдущий деноминатор
)
{
    ///--
    ///--Переменная для хранения имеющегося prev_value полюса
    ///--
    Pole * ptr_SourcePole = nullptr;


    ///--
    ///--Переменная для хранения добавленного полюса (или имеющегося) полюса
    ///--для последующей привязки в connections для имеющегося prev_value полюса
    ///--
    Pole * ptr_TargetPole = nullptr;

    Forecast * Answer = nullptr;


    ///--
    ///--Сортируем кольцо деноминаторов (DenominatorsRing)
    ///--


    /////////////
    //         //
    // 1  ЭТАП //
    //         //
    /////////////

    ///--
    ///--Перебираем кольцо деноминаторов
    /*                                                       1
    |                                              28        *        2
    |                                           27   *               *   3
    |                                        26   *                     *   4
    |                                           *    \       |       /    *
    |                                      25 *                             * 5
    |                                     24 *                               * 6
    |                                    23 *               \ /               * 7
    |                                    22 *    -   -     - + -     -   -    * 8
    |                                    21 *               / \               * 9
    |                                     20 *                               * 10
    |                                      19 *                             * 11
    |                                        18 *    /       |       \    * 12
    |                                           17*                     *13
    |                                             16 *               * 14
    |                                                        *
    |                                                        15
    */
    ///--


    ///--
    ///--Если кольцо пустое, то добавим сразу полюс в кольцо
    ///--с текущим значением
    ///--

    if (DenominatorsRing.size() == 0)
    {
        Pole * ptr_NewPole = new Pole(denominator);
        AddNewPoleToPolesRing(ptr_NewPole, true);

        ptr_TargetPole = ptr_NewPole;	// связываем целевой полюс с новым
    }
        ///--
        ///--Если в кольце есть одно значение
        ///--то сравниваем это значение со входящим
        ///--
    else if (DenominatorsRing.size() == 1)
    {
        ///--
        ///--Выясняем больше ли вводимое значение текущего перебираемого полюса
        ///--чем на _Step процентов
        ///--
        double bias = 0;

        if (denominator > DenominatorsRing[0]->GetValue())
        {
            bias = 100 - DenominatorsRing[0]->GetValue() / (denominator / 100);
        }
        else
        {
            bias = 100 - denominator / (DenominatorsRing[0]->GetValue() / 100);
        }

        ///--
        ///--Если больше, то создаем новый полюс в кольце
        ///--
        if (bias > int_Step)
        {
            Pole * ptr_NewPole = new Pole(denominator);

            ///--
            ///--Если заводимое значение больше нулевого полюса
            ///--то:
            ///--
            if (denominator > DenominatorsRing[0]->GetValue())
            {
                //добавляем в конец
                AddNewPoleToPolesRing(ptr_NewPole, true);
            }
                ///--
                ///--В другом случае
                ///--
            else
            {
                ///--
                ///--добавляем в начало
                ///--тем самым сохраняя упорядоченность кольца по возрастанию
                ///--
                AddNewPoleToPolesRing(ptr_NewPole, false, 0);
            }

            ptr_TargetPole = ptr_NewPole;	// связываем целевой полюс с новым
        }
        else
        {
            ptr_TargetPole = DenominatorsRing[0];	// связываем целевой полюс с новым
        }

    }
        ///--
        ///--Определяем нужно ли добавить новый полюс или работать с уже существующим
        ///--Полюса вероятностей создаются с шагом в _Step процентов
        ///--
    else if (DenominatorsRing.size() > 1)
    {

        for (int i = 0; i != DenominatorsRing.size(); ++i)	// Цикл перебора кольца
        {

            if (denominator == DenominatorsRing[i]->GetValue())
            {
                Answer = ProcessPole(DenominatorsRing[i], denominator);	// формируем ответ
                ptr_TargetPole = DenominatorsRing[i];				// связываем целевой полюс с новым
                break;
            }

            else if (i == 0 && denominator > DenominatorsRing[i]->GetValue())
            {
                continue;
            }
                ///--
                ///--Если мы находимся в начале перебора кольца и
                ///--значение уже меньше текущего и предыдущего полюсов
                ///--то выясняем нужно ли добавлять в начало новый полюс
                ///--или работать с первым
                ///--
            else if ((i == 0 && denominator < DenominatorsRing[i]->GetValue()) || (i == 1 && denominator < DenominatorsRing[i]->GetValue() && denominator < DenominatorsRing[i - 1]->GetValue()))
            {

                ///--
                ///--Выясняем больше ли вводимое значение текущего перебираемого полюса
                ///--чем на _Step процентов
                ///--
                double bias = 0;

                bias = 100 - denominator / (DenominatorsRing[0]->GetValue() / 100);

                ///--
                ///--Если больше, то создаем новый полюс в кольце
                ///--
                if (bias > int_Step)
                {
                    Pole * ptr_NewPole = new Pole(denominator);
                    AddNewPoleToPolesRing(ptr_NewPole, false, 0);

                    ptr_TargetPole = ptr_NewPole;				// связываем целевой полюс с новым
                }
                    ///--
                    ///--В противном случае работаем с имеющимся полюсом
                    ///--
                else
                {
                    Answer = ProcessPole(DenominatorsRing[0], denominator);	// формируем ответ
                    ptr_TargetPole = DenominatorsRing[0];				// связываем целевой полюс с новым
                }
                break;
            }
                ///--
                ///--Если заводимое значение меньше текущего перебираемого полюса и больше предыдущего
                ///--перебранного полюса, то пытаемся втиснуть заводимое значение между ними.
                ///--
            else if (i > 0 && denominator < DenominatorsRing[i]->GetValue() && denominator > DenominatorsRing[i - 1]->GetValue())
            {
                ///--
                ///--Для этого:
                ///--	из текущего перебираемого полюса вычитаем заводимое значение
                ///--	из заводимого значения вычитаем предыдущий перебранный полюс
                ///--
                double a = DenominatorsRing[i]->GetValue() - denominator;		// разность между текущим перебираемым полюсом и заводимым значением
                double b = denominator - DenominatorsRing[i - 1]->GetValue();	// разность между заводимым значением и предыдущим перебранным
                double bias = 0;								// переменная для хранения смещения в процентах
                Pole * ptr_PoleToWorkWith = nullptr;			// переменная для записи рабочего полюса

                ///--
                ///--Затем вычисляем смещение в процентах относительно наименьшей разности
                ///--Для этого оцениваем какая из разностей меньше
                ///--Если разница текущего полюса меньше, берем за его 100 процентов
                ///--Если меньше разница предыдущего полюса, берем вводимое значение за 100 процентов
                ///--Затем вычисляем смещение в процентах между полюсом и вводимым значением
                ///--
                if (a < b)
                {
                    bias = 100 - denominator / (DenominatorsRing[i]->GetValue() / 100);
                    ptr_PoleToWorkWith = DenominatorsRing[i];						// Назначаем рабочий полюс
                }
                else
                {
                    bias = 100 - DenominatorsRing[i - 1]->GetValue() / (denominator / 100);
                    ptr_PoleToWorkWith = DenominatorsRing[i - 1];					// --
                }

                ///--
                ///--Если это смещение больше _Step процентов, тогда создаем новый полюс
                ///--
                if (bias > int_Step)
                {
                    Pole * ptr_NewPole = new Pole(denominator);

                    ///--
                    ///--Вставляем новый полюс между двумя перебираемыми полюсами
                    ///--
                    AddNewPoleToPolesRing(ptr_NewPole, false, i);

                    ptr_TargetPole = ptr_NewPole;	// связываем целевой полюс с новым

                }
                    ///--
                    ///--Если смещение меньше _Step процентов, тогда считаем рабочий полюс
                    ///--Пересчитываем значения и связи
                    ///--
                else
                {
                    Answer = ProcessPole(ptr_PoleToWorkWith, denominator);
                    ptr_TargetPole = ptr_PoleToWorkWith;
                }

                break;
            }

            else if (i > 0 && (i < DenominatorsRing.size() - 1) && denominator > DenominatorsRing[i]->GetValue() && denominator > DenominatorsRing[i - 1]->GetValue())
            {
                continue;
            }
                ///--
                ///--Если же перешли к конечному полюсу
                ///--и заводимое значение всё ещё больше текущего перебираемого полюса
                ///--и предыдущего перебранного полюса
                ///--то:
                ///--
            else if ((i == DenominatorsRing.size() - 1) && denominator > DenominatorsRing[i]->GetValue() && denominator > DenominatorsRing[i - 1]->GetValue())
            {
                ///--
                ///--Выясняем больше ли вводимое значение текущего перебираемого полюса
                ///--чем на _Step процентов
                ///--
                double bias = 0;
                bias = 100 - DenominatorsRing[i]->GetValue() / (denominator / 100);

                ///--
                ///--Если больше, то создаем новый полюс в кольце
                ///--
                if (bias > int_Step)
                {
                    Pole * ptr_NewPole = new Pole(denominator);
                    AddNewPoleToPolesRing(ptr_NewPole, true, i);

                    ptr_TargetPole = ptr_NewPole;
                }
                    ///--
                    ///--Если меньше, то работаем с текущим перебираемым полюсом
                    ///--
                else
                {
                    Answer = ProcessPole(DenominatorsRing[i], denominator);
                    ptr_TargetPole = DenominatorsRing[i];
                }

                break;
            }
                ///--
                ///--Отладочная ветвь
                ///--
            else
            {
                int check = 0;
            }
        }
    }

    /////////////
    //         //
    // 2  ЭТАП //
    //         //
    /////////////

    ///--
    ///--Если передано предыдущее значение (не равно нулю)
    ///--то найдем полюс, соотвествующий предыдущему значению
    ///--

    if(prev_denominator != 0)
    {
        for (int i = 0; i != DenominatorsRing.size(); ++i)
        {
            double d_max = max(prev_denominator, DenominatorsRing[i]->GetValue());	// максимальное значение
            double d_min = min(prev_denominator, DenominatorsRing[i]->GetValue());	// минимальное значение
            double bias = 100 - d_min / (d_max / 100);				// смещение в процентах между максимальным
            // и минимальным значением относительно максимального
            if(bias < int_Step)
            {
                ///--
                ///--Если смещение менее _Step процентов значит
                ///--полюс найден
                ///--
                ptr_SourcePole = DenominatorsRing[i];	// найденный полюс

                ///--
                ///--Далее перебираем связи в найденном полюсе
                ///--и если в связях мы обнаружили связь которая
                ///--указывает на текущее переданное значение
                ///--то укрепляем её
                ///--если нет - создаем новую связь
                ///--

                int _ConnectionsSize = (int)(DenominatorsRing[i]->Connections.size());	// количество связей
                bool IsBondFound = false;										// флаг для записи признака найдена ли связь

                ///--
                ///--Цикл перебора связей
                ///--
                for (int j = 0; j != _ConnectionsSize; ++j)
                {
                    ///--
                    ///--Если указатели соотвествуют
                    ///--то укрепляем связь
                    ///--
                    if (ptr_SourcePole->Connections[j]->GetTargetPole() == ptr_TargetPole)
                    {
                        IsBondFound = true;								// взводим флаг, так как связь найдена
                        ptr_SourcePole->Connections[j]->Strengthen(); 	// укрепляем связь
                    }
                }

                ///--
                ///--Если связь не найдена
                ///--Создадим новую
                ///--
                if (!IsBondFound)
                {
                    Bond * NewBond = new Bond(ptr_SourcePole, ptr_TargetPole, d_Easing_ratio);	// новая связь
                    ptr_SourcePole->Connections.push_back(NewBond);								// заводим связь

                    ///--
                    ///--После добавления сортируем связи в полюсе
                    ///--
                    ptr_SourcePole->SortSourceConnections();
                }
            }
        }
    }

    ///--
    ///--Ослабляем все связи
    ///--
    for (int i = 0; i != DenominatorsRing.size(); ++i)
    {
        DenominatorsRing[i]->EaseAllBonds();
    }

    return Answer;
}


///--
///--Возвращает прогноз по полюсу
///--
Forecast * Vortex::ProcessPole(Pole * _pole, double value)
{
    ///--
    ///--Создаем прогноз с нулевыми значениями
    ///--
    Forecast * answer = new Forecast();
    answer->value		= 0;
    answer->reliability	= 0;
    answer->distance	= 0;

    ///--
    ///--Если у полюса есть связи то выбираем первую
    ///--так как они отсортированы по убыванию
    ///--
    if (_pole->Connections.size() > 0)
    {
        answer->value		= _pole->Connections[0]->GetTargetPole()->GetValue();
        answer->reliability	= _pole->Connections[0]->GetReliability();
    }


    ///--
    ///--Если у полюса нет связей возвращаем прогноз с нулями
    ///--
    return answer;
}

void Vortex::AddNewPoleToPolesRing(Pole * ptr_NewPole, bool isPush, int index)
{
    ///--
    ///--Если мы превысили максимальный размер кольца
    ///--то удаляем самый старый полюс с, по возможности, наименьшим количеством связей
    ///--
    if ((int)PolesRing.size() >= int_MaxSizeOfRing)
    {
        ///--
        ///--Перебираем число связей по порядку
        ///--
        for (int i = 0; true; i++)
        {
            ///--
            ///--Перебираем упорядоченное кольцо
            ///--и сравниваем с предложенным числом связей
            ///--
            for (auto o_it = OrderedPolesRing.begin(); o_it != OrderedPolesRing.end(); o_it++)
            {
                ///--
                ///--И если такое количество связей нашлось
                ///--
                if ((*o_it)->Connections.size() == i)
                {
                    ///--
                    ///--То находим в основном кольце тот полюс который совпал
                    ///--
                    for (auto it = PolesRing.begin(); it != PolesRing.end(); ++it)
                    {
                        if (*it == (*o_it))
                        {
                            ///--
                            ///--и удаляем его
                            ///--
                            delete *it;
                            PolesRing.erase(it);
                            OrderedPolesRing.erase(o_it);
                            goto EndSearch;
                        }
                    }
                }
            }
        }
    }

    EndSearch:

    //--
    //--Проверяем ли полюс в конец кольца
    //--или вставлять между другими полюсами
    //--
    if (isPush)
    {
        PolesRing.push_back(ptr_NewPole);
    }
    else
    {
        PolesRing.insert(PolesRing.begin() + index, ptr_NewPole);
    }

    Pole * ptr_ToOrderedRing = ptr_NewPole;
    OrderedPolesRing.push_back(ptr_ToOrderedRing);
}


