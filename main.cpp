// ConsoleApplication1.cpp : Defines the entry point for the console application.
// DiagonalSearch branch

#include "VortexModel.h"

#include <iostream>
#include <fstream>
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
                       0, 		// Поколение
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

    double value_to_push = 0;	// для хранения входного значения

    string s;                                                       											// сюда будем ложить считанную строку

    ifstream file("/home/vortex/ClionProjects/Leo");   // файл из которого читаем

    ///--
    ///--Инициализируем вихрь
    ///--
    InitializeVortex(
                       300,     //
                         0, 	// Поколение
                       0.25, 	// Шаг в процентах между полюсами
                      1000,     // Максимальный размер кольца
                    0.0001, 	// Коэффициент ослабления
                       1.0		// Шаг укрепления связи
    );

    int i_counter = 1;		// отладочный счетчик

	///--
	///--Цикл перебора строк файла
	///--
    while (getline(file, s))
    {

		///--
		///--Отладочная проверка
		///--
        if (i_counter == 9998)				
        {										
            int b = 0;						 
            //break;
        }

        const char * cstr = s.c_str();									// получаем строку в стиле C 

		///--
		///--Цикл перебора строки
		///--
        for (unsigned int i = 0; i < strlen(cstr); i++) 
		{
            value_to_push = (double)((int)(cstr[i]));					// нормализуем входное значение для дальнейшей обработки
            pushAgent(value_to_push, true);								// заводим значение в модель
            cout << cstr[i] << "\t " <<  ((int)cstr[i]) << "\t " << (int)i_counter << endl; 	// выводим на экран
            i_counter++;
        }

    }

    file.close(); // закрываем файл


    ifstream file1("/home/vortex/ClionProjects/Deas_thief_takers_apprentice_2_Warlocks_shadow_RuLit_Net.txt");   // файл из которого читаем
    //ifstream file1("/home/vortex/ClionProjects/Leo");   // файл из которого читаем

    ///--
    ///--Цикл перебора строк файла
    ///--
    while (getline(file1, s))
    {

        ///--
        ///--Отладочная проверка
        ///--
        if (i_counter == 9998)
        {
            int b = 0;
            //break;
        }

        const char * cstr = s.c_str();									// получаем строку в стиле C

        ///--
        ///--Цикл перебора строки
        ///--
        for (unsigned int i = 0; i < strlen(cstr); i++)
        {
            value_to_push = (double)((int)(cstr[i]));					// нормализуем входное значение для дальнейшей обработки
            pushAgent(value_to_push, true);								// заводим значение в модель
            cout << cstr[i] << "\t " <<  ((int)cstr[i]) << "\t " << (int)i_counter << endl; 	// выводим на экран
            i_counter++;
        }

    }

    file1.close(); // закрываем файл

    return 0;

}

int main()
{

    //ProcessPoints();
    ProcessChars();

    system("pause");
    return 0;
}
