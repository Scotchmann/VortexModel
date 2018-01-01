// ConsoleApplication1.cpp : Defines the entry point for the console application.
// DiagonalSearch branch

#include "VortexModel.h"
#include <cstring>
#include <math.h>


using namespace std;

int ProcessPoints_()
{
    // сюда будем ложить считанные строки
    ifstream file("/home/vortex/Dropbox/VortexModel_linux/EUR_USD_5mitunes_TOD.txt");    	// файл из которого читаем

                                                    ///--
                                                    ///--Инициализируем вихрь
                                                    ///--
    InitializeVortex(
        40, 		//
        0.0000, 	// Шаг в процентах между полюсами
        500000, 	// Максимальный размер кольца
        0.00001, // Коэффициент ослабления
        1		// Шаг укрепления связи
    );


    int i;					// отладочный счетчик
    i = 1;


    int 	i_counter = 1;		// отладочный счетчик
    double 	nextchar = 0;	   	// прогноз на следующий знак
    int 	total_counter = 0;	   	// общий подсчет совпадений
    double 	reliability = 0;	   	// надежность
    int     distance = 0;    	// дистанция

    double 	value_to_push = 0;		// для хранения входного значения
    string 	s;     						// сюда будем ложить считанную строку
    ForecastedValue FCV_G; 				// полученный прогноз
    double MAXIMAL_PERCENTAGE = 0;     // максимальный зарегистрированный процентаж
    double Prevval = 1;

    bool IsBigger = false;
    bool IsLower = false;

    ///--
    ///--Цикл перебора строк файла
    ///--
    while (getline(file, s))
    {
        //     if (i == 4000)
        //     {
        //file.seekg(0, file.beg);
        //i = 1;
        //         //break;
        //     }

        value_to_push = atof(s.c_str());			// нормализуем входное значение для дальнейшей обработки

        value_to_push = trunc(value_to_push * 100000) / 100000;

        string _IsBigger = "!";
        string _IsLower = "!";
        _IsBigger = IsBigger ? "1" : "0";
        _IsLower = IsLower ? "1" : "0";


        if (IsBigger == IsLower)
        {
            _IsBigger = _IsLower = '-';
        }

        if (nextchar != 0)
        {
            if (((Prevval < value_to_push) == IsBigger) && ((Prevval > value_to_push) == IsLower))
            {
                _IsBigger = "\033[32m" + _IsBigger + "\033[0m";
                _IsLower  = "\033[32m" + _IsLower  + "\033[0m";
                total_counter++;
            }
            else
            {
                _IsBigger = "\033[31m" + _IsBigger + "\033[0m";
                _IsLower  = "\033[31m" + _IsLower  + "\033[0m";
            }
        }
        double current_percentage = (double)(((double)total_counter) / i_counter * 100);


        cout << "\t " << i                     // счетчик всего перебранных символов
            << "\t " << value_to_push
            << "\t " << nextchar + Prevval - 100      		// прогнозируемый символ
            << "\t " << _IsBigger                     		//
            << "\t " << _IsLower
            << "\t " << reliability << "% "                // надежность в процентах
            << "\t " << distance                           // дистанция
            << "\t " << (int)i_counter                     // счетчик всего перебранных символов
            << "\t " << total_counter                      // счетчик совпадений
            << "\t " << current_percentage << "% "			// текущий процентаж совпадений
            << "\t " << MAXIMAL_PERCENTAGE << "% " << endl;	// максимальный зарегистрированный процентаж


        if (current_percentage > MAXIMAL_PERCENTAGE && i_counter > 500)
        {
            MAXIMAL_PERCENTAGE = current_percentage;
        }


        double value_to_push_ = value_to_push - Prevval + 100;

        //--
        //--Заводим значение в модель и получаем прогноз
        //--
        FCV_G = pushAgent(value_to_push_, true);

        nextchar = FCV_G.value;     		// значение
        reliability = FCV_G.reliability * 100;		// надежность
        distance = (int)FCV_G.distance;    // дистанция

                                           //--
                                           //--Обновляем предыдущее значение
                                           //--

        double toRound = (nextchar + value_to_push - 100) * 1000000;
        IsBigger = (double)((int)toRound) / 1000000 > value_to_push;
        IsLower = (double)((int)toRound) / 1000000 < value_to_push;
        Prevval = value_to_push;



        if (IsBigger == IsLower)
        {
            int test_ = 1;
        }


        if (nextchar != 0)
            i_counter++;

        i++;

    }

    file.close(); // закрываем файл

    return 0;
}


