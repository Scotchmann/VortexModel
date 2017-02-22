
#include "Vortex.h"

using namespace std;

Vortex::Vortex()
{
    int_ArraySize = 0;
}

//--
//--Конструктор класса
//--	ArraySize 	- Глубина треугольной матрицы
//--	Generation 	- Поколение
//--	Step		- Шаг расстановки полюсов в кольце, по умолчанию - 2%
//--
Vortex::Vortex(int ArraySize, double Step, int MaxSizeOfRing, double EasingRatio, double strengthen_step)
{
    //--
    //--Заполняем внутренние переменные
    //--
    int_ArraySize 		= ArraySize;
    int_Step			= Step;
    int_MaxSizeOfRing	= MaxSizeOfRing;
    d_Easing_ratio		= EasingRatio;
    d_strengthen_step   = strengthen_step;
}

//--
//--Деструктор класса
//--
Vortex::~Vortex()
{

}

//--
//--Заведение агента в вихрь
//--	d_value 	-	следующее значение
//--
double Vortex::pushAgent(double value, CumulativeVector * _cumuVec)
{
    //--
    //--Проверяем очередь на полноту
    //--И если очередь полна, то удаляем первый элемент в очереди
    //--
    if (_Agents.size() == int_ArraySize + 1)
    {
        _Agents.begin()->clear();
        _Agents.erase(_Agents.begin());
    }

    //--
    //--Добавляем горизонтальную струну
    //--
    _Agents.push_back(vector<Agent>((unsigned long)int_ArraySize));


    //--
    //--Если необходимо добавим новое кольцо в стопку
    //--
    if(PolesRingsStack.size() == 0)
    {
        PolesRingsStack.push_back(vector<Pole*>());
    }


    //--
    //--Определяем текущий размер массива
    //--
    int vecSize = (int)_Agents.size();

    
	//--
    //--Присваем значение агенту в струне
    //--
    _Agents[vecSize - 1][0].setValue(value);


    if (vecSize > 1)
    {
		//--
		//--Инерциальный вектор
		//--
        InertialVector * fcst = new InertialVector();

		fcst =	PushToPolesRing (
                                    0,                          // уровень матрицы
                                    &_Agents[vecSize - 1][0]    // отношение текущего значения по уровню матрицы к предыдущему
                                );
								
		//--
		//--Если инерциальный прогноз сформирован и его значение не равно нулю
		//--то нормализуем его под текущий уровень в матрице и вкладываем в куммулятивыный
		//--вектор 
		//--
        if(fcst != nullptr && fcst->getValue() > 0)
        {
            fcst->setValue(fcst->getValue());
            fcst->setDistance(1);
            _cumuVec->push_back(fcst);
        }
	
		//--
        //--Рекурсивно пересчитываем струны в треугольной матрице
        //--
        RecalculationOfMainPool(vecSize - 1, 0, &_Agents, 1, _cumuVec);
	}

    //--
    //--Возращаем размер массива
    //--
    double fvecsize = 0;
    fvecsize = (double)_cumuVec->size();

    return (double)fvecsize;
}

double Vortex::getAgent(int i, int j)
{
    return (double)PolesRingsStack.size();
}

double Vortex::getBuf()
{
    return 0;
}

//--
//--Получение дистанции инерции
//--
int Vortex::getDistance()
{
    return 0;
}


