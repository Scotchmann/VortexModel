
#include "Vortex.h"
#include "VortexModel.h"

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
Vortex::Vortex(int ArraySize, int Generation, double Step, int MaxSizeOfRing, double EasingRatio, double strengthen_step)
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
		_Agents[vecSize - 1][0].setDifferential ( 
													(_Agents[vecSize - 1][0].getValue()) / (_Agents[vecSize - 1 - 1][0].getValue()) 
												);

        InertialVector * fcst = new InertialVector();
		
		fcst =	PushToPolesRing (
                                    0,                                  // Уровень матрицы
									_Agents[vecSize - 1][0].getValue()	// Отношение текущего значения по уровню матрицы к предыдущему
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
            _Agents[vecSize - 1][0].setReceivedForecast(fcst->getValue());
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


    //return fvecsize;
    return (double)vecSize;

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

             (*ptr_array)[i - 1][j + 1].setValue(										// расчитываемый
													(*ptr_array)[i][j].getValue()		// текущий	
												  +
													(*ptr_array)[i - 1][j].getValue()	// предыдущий
												);

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
            //--                  _______предыдущий _______________рассчитываемый
            //--				 |						   |
            //-- вычитаемый______|_______текущий___________|
            //--

            (*ptr_array)[i - 1][j + 1].setValue(										// расчитываемый
													(*ptr_array)[i][j].getValue()		// текущий	
												 +
													(*ptr_array)[i - 1][j].getValue()	// предыдущий
												 -
													(*ptr_array)[i][j - 1].getValue()  	// вычитаемый
												);

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

                //--
                //--Если мы не дошли до равенства строки и уровня цикла
                //--то берем текущее и предыщущее значение по циклу и заводим их в кольцо
                //--
                if (i - 1 >= level )
                {

                    //--
                    //--Процентный переход
                    //--

                    //(*ptr_array)[i - 1][j + 1].setDifferential(   ((*ptr_array)[i - 1][j + 1].getValue()) / ((*ptr_array)[i - 1 - level][j + 1].getValue())  );

                    fcst =	PushToPolesRing (   
												level,								// Уровень
												(*ptr_array)[i][j].getValue(),		// Отношение текущего значения по уровню матрицы к предыдущему
                                                (*ptr_array)[i][j-1].getValue()		// предыдущее отношение по уровню матрицы
											);
                
					//--
					//--Если инерциальный прогноз сформирован и его значение не равно нулю
					//--то нормализуем его под текущий уровень в матрице и вкладываем в куммулятивыный
					//--вектор 
					//--
                    if(fcst != nullptr && fcst->getValue() > 0)
                    {

                        fcst->setDistance(level);			// Устанавливаем уровень в матрице
						
                        _cumuVec->push_back(fcst);			// Заводим в куммулятивный вектор прогноза
                       
						// (*ptr_array)[i - 1][j + 1].setReceivedForecast(fcst->getValue() );
                    }
                }
                    
				//--
				//--Если значение уровня больше номера строки то заводим в кольцо только текущее значение
				//--
                else
                {
					
                    fcst = PushToPolesRing  (	
												level, 										// Уровень
												(*ptr_array)[i][j].getValue()				// Текущее значение по уровню
											);

					//--
					//--Если инерциальный прогноз сформирован и его значение не равно нулю
					//--то нормализуем его под текущий уровень в матрице и вкладываем в куммулятивный
					//--вектор 
					//--
                    if (fcst != nullptr && fcst->getValue() > 0)
                    {

                        fcst->setDistance(level);			// Устанавливаем уровень в матрице
						
                        _cumuVec->push_back(fcst);			// Заводим в куммулятивный вектор прогноза
						
                       // (*ptr_array)[i - 1][j + 1].setReceivedForecast(fcst->getValue());
						
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
InertialVector * Vortex::PushToPolesRing( int 		level,		// уровень матрицы
                                          double 	value,		// заводимое в кольцо значение
                                          double 	prev_value	// предыщущее значение в цикле для которого подходящий полюс уже есть
                                        )
{

    //--
    //--Переменная для хранения имеющегося prev_value полюса
    //--
    Pole * ptr_SourcePole	= nullptr;


    //--
    //--Переменная для хранения добавленного полюса (или имеющегося) полюса
    //--для последующей привязки в connections для имеющегося prev_value полюса
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
    

    //--
    //--Если кольцо пустое, то добавим сразу полюс в кольцо
    //--с текущим значением
    //--
    if (PolesRingsStack[level].size() == 0)
    {
        Pole * ptr_NewPole = new Pole(value);				// новый полюс
        AddNewPoleToPolesRing(level, ptr_NewPole, true);	// заводим новый полюс колцо полюсов	
        ptr_TargetPole = ptr_NewPole;						// связываем целевой полюс с новым
    }
    //--
    //--Если в кольце есть одно значение
    //--то сравниваем это значение со входящим
    //--
    else if (PolesRingsStack[level].size() == 1)
    {
        //--
        //--Выясняем больше ли вводимое значение текущего перебираемого полюса
        //--чем на _Step процентов
        //--
        double bias = 0;

        if (value > PolesRingsStack[level][0]->getValue())
        {
            bias = 100 - PolesRingsStack[level][0]->getValue() / (value / 100);
        }
        else
        {
            bias = 100 - value / (PolesRingsStack[level][0]->getValue() / 100);
        }

        //--
        //--Если больше, то создаем новый полюс в кольце
        //--
        if (bias > int_Step)
        {
            Pole * ptr_NewPole = new Pole(value);

            //--
            //--Если заводимое значение больше нулевого полюса
            //--то:
            //--
            if (value > PolesRingsStack[level][0]->getValue())
            {  
                AddNewPoleToPolesRing(level, ptr_NewPole, true);	//добавляем в конец
            }
			//--
			//--В другом случае
			//--
            else
            {
                //--
                //--добавляем в начало
                //--тем самым сохраняя упорядоченность кольца по возрастанию
                //--
                AddNewPoleToPolesRing(level, ptr_NewPole, false, 0);
            }

            ptr_TargetPole = ptr_NewPole;	// связываем целевой полюс с новым
        }
        else
        {
            ptr_TargetPole = PolesRingsStack[level][0];	// связываем целевой полюс с новым
        }

    }
    //--
    //--Определяем нужно ли добавить новый полюс или работать с уже существующим
    //--Полюса вероятностей создаются с шагом в _Step процентов
    //--
    else if (PolesRingsStack[level].size() > 1)
    {

        for (int i = 0; i != PolesRingsStack[level].size(); ++i)	// Цикл перебора кольца
        {
			
            if (value == PolesRingsStack[level][i]->getValue())
            {
                Answer 			= ProcessPole(PolesRingsStack[level][i], value, level);		// формируем ответ
                ptr_TargetPole 	= PolesRingsStack[level][i];								// связываем целевой полюс с новым
                break;
            }

            else if (i == 0 && value > PolesRingsStack[level][i]->getValue())
            {
                continue;
            }
            //--
            //--Если мы находимся в начале перебора кольца и
            //--значение уже меньше текущего и предыдущего полюсов
            //--то выясняем нужно ли добавлять в начало новый полюс
            //--или работать с первым
            //--
            else if ((i == 0 && value < PolesRingsStack[level][i]->getValue()) || (i == 1 && value < PolesRingsStack[level][i]->getValue() && value < PolesRingsStack[level][i - 1]->getValue()))
            {

                //--
                //--Выясняем больше ли вводимое значение текущего перебираемого полюса
                //--чем на _Step процентов
                //--
                double bias = 0;
                bias 		= 100 - value / (PolesRingsStack[level][0]->getValue() / 100);

                //--
                //--Если больше, то создаем новый полюс в кольце
                //--
                if (bias > int_Step)
                {
                    Pole * ptr_NewPole 	= new Pole(value);					// Создаем новый полюс                    
					AddNewPoleToPolesRing(level, ptr_NewPole, false, 0);	// Заводим новый полюс в кольцо полюсов
					ptr_TargetPole 		= ptr_NewPole;						// связываем целевой полюс с новым
                }    
				//--
				//--В противном случае работаем с имеющимся полюсом
				//--
                else
                {
                    Answer 			= ProcessPole(PolesRingsStack[level][0], value, level);	// формируем ответ
                    ptr_TargetPole 	= PolesRingsStack[level][0];							// связываем целевой полюс с новым
                }
                
                break;
            }
            //--
            //--Если заводимое значение меньше текущего перебираемого полюса и больше предыдущего
            //--перебранного полюса, то пытаемся втиснуть заводимое значение между ними.
            //--
            else if (i > 0 && value < PolesRingsStack[level][i]->getValue() && value > PolesRingsStack[level][i - 1]->getValue())
            {
                //--
                //--Для этого:
                //--	из текущего перебираемого полюса вычитаем заводимое значение
                //--	из заводимого значения вычитаем предыдущий перебранный полюс
                //--
                double a 					= PolesRingsStack[level][i]->getValue() - value;		// разность между текущим перебираемым полюсом и заводимым значением
                double b 					= value - PolesRingsStack[level][i - 1]->getValue();	// разность между заводимым значением и предыдущим перебранным
                double bias 				= 0;								    				// переменная для хранения смещения в процентах
                Pole * ptr_PoleToWorkWith 	= nullptr;			    								// переменная для записи рабочего полюса

                //--
                //--Затем вычисляем смещение в процентах относительно наименьшей разности
                //--Для этого оцениваем какая из разностей меньше
                //--Если разница текущего полюса меньше, берем за его 100 процентов
                //--Если меньше разница предыдущего полюса, берем вводимое значение за 100 процентов
                //--Затем вычисляем смещение в процентах между полюсом и вводимым значением
                //--
                if (a < b)
                {
                    bias 				= 100 - value / (PolesRingsStack[level][i]->getValue() / 100);		// Вычисляем смещение в процентах
                    ptr_PoleToWorkWith 	= PolesRingsStack[level][i];										// Назначаем рабочий полюс
                }
                else
                {
                    bias 				= 100 - PolesRingsStack[level][i - 1]->getValue() / (value / 100);	// --
                    ptr_PoleToWorkWith 	= PolesRingsStack[level][i - 1];									// --
                }

                //--
                //--Если это смещение больше _Step процентов, тогда создаем новый полюс
                //--
                if (bias > int_Step)
                {
                    Pole * ptr_NewPole	= new Pole(value);					// создаем новый полюс
                    AddNewPoleToPolesRing(level, ptr_NewPole, false, i);	// Вставляем новый полюс между двумя перебираемыми полюсами
					ptr_TargetPole 		= ptr_NewPole;						// связываем целевой полюс с новым
                }
                //--
                //--Если смещение меньше _Step процентов, тогда считаем рабочий полюс
                //--Пересчитываем значения и связи
                //--
                else
                {
                    Answer			= ProcessPole(ptr_PoleToWorkWith, value, level);	// формируем ответ
                    ptr_TargetPole 	= ptr_PoleToWorkWith;								// Назначаем целевой полюс
                }

                break;
            }

            else if (i > 0 && (i < PolesRingsStack[level].size() - 1) && value > PolesRingsStack[level][i]->getValue() && value > PolesRingsStack[level][i - 1]->getValue())
            {
                continue;
            }
            //--
            //--Если же перешли к конечному полюсу
            //--и заводимое значение всё ещё больше текущего перебираемого полюса
            //--и предыдущего перебранного полюса
            //--то:
            //--
            else if ((i == PolesRingsStack[level].size() - 1) && value > PolesRingsStack[level][i]->getValue() && value > PolesRingsStack[level][i - 1]->getValue())
            {
                //--
                //--Выясняем больше ли вводимое значение текущего перебираемого полюса
                //--чем на _Step процентов
                //--
                double bias = 0;															// Переменная для хранения смещения
                bias 		= 100 - PolesRingsStack[level][i]->getValue() / (value / 100);	// Вычисляем смещение в процентах

                //--
                //--Если больше, то создаем новый полюс в кольце
                //--
                if (bias > int_Step)
                {
                    Pole * ptr_NewPole = new Pole(value);						// Создаем новый полюс
					AddNewPoleToPolesRing(level, ptr_NewPole, true, i);			// Заводим полюс в кольцо полюсов
                    ptr_TargetPole = ptr_NewPole;								// Назначаем новый полюс в качестве целевого
                }
                //--
                //--Если меньше, то работаем с текущим перебираемым полюсом
                //--
                else
                {
                    Answer = ProcessPole(PolesRingsStack[level][i], value, level);	// формируем ответ
                    ptr_TargetPole = PolesRingsStack[level][i];						// Назначаем целевой полюс
                }

                break;
            }
            //--
            //--Отладочная ветвь
            //--
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

    //--
    //--Если передано предыдущее значение (не равно нулю)
    //--то найдем полюс, соотвествующий предыдущему значению
    //--
    if(prev_value != 0 && level > 0 && level < int_ArraySize)
    {
        for (int i = 0; i != PolesRingsStack[level-1].size(); ++i)
        {
            double d_max 	= max(prev_value, PolesRingsStack[level-1][i]->getValue());	// максимальное значение
            double d_min 	= min(prev_value, PolesRingsStack[level-1][i]->getValue());	// минимальное значение
            double bias 	= 100 - d_min / (d_max / 100);				                // смещение в процентах между максимальным
																			            // и минимальным значением относительно максимального

            //--
            //--
            //--
            if(bias < int_Step)
            {
                //--
                //--Если смещение менее _Step процентов значит
                //--полюс найден
                //--
                ptr_SourcePole = PolesRingsStack[level-1][i];	// найденный полюс

                //--
                //--Далее перебираем связи в найденном полюсе
                //--и если в связях мы обнаружили связь которая
                //--указывает на текущее переданное значение
                //--то укрепляем её
                //--если нет - создаем новую связь
                //--
                int _ConnectionsSize 	= (int)(PolesRingsStack[level-1][i]->Connections.size());	// количество связей
                bool IsBondFound 		= false;									                // флаг для записи признака найдена ли связь

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
                        IsBondFound = true;								// взводим флаг, так как связь найдена
                        ptr_SourcePole->Connections[j]->Strengthen(); 	// укрепляем связь
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
                }
            }




        }

        //--
        //--Ослабляем все связи
        //--
        for (int i = 0; i != PolesRingsStack[level-1].size(); ++i)
        {
            PolesRingsStack[level-1][i]->easeAllBonds();
        }
    }



    return Answer;
}

//--
//--Возвращает вектор инерции по полюсу
//--
InertialVector * Vortex::ProcessPole(Pole *_pole, double value, int level)
{


    //--
    //--Создаем вектор инерции с нулевыми значениями
    //--
    InertialVector * answer = new InertialVector();
    answer->setValue(0);
    answer->setReliability(0);
    answer->setDistance(0);

    _pole->sortSourceConnections();

    //--
    //--Если у полюса есть связи то выбираем первую
    //--так как они отсортированы по убыванию
    //--
    if (_pole->Connections.size() > 0)
    {
        answer->setValue(_pole->Connections[0]->getTargetPole()->getValue()  -  _pole->getValue());	// Устанавливаем значение ответа
		
		double cumulativeTotal 		= _pole->getCumulativeReliability();		// Получаем куммулятивную надежность полюса
		double strongestReliability = _pole->Connections[0]->getReliability();	// Получаем максимальную надежность из связей в полюсе

        //--
        //--Проверяем куммулятивную надежность на ноль, во избежание ошибки деления
        //--
		if(cumulativeTotal > 0)
		{
			double _reliability = strongestReliability/cumulativeTotal*100;		//	
			answer->setReliability(_reliability);								//
		}  
    }

    //--
    //--Если у полюса нет связей возвращаем вектор инерции с нулями
    //--
    return answer;
}

void Vortex::AddNewPoleToPolesRing(int level, Pole * ptr_NewPole, bool isToPush, int index)
{

    while (OrderedPolesRing.size() < level + 1)
    {
        OrderedPolesRing.push_back(vector<Pole*>());
    }

    //--
    //--Сортируем референсное кольцо по куммулятивной силе
    //--
    sort(OrderedPolesRing[level].begin(), OrderedPolesRing[level].end(), PoleComparatorObject);


    if ((int)PolesRingsStack[level].size() >= int_MaxSizeOfRing)
    {
        if(OrderedPolesRing[level].size() > 0)
        {
            Pole * poleToDelete = OrderedPolesRing[level][0];

            for (auto it = PolesRingsStack[level].begin(); it != PolesRingsStack[level].end(); ++it)
            {
                if (*it == poleToDelete)
                {
                    ///--
                    ///--и удаляем его
                    ///--
                    delete *it;
                    PolesRingsStack[level].erase(it);
                    OrderedPolesRing[level].erase(OrderedPolesRing[level].begin());
                    goto EndSearch;
                }
            }
        }
    }

    EndSearch:

    //--
    //--Проверяем вставлять ли полюс в конец кольца
    //--или вставлять между другими полюсами
    //--
    if (isToPush)
    {
        PolesRingsStack[level].push_back(ptr_NewPole);
    }
    else
    {
        PolesRingsStack[level].insert(PolesRingsStack[level].begin() + index, ptr_NewPole);
    }

    Pole * ptr_ToOrderedRing = ptr_NewPole;



    OrderedPolesRing[level].push_back(ptr_ToOrderedRing);
}