int ProcessPoints()
{
    // сюда будем ложить считанные строки
    ifstream file("/home/vortex/Dropbox/VortexModel_linux/EUR_USD_5mitunes_TOD.txt");    	// файл из которого читаем

    ///--
    ///--Инициализируем вихрь
    ///--
    InitializeVortex(
                40, 		//
                0.0000, 	// Шаг в процентах между полюсами
                500000, 	// Максимальный размер кольца
                0.00001, // Коэффициент ослабления
                1		// Шаг укрепления связи
                );


    int i;					// отладочный счетчик
    i = 1;


    int 	i_counter 		   = 1;		// отладочный счетчик
    double 	nextchar  		   = 0;	   	// прогноз на следующий знак
    int 	total_counter 	   = 0;	   	// общий подсчет совпадений
    double 	reliability 	   = 0;	   	// надежность
    int     distance           = 0;    	// дистанция

    double 	value_to_push 	   = 0;		// для хранения входного значения
    string 	s;     						// сюда будем ложить считанную строку
    ForecastedValue FCV_G; 				// полученный прогноз
    double MAXIMAL_PERCENTAGE  = 0;     // максимальный зарегистрированный процентаж
    double Prevval = 1;

    bool IsBigger = false;
    bool IsLower  = false;

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

        string _IsBigger = "!";
        string _IsLower  = "!";
        _IsBigger = IsBigger ? "1":"0";
        _IsLower  = IsLower  ? "1":"0";


        if (IsBigger == IsLower)
        {
            _IsBigger = _IsLower = '-';
        }

        if(nextchar != 0)
        {
            if(  (( Prevval < value_to_push) == IsBigger )  &&   (( Prevval > value_to_push) == IsLower )   )
            {
                _IsBigger = "\033[32m" + _IsBigger + "\033[0m";
                _IsLower  = "\033[32m" + _IsLower  + "\033[0m";
                total_counter++;
            }
            else
            {
                _IsBigger = "\033[31m" + _IsBigger + "\033[0m";
                _IsLower  = "\033[31m" + _IsLower  + "\033[0m";
            }
        }
        double current_percentage = (double)(((double)total_counter) / i_counter * 100) ;


            cout << "\t " << value_to_push
                 << "\t " << nextchar * Prevval           		// прогнозируемый символ
                 << "\t " << _IsBigger                     		//
                 << "\t " << _IsLower
                 << "\t " << reliability << "% "                // надежность в процентах
                 << "\t " << distance                           // дистанция
                 << "\t " << (int)i_counter                     // счетчик всего перебранных символов
                 << "\t " << total_counter                      // счетчик совпадений
                 << "\t " << current_percentage << "% "			// текущий процентаж совпадений
                 << "\t " << MAXIMAL_PERCENTAGE << "% "<< endl;	// максимальный зарегистрированный процентаж


            if(current_percentage > MAXIMAL_PERCENTAGE && i_counter > 500)
            {
                MAXIMAL_PERCENTAGE = current_percentage;
            }


        double value_to_push_ = value_to_push / Prevval;

        //--
        //--Заводим значение в модель и получаем прогноз
        //--
        FCV_G = pushAgent(value_to_push_, true);

        nextchar 	=	FCV_G.value;     		// значение
        reliability =	FCV_G.reliability * 100;		// надежность
        distance    =   (int)FCV_G.distance;    // дистанция

        //--
        //--Обновляем предыдущее значение
        //--

        double toRound = nextchar * value_to_push * 1000000;
        IsBigger = (double)((int)toRound)/1000000 > value_to_push ;
        IsLower  = (double)((int)toRound)/1000000 < value_to_push;
        Prevval   = value_to_push;



        if(IsBigger == IsLower)
        {
            int test_ = 1;
        }


        if (nextchar != 0 )
            i_counter++;

    }

    file.close(); // закрываем файл

    return 0;
}