//--
//--Рекурсивно пересчитывает вихрь
//--	i 			- координата строки в треугольной матрице
//--	j 			- координата столбца в треугольной матрице
//--	ptr_array 	- указатель на треугольную матрицу
//--	level		- глубина цикла
//--
void Vortex::RecalculationOfMainPool(int i, int j, AgentsArray * ptr_array, int level, CumulativeVector * _cumuVec)
{
	//--
	//--Если необходимо добавим новое кольцо в стопку
	//--
    while (PolesRingsStack.size() < level + 1)
    {
        PolesRingsStack.push_back(vector<Pole*>());
    }

    InertialVector * fcst = new InertialVector();

    //--
    //--Выстраиваем треугольную суммирующую матрицу
    //--

    /*

                                                               22

                                                    21       (0.2)        17

                                        19       (0.400)       16      (0.250)        13

                             12       (1.400)       14      (0.500)       12       (0.333)      10

                   9       (0.600)       7       (1.750)       10      (0.666)         9      (0.142)       3

        5       (0.800)       4       (0.750)        3      (2.333)        7       (0.285)       2       (0.500)       1


    */

    //--
    //--В начале пересчета столбец является нулевым, поэтому
    //--расчитываем по схеме без вычитаемого узла
    //--
    if (j == 0)
    {
        //--
        //--Если мы еще не дошли до нулевой строки
        //--тогда расчитываем узлы по схеме:
        //--
        if (i > 0)
        {
            //--
            //-- предыдущий________________рассчитываемый
            //--                  |
            //-- текущий__________|
            //--

             (*ptr_array)[i - 1][j + 1].setValue(										// <- расчитываемый
													(*ptr_array)[i][j].getValue()		// <- текущий	
												  +
													(*ptr_array)[i - 1][j].getValue()	// <- предыдущий
												);

            DifferentialSet Diffset;

            Diffset.b   =   (*ptr_array)[i - 1][j].getValue();
            Diffset.c   =   (*ptr_array)[i][j].getValue();
												
            (*ptr_array)[i - 1][j + 1].setDifferential(Diffset);
        }
    }

    //--
    //--Если текущий столбец не нулевой и меньше конечного индекса столбца в струне
    //--тогда:
    //--
    else if (j > 0 && j < int_ArraySize - 1)
    {
        //--
        //--Если мы еще не дошли до нулевой строки
        //--тогда расчитываем узлы по схеме:
        //--
        if (i > 0)
        {    
			//--
            //--                     _______предыдущий _______________рассчитываемый
            //--                    |                       |
            //-- вычитаемый_________|_______текущий_________|
            //--

            (*ptr_array)[i - 1][j + 1].setValue(										// <- расчитываемый
													(*ptr_array)[i][j].getValue()		// <- текущий	
												 +
													(*ptr_array)[i - 1][j].getValue()	// <- предыдущий
												 -
													(*ptr_array)[i][j - 1].getValue()  	// <- вычитаемый
                                               );
			
            DifferentialSet Diffset;

            Diffset.b   =   (*ptr_array)[i - 1][j].getValue();
            Diffset.c   =   (*ptr_array)[i][j].getValue();

            (*ptr_array)[i - 1][j + 1].setDifferential(Diffset);

            //--
            //--Заводим значение в кольцо полюсов (PolesRing)
            //--
            if (level >= 0)
            {
                //--
                //--При заведении значения в колцо полюсов определяем, возможно ли
                //--взять предыдущее значение
                //--
                /*

                      |      |      |      |
                      |  L1  |  L2  |  L3  |
                ______|______|______|______|
                      |      |      |      |
                  i1  |      |      |      |
                ______|______|______|______|
                      |      |      |      |
                  i2  |      |      |      |
                ______|______|______|______|
                      |      |      |      |
                  i3  |      |      |      |
                ______|______|______|______|


                */

                //--
                //--Если мы не дошли до равенства строки и уровня цикла
                //--то берем текущее и предыщущее значение по циклу и заводим их в кольцо
                //--
                if (i - 1 >= level )
                {
                    ((Agent*)(&(*ptr_array)[i][j]))->B_Agent = &(*ptr_array)[i][j-1];

                    fcst =	PushToPolesRing (   
												level,						// уровень
                                                &(*ptr_array)[i][j],		// текущий агент матрицы
                                                &(*ptr_array)[i-1][j]	    // предыдущий агент матрицы
											);
                
					//--
					//--Если инерциальный прогноз сформирован и его значение не равно нулю
					//--то нормализуем его под текущий уровень в матрице и вкладываем в куммулятивыный
					//--вектор 
					//--
                    if(fcst != nullptr && fcst->getValue() > 0)
                    {
                        fcst->setDistance(level);			// устанавливаем уровень в матрице
                        _cumuVec->push_back(fcst);			// заводим в куммулятивный вектор прогноза
                    }
                }
                    
				//--
				//--Если значение уровня больше номера строки то заводим в кольцо только текущее значение
				//--
                else
                {

                    ((Agent*)(&(*ptr_array)[i][j]))->B_Agent = &(*ptr_array)[i][j-1];

                    fcst = PushToPolesRing  (	
												level, 					// уровень
                                                &(*ptr_array)[i][j]		// текущее значение по уровню
											);

					//--
					//--Если инерциальный прогноз сформирован и его значение не равно нулю
					//--то нормализуем его под текущий уровень в матрице и вкладываем в куммулятивный
					//--вектор 
					//--
                    if (fcst != nullptr && fcst->getValue() > 0)
                    {
                        fcst->setDistance(level);			// устанавливаем уровень в матрице		
                        _cumuVec->push_back(fcst);			// заводим в куммулятивный вектор прогноза		
                    }
                }
            }
        }
    }

    //--
    //--Если мы не дошли до нулевой строки и не превзошли
    //--максимальный индекс для столбцов в строке, то
    //--продолжаем рекурсию по схеме:
    //--        |             |             |
    //--        |      j      |     j+1     |
    //-- _______|_____________|_____________|
    //--        |
    //--   i-1  |              _> текущий'
    //-- _______|             |
    //--        |             |
    //--    i   |  текущий >__|
    //-- _______|
    //--
    if (i > 0 && j < int_ArraySize - 1)
    {
        RecalculationOfMainPool(i - 1, j + 1, ptr_array, level + 1, _cumuVec);
    }
    else
    {
        return; // вектор инерции
    }
}

