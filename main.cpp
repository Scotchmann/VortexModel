
#include "VortexModel.h"
#include <cstring>
#include <math.h>

using namespace std;

#ifdef linux
    const string red_marker     = "\033[31m";    // красный маркер для вывода в терминале
    const string green_marker   = "\033[32m";    // зеленый маркер для вывода в терминале
    const string default_marker = "\033[0m";     // сброс маркеров вывода в терминале
#else
    const string red_marker     = "";
    const string green_marker   = "";
    const string default_marker = "";
#endif

struct ModeStruct
{
    string mode;                                  // режим
    bool   activated;                             // признак активности
    int(*proc_func)(std::vector<string>, int);    // функция обработки режима
    string description;
};

int ProcessPoints_(vector<string> FilesToRead, int file_number = 0)
{
    //  Инициализируем вихрь
    InitializeVortex(
                      40,             // глубина матрицы
                      0.0000,         // шаг в процентах между полюсами
                      500000,         // максимальный размер кольца
                      0.00001,        // коэффициент ослабления
                      1               // шаг укрепления связи
                    );

    int i = 1;                        // отладочный счетчик

    int 	i_counter     = 1;        // отладочный счетчик
    double 	nextchar      = 0;        // прогноз на следующий знак
    int 	total_counter = 0;        // общий подсчет совпадений
    double 	reliability   = 0;        // надежность
    int     distance      = 0;        // дистанция

    double 	value_to_push     = 0;    // для хранения входного значения
    string 	s;                        // сюда будем ложить считанную строку
    ForecastedValue FCV_G;            // полученный прогноз
    double MAXIMAL_PERCENTAGE = 0;    // максимальный зарегистрированный процентаж
    double Prevval            = 1;

    bool IsBigger = false;
    bool IsLower  = false;

	for(; file_number < FilesToRead.size(); file_number++)
    {
		ifstream file(FilesToRead[file_number]);    // файл из которого читаем

		//  Цикл перебора строк файла
		while (getline(file, s))
		{
            //  Отладочное циклирование

			//if (i == 4000)
			//{
			//    file.seekg(0, file.beg);
			//    i = 1;
			//    //break;
			//}

            //  Нормализуем входное значение для дальнейшей обработки
			value_to_push = atof(s.c_str());

			value_to_push = trunc(value_to_push * 100000) / 100000;

			string _IsBigger = "!";
			string _IsLower  = "!";
			_IsBigger = IsBigger ? "1" : "0";
			_IsLower  = IsLower  ? "1" : "0";

			if (IsBigger == IsLower)
			{
				_IsBigger = _IsLower = '-';
			}

			if (nextchar != 0)
			{
				if ( ((Prevval < value_to_push) == IsBigger)
                &&   ((Prevval > value_to_push) == IsLower ) )
				{
					_IsBigger = green_marker + _IsBigger + default_marker;
					_IsLower  = green_marker + _IsLower  + default_marker;
					total_counter++;
				}
				else
				{
					_IsBigger = red_marker + _IsBigger + default_marker;
					_IsLower  = red_marker + _IsLower  + default_marker;
				}
			}

            double current_percentage = (double)(((double)total_counter) / i_counter * 100);

			cout << "\t " << i                          // счетчик всего перебранных символов
                 << "\t " << value_to_push              // заводимое значение
                 << "\t " << nextchar + Prevval - 100   // прогнозируемый символ
                 << "\t " << _IsBigger                  //
                 << "\t " << _IsLower                   //
                 << "\t " << reliability << "% "        // надежность в процентах
                 << "\t " << distance                   // дистанция
                 << "\t " << (int)i_counter             // счетчик всего перебранных символов
                 << "\t " << total_counter              // счетчик совпадений
                 << "\t " << current_percentage << "% " // текущий процентаж совпадений
                 << "\t " << MAXIMAL_PERCENTAGE << "% " // максимальный зарегистрированный процентаж
                 << endl  << flush;

			if (current_percentage > MAXIMAL_PERCENTAGE && i_counter > 500)
			{
				MAXIMAL_PERCENTAGE = current_percentage;
			}

			double value_to_push_ = value_to_push - Prevval + 100;

			//  Заводим значение в модель и получаем прогноз
			FCV_G = pushAgent(value_to_push_, true);

			nextchar    = FCV_G.value;                  // значение
			reliability = FCV_G.reliability * 100;      // надежность
			distance    = (int)FCV_G.distance;          // дистанция

			//  Обновляем предыдущее значение
			double rounded = (double)((int)(nextchar + value_to_push - 100) * 1000000) / 1000000;
			IsBigger = rounded > value_to_push;
			IsLower  = rounded < value_to_push;
			Prevval  = value_to_push;

			if (IsBigger == IsLower)
			{
				int test_ = 1;
			}

			if (nextchar != 0) i_counter++;

			i++;
		}

        //  Закрываем файл
		file.close();
	}

    return 0;
}