int ProcessChars()
{
    std::vector<string> BooksToRead;

    BooksToRead.push_back("/opt/ClionProjects/Taber_The_Red_White_and_Blue_Universe_1_RED_Burning_Skies_RuLit_Me.txt");
    BooksToRead.push_back("/opt/ClionProjects/Leo");
    BooksToRead.push_back("/opt/ClionProjects/Deas_thief_takers_apprentice_2_Warlocks_shadow_RuLit_Net.txt");
    BooksToRead.push_back("/opt/ClionProjects/Schwarze_Alien_Domicile_Escape_Area_51_RuLit_Me.txt");
    BooksToRead.push_back("/opt/ClionProjects/Bolduin_Alexi_Sokolsky_Hound_of_Eden_1_Blood_Hound_RuLit_Me.txt");

    BooksToRead.push_back("/opt/ClionProjects/Hagberg_The_Shadowmen_RuLit_Me.txt");
    BooksToRead.push_back("/opt/ClionProjects/Karlson_The_Gambit_RuLit_Me.txt");
    BooksToRead.push_back("/opt/ClionProjects/Davidson_The_Deep_RuLit_Me.txt");
    //BooksToRead.push_back("/opt/ClionProjects/Ebbot_History_of_Julius_Caesar_RuLit_Me.txt");
    //BooksToRead.push_back("/opt/ClionProjects/Ebbot_Marco_Paul_s_Voyages_and_Travels_Vermont_RuLit_Me.txt");

    BooksToRead.push_back("/opt/ClionProjects/Forsten_John_Matherson_3_The_Final_Day_RuLit_Me.txt");
    BooksToRead.push_back("/opt/ClionProjects/Koffi_Silent_Waters_RuLit_Me.txt");
    BooksToRead.push_back("/opt/ClionProjects/Middleton_The_Boris_Chronicles_3_Revelations_RuLit_Me.txt");
    BooksToRead.push_back("/opt/ClionProjects/the_lovers_RuLit_Net_96636.txt");
    BooksToRead.push_back("/opt/ClionProjects/Danseyni_A_Night_at_an_Inn_RuLit_Me.txt");

    BooksToRead.push_back("/opt/ClionProjects/Danseyni_Why_the_Milkman_Shudders_When_He_Perceives_the_Dawn_RuLit_Me.txt");

    //--
    //--Инициализируем вихрь
    //--
    InitializeVortex(
                40,         	// размерность матрицы
                0, 				// шаг в процентах между полюсами
                1000,       	// максимальный размер кольца
                0.001,      	// коэффициент ослабления
                1           	// шаг укрепления связи
                );

    int 	i_counter 		   = 1;		// отладочный счетчик
    int     f_counter          = 0;     //
    int 	nextchar  		   = 0;	   	// прогноз на следующий знак
    int 	total_counter 	   = 0;	   	// общий подсчет совпадений
    double 	reliability 	   = 0;	   	// надежность
    int     distance           = 0;    	// дистанция

    double 	value_to_push 	   = 0;		// для хранения входного значения
    string 	s;     						// сюда будем ложить считанную строку
    ForecastedValue FCV_G; 				// полученный прогноз
    double MAXIMAL_PERCENTAGE  = 0;     // максимальный зарегистрированный процентаж
    int prev_char              = 0;		// предыдущее заведенный символ


    for(int times_counter = 0; times_counter < 1; times_counter++)
    {

        //--
        //--Читаем переданные книги
        //--
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

                    //--
                    //--Отсекаем нечитаемые символы
                    //--
                    if(value_to_push < 32 || (value_to_push == 32 && prev_char == 32))
                    {
                        prev_char = value_to_push;
                        continue;
                    }

                    //--
                    //--Переводим заводимое значение в нижний регистр
                    //--
                    if(value_to_push >=65 && value_to_push <=90)
                    {
                        value_to_push = value_to_push + 32;
                    }

                    //--
                    //--Проверяем совпадение
                    //--
                    if( ((int)value_to_push) == nextchar && reliability > 50)
                    {
                        total_counter++;
                    }


                    double current_percentage = f_counter == 0 ? 0 : (double)(((double)total_counter) / f_counter * 100) ;

                    //--
                    //--Выводим на экран
                    //--


                    cout << cstr[i] << "\t " << ((int)cstr[i]) 			// номер символа
                         << "\t " << nextchar 				            // прогнозируемый символ
                         << "\t " << (char)nextchar                     // номер прогнозируемого символа
                         << "\t " << reliability << "% "                // надежность в процентах
                         << "\t " << distance                           // дистанция
                         << "\t " << (int)i_counter                     // счетчик всего перебранных символов
                         << "\t " << (int)f_counter                     // счетчик всего  символов
                         << "\t " << total_counter                      // счетчик совпадений
                         << "\t " << current_percentage << "% "			// текущий процентаж совпадений
                         << "\t " << MAXIMAL_PERCENTAGE << "% "			// максимальный зарегистрированный процентаж
                         << "\t " << book_number + 1 << endl;			// текущая читаемая книга

                    if(current_percentage > MAXIMAL_PERCENTAGE)
                    {
                        MAXIMAL_PERCENTAGE = current_percentage;
                    }

                    //--
                    //--Заводим значение в модель и получаем прогноз
                    //--
                    FCV_G = pushAgent(value_to_push, true);
                    
                    nextchar 	=	(int)FCV_G.value; 		// значение
                    reliability =	FCV_G.reliability * 100;		// надежность
                    distance    =   (int)FCV_G.distance;    // дистанция

                    if(reliability > 50)
                        f_counter++;

                    //--
                    //--Обновляем предыдущее значение
                    //--
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
    //ProcessPoints_();
    ProcessChars();

    system("pause");
    return 0;
}