//--
//--Заводит значение треугольной матрицы в кольцо
//--	d_value	- текущее заводимое значение
//--
InertialVector * Vortex::PushToPolesRing( 
                                            int 	level,          // уровень матрицы
                                            Agent *	CurrentAgent,	// заводимое в кольцо значение
                                            Agent * prev_Agent      // предыщущее значение в цикле для которого подходящий полюс уже есть
                                        )
{
	double value = CurrentAgent->getValue();

    //--
    //--Переменная для хранения имеющегося prev_Agent полюса
    //--
    Pole * ptr_SourcePole	= nullptr;

    //--
    //--Переменная для хранения добавленного полюса (или имеющегося) полюса
    //--для последующей привязки в connections для имеющегося prev_Agent полюса
    //--
    Pole * ptr_TargetPole	= nullptr;

    InertialVector * Answer	= nullptr;


    /////////////
    //         //
    // 1  ЭТАП //
    //         //
    /////////////

    //--
    //--Перебираем кольцо полюсов
    /* 
                                                            1
                                                  28        *        2
                                               27   *               *   3
                                            26   *                     *   4
                                               *    \       |       /    *
                                          25 *                             * 5
                                         24 *                               * 6
                                        23 *               \ /               * 7
                                        22 *    -   -     - + -     -   -    * 8
                                        21 *               / \               * 9
                                         20 *                               * 10
                                          19 *                             * 11
                                            18 *    /       |       \    * 12
                                               17*                     *13
                                                 16 *               * 14
                                                            *
                                                            15
    */
    
    bool PoleIsFound = false;
 
	for(auto it = PolesRingsStack[level].begin(); it != PolesRingsStack[level].end(); ++it)
	{
        if((*it)->getValue() != value) continue;

		if( (*it)->getValue() == value && (*it)->get_c() == (CurrentAgent->getDifferential()).c && (*it)->get_b() == (CurrentAgent->getDifferential()).b)
		{
			ptr_TargetPole = (*it);
            PoleIsFound = true;
			break;
		}
	}
	
    if(!PoleIsFound)
    {
        if(level > 1)
        {
			Pole * ptr_NewPole = new Pole(value, CurrentAgent->getDifferential());
			PolesRingsStack[level].push_back(ptr_NewPole);
			ptr_TargetPole = ptr_NewPole;
        }
    }

    if(level >1)
	{
        Answer = ProcessPole(ptr_TargetPole, value, level, CurrentAgent);
	}
		
	CurrentAgent->CorrespondingPole = ptr_TargetPole;

    /////////////
    //         //
    // 2  ЭТАП //		ОБРАБОТКА ПРЕДЫДУЩЕГО ЗНАЧЕНИЯ
    //         //
    /////////////

    //--
    //--Если передано предыдущее значение (не равно нулю)
    //--то найдем полюс, соотвествующий предыдущему значению
    //--
    if(prev_Agent != nullptr && prev_Agent->CorrespondingPole != nullptr && level > 0 && level < int_ArraySize)
    {	
		ptr_SourcePole  = prev_Agent->CorrespondingPole;	// найденный полюс
		
		//--
		//--Далее перебираем связи в найденном полюсе
		//--и если в связях мы обнаружили связь которая
		//--указывает на текущее переданное значение
		//--то укрепляем её
		//--если нет - создаем новую связь
		//--
		int  _ConnectionsSize 	= (int)(ptr_SourcePole->Connections.size());   // количество связей
		bool IsBondFound 		= false;									   // флаг для записи признака найдена ли связь

		//--
		//--Цикл перебора связей
		//--
		for (int j = 0; _ConnectionsSize > 0 && j < _ConnectionsSize; ++j)
		{
			//--
			//--Если указатели соотвествуют
			//--то укрепляем связь
			//--
			if (ptr_SourcePole->Connections[j]->getTargetPole() == ptr_TargetPole)
			{
				ptr_SourcePole->BondsQueue.push(ptr_SourcePole->Connections[j]);				//
				ptr_SourcePole->TotalRepeatsCounter = ptr_SourcePole->TotalRepeatsCounter + 1;	//
				IsBondFound = true;															    // взводим флаг, так как связь найдена
				ptr_SourcePole->Connections[j]->Strengthen(); 									// укрепляем связь
                break;
			}
		}

		//--
		//--Если связь не найдена
		//--Создадим новую
		//--
		if (!IsBondFound)
		{
			Bond * NewBond = new Bond(ptr_SourcePole, ptr_TargetPole, d_Easing_ratio, d_strengthen_step);	// новая связь
			ptr_SourcePole->Connections.push_back(NewBond);													// заводим связь
			ptr_SourcePole->BondsQueue.push(NewBond);
			ptr_SourcePole->TotalRepeatsCounter = ptr_SourcePole->TotalRepeatsCounter + 1;
			ptr_SourcePole->TotalConnectionCounter = ptr_SourcePole->TotalConnectionCounter + 1;
		}
			
		//--
		//--Если превышен максимальный размер очереди подсчета удаляем первый элемент очереди
		//--
        if(ptr_SourcePole->BondsQueue.size() > 100) // ptr_SourcePole->TotalConnectionCounter)
		{
			((Bond*)(ptr_SourcePole->BondsQueue.front()))->Ease();
			ptr_SourcePole->BondsQueue.pop();
			ptr_SourcePole->TotalRepeatsCounter = ptr_SourcePole->TotalRepeatsCounter - 1;
		}	
    }

    return Answer;
}