int ProcessPoints(vector<string> FilesToRead, int file_number = 0)
{
    //  Инициализируем вихрь
    InitializeVortex(
                      40,              // глубина матрицы
                      0.0000,          // шаг в процентах между полюсами
                      500000,          // максимальный размер кольца
                      0.00001,         // коэффициент ослабления
                      1                // шаг укрепления связи
                    );

    int     i                  = 1;    // отладочный счетчик
    int 	i_counter 		   = 1;    // отладочный счетчик
    double 	nextchar  		   = 0;    // прогноз на следующий знак
    int 	total_counter 	   = 0;    // общий подсчет совпадений
    double 	reliability 	   = 0;    // надежность
    int     distance           = 0;    // дистанция

    double 	value_to_push 	   = 0;    // для хранения входного значения
    string 	s;                         // сюда будем ложить считанную строку
    ForecastedValue FCV_G;             // полученный прогноз
    double MAXIMAL_PERCENTAGE  = 0;    // максимальный зарегистрированный процентаж
    double Prevval = 1;                //

    bool IsBigger = false;             //
    bool IsLower  = false;             //

	for(; file_number < FilesToRead.size(); file_number++)
    {
		ifstream file(FilesToRead[file_number]);    // файл из которого читаем

		//  Цикл перебора строк файла
		while (getline(file, s))
		{
			if (i == 9998)
			{
				int b = 0;
				//break;
			}

            //  Нормализуем входное значение для дальнейшей обработки
			value_to_push = atof(s.c_str());

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
				if(  (( Prevval < value_to_push) == IsBigger )
                &&   (( Prevval > value_to_push) == IsLower  )   )
				{
					_IsBigger = green_marker + _IsBigger + default_marker;
					_IsLower  = green_marker + _IsLower  + default_marker;
					total_counter++;
				}
				else
				{
					_IsBigger = red_marker + _IsBigger + default_marker;
					_IsLower  = red_marker + _IsLower  + default_marker;
				}
			}

			double current_percentage = ((double)total_counter) / i_counter * 100;

			cout << "\t " << value_to_push              // заводимое значение
				 << "\t " << nextchar * Prevval         // прогнозируемый символ
				 << "\t " << _IsBigger                  //
				 << "\t " << _IsLower                   //
				 << "\t " << reliability << "% "        // надежность в процентах
				 << "\t " << distance                   // дистанция
				 << "\t " << (int)i_counter             // счетчик всего перебранных символов
				 << "\t " << total_counter              // счетчик совпадений
				 << "\t " << current_percentage << "% " // текущий процентаж совпадений
				 << "\t " << MAXIMAL_PERCENTAGE << "% " // максимальный зарегистрированный процентаж
                 << endl  << flush;

			if(current_percentage > MAXIMAL_PERCENTAGE && i_counter > 500)
			{
				MAXIMAL_PERCENTAGE = current_percentage;
			}

			double value_to_push_ = value_to_push / Prevval;

			//  Заводим значение в модель и получаем прогноз
			FCV_G = pushAgent(value_to_push_, true);

			nextchar 	=	FCV_G.value;                // значение
			reliability =	FCV_G.reliability * 100;    // надежность
			distance    =   (int)FCV_G.distance;        // дистанция

			//  Обновляем предыдущее значение
			double rounded = (double)((int)nextchar * value_to_push * 1000000)/1000000;
			IsBigger = rounded > value_to_push ;
			IsLower  = rounded < value_to_push;
			Prevval  = value_to_push;

			if(IsBigger == IsLower)
			{
				int test_ = 1;
			}

			if (nextchar != 0 ) i_counter++;
		}

        //  Закрываем файл
		file.close();
	}

    return 0;
}

