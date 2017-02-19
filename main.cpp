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

    BooksToRead.push_back("/home/vortex/ClionProjects/Taber_The_Red_White_and_Blue_Universe_1_RED_Burning_Skies_RuLit_Me.txt");
	BooksToRead.push_back("/home/vortex/ClionProjects/Leo");
	BooksToRead.push_back("/home/vortex/ClionProjects/Deas_thief_takers_apprentice_2_Warlocks_shadow_RuLit_Net.txt");
    BooksToRead.push_back("/home/vortex/ClionProjects/Schwarze_Alien_Domicile_Escape_Area_51_RuLit_Me.txt");
    BooksToRead.push_back("/home/vortex/ClionProjects/Bolduin_Alexi_Sokolsky_Hound_of_Eden_1_Blood_Hound_RuLit_Me.txt");

    BooksToRead.push_back("/home/vortex/ClionProjects/Hagberg_The_Shadowmen_RuLit_Me.txt");
    BooksToRead.push_back("/home/vortex/ClionProjects/Karlson_The_Gambit_RuLit_Me.txt");
    BooksToRead.push_back("/home/vortex/ClionProjects/Davidson_The_Deep_RuLit_Me.txt");
    BooksToRead.push_back("/home/vortex/ClionProjects/Ebbot_History_of_Julius_Caesar_RuLit_Me.txt");
    BooksToRead.push_back("/home/vortex/ClionProjects/Ebbot_Marco_Paul_s_Voyages_and_Travels_Vermont_RuLit_Me.txt");

    BooksToRead.push_back("/home/vortex/ClionProjects/Forsten_John_Matherson_3_The_Final_Day_RuLit_Me.txt");
    BooksToRead.push_back("/home/vortex/ClionProjects/Koffi_Silent_Waters_RuLit_Me.txt");
    BooksToRead.push_back("/home/vortex/ClionProjects/Middleton_The_Boris_Chronicles_3_Revelations_RuLit_Me.txt");
    BooksToRead.push_back("/home/vortex/ClionProjects/the_lovers_RuLit_Net_96636.txt");
    BooksToRead.push_back("/home/vortex/ClionProjects/Danseyni_A_Night_at_an_Inn_RuLit_Me.txt");

    BooksToRead.push_back("/home/vortex/ClionProjects/Danseyni_Why_the_Milkman_Shudders_When_He_Perceives_the_Dawn_RuLit_Me.txt");

    //--
    //--Инициализируем вихрь
    //--
    InitializeVortex(
                        40,         // размерность матрицы
                        0, 	// шаг в процентах между полюсами
                        1000,       // максимальный размер кольца
                        0.001,      // коэффициент ослабления
                        1           // шаг укрепления связи
					);

    int 	i_counter 		   = 1;	   // отладочный счетчик
    int 	nextchar  		   = 0;	   // прогноз на следующий знак
    int 	total_counter 	   = 0;	   // общий подсчет совпадений
    double 	reliability 	   = 0;	   // надежность
    int     distance           = 0;    // дистанция
	
	double 	value_to_push 	= 0;	// для хранения входного значения
    string 	s;     					// сюда будем ложить считанную строку
	ForecastedValue FCV_G; 			// Полученный прогноз
    double MAXIMAL_PERCENTAGE = 0;
    int prev_char             = 0;
	
    for(int times_counter = 0; times_counter < 1; times_counter++)
    {



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
                if (i_counter > 3000)
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

                    if(value_to_push < 32 || (value_to_push == 32 && prev_char == 32))
                    {
                        prev_char = value_to_push;
                        continue;
                    }

                    if(value_to_push >=65 && value_to_push <=90)
                    {
                        value_to_push = value_to_push + 32;
                    }

                    if( ((int)value_to_push) == nextchar)
                    {
                        total_counter++;
                    }


                    double current_percentage = (double)(((double)total_counter) / i_counter * 100) ;

                    //--
                    //--Выводим на экран
                    //--
                    cout << cstr[i] << "\t " << ((int)cstr[i]) 			// номер символа
                         << "\t " << nextchar 				            // символ
                         << "\t " << (char)nextchar                     // символ
                         << "\t " << reliability << "% "                // надежность в процентах
                         << "\t " << distance                           // дистанция
                         << "\t " << (int)i_counter                     // счетчик всего перебранных символов
                         << "\t " << total_counter                      // счетчик совпадений
                         << "\t " << current_percentage << "% "
                         << "\t " << MAXIMAL_PERCENTAGE << "% "
                         << "\t " << book_number + 1 << endl;

                    if(current_percentage > MAXIMAL_PERCENTAGE)
                    {
                        MAXIMAL_PERCENTAGE = current_percentage;
                    }

                    FCV_G = pushAgent(value_to_push, true);	// заводим значение в модель
                    nextchar 	=	(int)FCV_G.value; 		// значение
                    reliability =	FCV_G.reliability;		// надежность
                    distance    =   (int)FCV_G.distance;    // дистанция

                    prev_char = value_to_push;

                    i_counter++;
                }


            }

            file.close(); // закрываем файл
        }

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