//--
//--Возвращает вектор инерции по полюсу
//--
InertialVector * Vortex::ProcessPole(Pole *_pole, double value, int level, Agent* CurrentAgent)
{
    //--
    //--Создаем вектор инерции с нулевыми значениями
    //--
    InertialVector * answer = new InertialVector();
		
		_pole->sortSourceConnections();

		//--
		//--Если у полюса есть связи то выбираем первую
		//--так как они отсортированы по убыванию
		//--
		if (_pole->Connections.size() > 0)
		{
			//ВАААЖЖЖНООО!!!!! {{{{
			answer->setValue(_pole->Connections[0]->getTargetPole()->get_c_forecast());	// устанавливаем значение ответа (Для циклических схем НУЖНО get_b_forecast() !!!!! )
			//}}}}
			
            double cumulativeTotal 		= (double)_pole->TotalRepeatsCounter;           // получаем куммулятивную надежность полюса
            double strongestReliability = _pole->Connections[0]->getReliability();		// получаем максимальную надежность из связей в полюсе
            answer->setVariability(_pole->TotalConnectionCounter);

			//--
			//--Проверяем куммулятивную надежность на ноль, во избежание ошибки деления
			//--
			if(cumulativeTotal > 0)
			{
                double _reliability = strongestReliability / 100 ; // cumulativeTotal*100;       //
				answer->setReliability(_reliability);									//
			}  
		}	

    //--
    //--Если у полюса нет связей возвращаем вектор инерции с нулями
    //--
    return answer;
}