int ProcessChars(vector<string> BooksToRead, int book_number = 0)
{
    //  Инициализируем вихрь
    InitializeVortex(
                      40,              // размерность матрицы
                      0,               // шаг в процентах между полюсами
                      1000,            // максимальный размер кольца
                      0.001,           // коэффициент ослабления
                      1                // шаг укрепления связи
                    );

    int 	i_counter 		   = 1;    // отладочный счетчик
    int     f_counter          = 0;    //
    int 	nextchar  		   = 0;    // прогноз на следующий знак
    int 	total_counter 	   = 0;    // общий подсчет совпадений
    double 	reliability 	   = 0;    // надежность
    int     distance           = 0;    // дистанция
    double 	value_to_push 	   = 0;    // для хранения входного значения
    string 	s;                         // сюда будем ложить считанную строку
    ForecastedValue FCV_G;             // полученный прогноз
    double MAXIMAL_PERCENTAGE  = 0;    // максимальный зарегистрированный процентаж
    int prev_char              = 0;    // предыдущее заведенный символ

    for(int times_counter = 0; times_counter < 1; times_counter++)
    {
        //  Читаем переданные книги
        for(; book_number < BooksToRead.size(); book_number++)
        {
            ifstream file(BooksToRead[book_number]);   // файл из которого читаем

            //  Цикл перебора строк файла
            while (getline(file, s))
            {
                //  Отладочная проверка
                if (i_counter > 3000)
                {
                    int b = 0;
                    //break;
                }

                //  Получаем С-строку
                const char * cstr = s.c_str();

                //  Цикл перебора строки
                for (unsigned int i = 0; i < strlen(cstr); i++)
                {
                    //  Нормализуем входное значение для дальнейшей обработки
                    value_to_push = (double)(cstr[i]);

                    //  Отсекаем нечитаемые символы
                    if(value_to_push < 32 || (value_to_push == 32 && prev_char == 32))
                    {
                        prev_char = value_to_push;
                        continue;
                    }

                    //  Переводим заводимое значение в нижний регистр
                    if(value_to_push >= 65 && value_to_push <= 90)
                    {
                        value_to_push = value_to_push + 32;
                    }

                    //  Проверяем совпадение
                    if( ((int)value_to_push) == nextchar && reliability > 50)
                    {
                        total_counter++;
                    }

                    double current_percentage = 0;             // текущий процентаж совпадений

                    if(f_counter != 0)
                    {
                        current_percentage = (double)(((double)total_counter) / f_counter * 100);
                    }

                    //  Выводим на экран

                    cout << cstr[i]                            //
                         << "\t " << ((int)cstr[i])            // номер символа
                         << "\t " << nextchar                  // прогнозируемый символ
                         << "\t " << (char)nextchar            // номер прогнозируемого символа
                         << "\t " << reliability << "% "       // надежность в процентах
                         << "\t " << distance                  // дистанция
                         << "\t " << (int)i_counter            // счетчик всего перебранных символов
                         << "\t " << (int)f_counter            // счетчик всего  символов
                         << "\t " << total_counter             // счетчик совпадений
                         << "\t " << current_percentage << "% "// текущий процентаж совпадений
                         // максимальный зарегистрированный процентаж
                         << "\t " << MAXIMAL_PERCENTAGE << "% "
                         << "\t " << book_number + 1 << endl;  // текущая читаемая книга

                    if(current_percentage > MAXIMAL_PERCENTAGE)
                    {
                        MAXIMAL_PERCENTAGE = current_percentage;
                    }

                    //  Заводим значение в модель и получаем прогноз
                    FCV_G = pushAgent(value_to_push, true);

                    nextchar 	=	(int)FCV_G.value;           // значение
                    reliability =	FCV_G.reliability * 100;    // надежность
                    distance    =   (int)FCV_G.distance;        // дистанция

                    if(reliability > 50) f_counter++;

                    //  Обновляем предыдущее значение
                    prev_char = value_to_push;

                    i_counter++;
                }
            }

            file.close(); // закрываем файл
        }
    }

    return 0;
}

int main(int argc, char **argv)
{
	string list_of_files_to_read;
	std::vector<string> files_to_read;
	string s;

    std::vector<ModeStruct> mode_map;
    int file_number = 0;

    mode_map.push_back({"-pp" , false, ProcessPoints, "processes numeric data in the given file"});
    mode_map.push_back({"-pc" , false, ProcessChars, "processes text data in the given file"});
    mode_map.push_back({"-pp_", false, ProcessPoints_, "processes numeric data in the given file"});

	for (int i = 1; i < argc; ++i)
	{
        //  Триггер режимов {{{
        for (auto& it_i : mode_map)
		{
			if(it_i.mode == string(argv[i]))
			{
				it_i.activated = true;

				for (auto& it_j : mode_map)
				{
					if(&it_i == &it_j) continue;

                    it_j.activated = false;
				}
			}
		}
        //  }}} Триггер режимов

        if (string(argv[i]) == "-l")
		{
			if( i+1 <= argc )
			{
				list_of_files_to_read = string(argv[i+1]);

                ifstream file(argv[i+1]);

				while (getline(file, s)) files_to_read.push_back(s);

				file.close();

				i++;
				continue;
			}
			else
			{
				cout << "List of files to read is not specified." << endl;
                exit(1);
			}
		}

		files_to_read.push_back(string(argv[i]));
	}

	for (const auto& it : mode_map)
	{
		if(it.activated)
		{
            while (true)
            {
                // Вызываем функцию обработки режима
    			(*(it.proc_func))(files_to_read, file_number);

                cout << endl << flush;

                while (true)
                {
                    cout << "Reading has ended. Would you like to continue?(y\\n): " << flush;
                    string  answer;
                    cin  >> answer;

                    if(answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes")
                    {
                        string one_more_file = "";
                        cout << "Please, put one more file to read: " << flush;
                        cin >> one_more_file;

                        files_to_read.push_back(one_more_file);
                        file_number = files_to_read.size() - 1;
                        break;
                    }
                    else if(answer == "n" || answer == "N" || answer == "no" || answer == "No")
                    {
                        exit(0);
                    }
                    else
                    {
                        cout << "Wrong input!" << endl << flush;
                    }
                }
            }

			return 0;
		}
	}

	cout << "Mode of processing is not specified." << endl << flush;
	cout << "All modes possible are listed below:" << endl << flush;

	for (const auto& it : mode_map)
	{
		cout << it.mode << " :\t" << it.description << endl << flush;
	}

    exit(0);
}
