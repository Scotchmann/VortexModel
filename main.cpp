// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "VortexModel.h"

#include <iostream>
#include <fstream>

using namespace std;

int main()
{

    double value_to_push = 0;

    string s;                                                       // сюда будем ложить считанные строки
    ifstream file("/home/vortex/ClionProjects/ProcessData.txt");    // файл из которого читаем (для линукс путь будет выглядеть по другому)

    InitializeVortex();
    int i;
    i = 1;

    //DrawChart();

    while (getline(file, s))
    {
        if (i == -41)
        {
            int b = 0;
            break;
        }
        value_to_push = atof(s.c_str());

        pushAgent(value_to_push, true);

        cout << value_to_push << " " << i << endl; // выводим на экран
        i++;
    }

    file.close(); // обязательно закрываем файл что бы не повредить его

    system("pause");
    return 0;
}