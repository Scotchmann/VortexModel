// ConsoleApplication1.cpp : Defines the entry point for the console application.
// DiagonalSearch branch

#include "VortexModel.h"
#include <cstring>

using namespace std;

int ProcessPoints()
{
    double value_to_push = 0;	// для хранения входного значения

    string s;                                                       		// сюда будем ложить считанные строки
    ifstream file("/home/vortex/ClionProjects/ProcessData_84460.txt");    	// файл из которого читаем

    ///--
    ///--Инициализируем вихрь
    ///--
    InitializeVortex(
                       0, 		//
                       0.0005, 		// Шаг в процентах между полюсами
                       500000, 		// Максимальный размер кольца
                       0.00001, 	// Коэффициент ослабления
                       1.0		// Шаг укрепления связи
    );


    int i;					// отладочный счетчик
    i = 1;

    double Prevval = 1;
	
	///--
	///--Цикл перебора строк файла
	///--
    while (getline(file, s))
    {
        if (i == 9998)
        {
            int b = 0;
            //break;
        }

        value_to_push = atof(s.c_str());			// нормализуем входное значение для дальнейшей обработки

        if(Prevval > 0)
        {
            pushAgent(value_to_push/Prevval*10000, true);				// заводим значение в модель
            cout << value_to_push/Prevval*10000 << "\t\t\t " << i << endl; 	// выводим на экран
        }
        else
        {
            pushAgent(value_to_push, true);				// заводим значение в модель
            cout << value_to_push << "\t " << i << endl; 	// выводим на экран
        }


        //cout << value_to_push << " " << i << endl; 	// выводим на экран

        Prevval = value_to_push;

        i++;
    }

    file.close(); // закрываем файл

    return 0;
}

int ProcessChars()
{
	std::vector<string> BooksToRead;

	BooksToRead.push_back("/home/vortex/ClionProjects/Leo");
	BooksToRead.push_back("/home/vortex/ClionProjects/Deas_thief_takers_apprentice_2_Warlocks_shadow_RuLit_Net.txt");

    //--
    //--Инициализируем вихрь
    //--
    InitializeVortex(
                        1200,       // размерность матрицы
                        0.025, 		// шаг в процентах между полюсами
                        1000,       // максимальный размер кольца
                        0.0001,     // коэффициент ослабления
                        1           // шаг укрепления связи
					);

    int 	i_counter 		= 1;	// отладочный счетчик
    int 	nextchar  		= 0;	// прогноз на следующий знак
    int 	total_counter 	= 0;	// общий подсчет совпадений
	double 	reliability 	= 0;	// надежность
    int     distance        = 0;    // дистанция
	
	double 	value_to_push 	= 0;	// для хранения входного значения
    string 	s;     					// сюда будем ложить считанную строку
	ForecastedValue FCV_G; 			// Полученный прогноз
	
    for(int book_number = 0; book_number < BooksToRead.size(); book_number++)
	{
		ifstream file(BooksToRead[book_number]);   // файл из которого читаем
		
		//--
		//--Цикл перебора строк файла
		//--
		while (getline(file, s))
		{
			//--
			//--Отладочная проверка
			//--
			if (i_counter == 9998)				
			{										
				int b = 0;						 
				//break;
			}

			const char * cstr = s.c_str();					// получаем строку в стиле C 

			//--
			//--Цикл перебора строки
			//--
			for (unsigned int i = 0; i < strlen(cstr); i++) 
			{
				value_to_push = (double)(cstr[i]);			// нормализуем входное значение для дальнейшей обработки
						
				if( ((int)(cstr[i])) == nextchar)
				{
					total_counter++;
				}
				
				//--
				//--Выводим на экран
				//--
                cout << cstr[i] << "\t " << ((int)cstr[i]) 			// номер символа
								<< "\t " << nextchar 				// символ
								<< "\t " << reliability << "% " 	// надежность в процентах
								<< "\t " << distance 				// дистанция
								<< "\t " << (int)i_counter 			// счетчик всего перебранных символов
								<< "\t " << total_counter << endl;	// счетчик совпадений
				
				FCV_G = pushAgent(value_to_push, true);	// заводим значение в модель
				nextchar 	=	(int)FCV_G.value; 		// значение
                reliability =	FCV_G.reliability;		// надежность
                distance    =   (int)FCV_G.distance;    // дистанция
					
				i_counter++;
			}
		}

		file.close(); // закрываем файл
	}

    return 0;
}

int main()
{
    //ProcessPoints();
    ProcessChars();

    system("pause");
    return 0;	
}
