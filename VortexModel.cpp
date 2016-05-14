// TestDLL.cpp : Defines the exported functions for the DLL application.
//
#include "VortexModel.h"
//#include <root/TRandom.h>
using namespace std;

Vortex * ptr_UpVortex;
Vortex * ptr_DownVortex;

const int 	ArraySize 	= 130;	// Размер массива
int 		counter 	= 1;	// Счетчик

int _count = 0;    // Размер масива У,Х
float* X;           // масив для хранение х-ов
float* Y;           // масив для хранения у-ов

///--
///--Инициализация вихря
///--
void InitializeVortex()
{
    ptr_UpVortex 	= new Vortex(ArraySize, 1);
    //ptr_DownVortex 	= new Vortex(ArraySize, 1);

    // Стандартное создание окна в OpenGl
    int argc = 0;
    char ** argv = nullptr;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(20, 810);
    glutCreateWindow("Chart");
    //glClearColor(0.53, 0.97, 0.57, 0);
    glClearColor(0.0, 0.0, 0.0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3, 100, -3, 100, -100, 100);


}

///--
///--Заводит значение в вихрь
///--
double pushAgent(double value, bool Up)
{
    DrawChart();
    Vortex * ptr_PrimalVortex = nullptr;

    Up ? ptr_PrimalVortex = ptr_UpVortex : ptr_PrimalVortex = ptr_DownVortex;

    return ptr_PrimalVortex->pushAgent(value);
}


double getAgent(int i, int j, bool Up)
{
    double size = 0;

    //Up ? size = AgentsUpTrend[i][j].InnerAgent->mutation_percentage : size = AgentsDownTrend[i][j].InnerAgent->mutation_percentage;

    size = ptr_UpVortex->GetAgent(i, j);

    return size;
}

int GetDistance()
{
    int i = 0;
    i = ptr_UpVortex->GetDistance();

    return i;
}

double GetBuf()
{
    double i = 0;
    i = ptr_UpVortex->GetBuf();

    return i;
}

void display(){                    // Функция перерисовки экрана
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0, 100, 0);   // Рисование системы координат
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(100, 0, 0);

    for(int i = -10; i < 20; i++){
        glVertex3f(10 + i * 5, -0.5, 0);
        glVertex3f(10 + i * 5, 0.5, 0);
    }

    for(int i = -10; i < 20; i++){
        glVertex3f(-0.5, 10 + i * 5 , 0);
        glVertex3f(0.5, 10 + i * 5 , 0);
    }// Конец рисования системы крдинат

    glEnd();

    glBegin(GL_POINTS); // Рисование точек графика функции
    //glColor3f(0.13, 0.67, 0.82);
    glColor3f(1.0, 1.0, 1.0);
    float y;
    for(int i = 0; i < _count; i++)
    {
        glVertex3f(X[i], Y[i], 0);
    }
    glEnd();
    glutSwapBuffers();
}

int DrawChart()
{
    vector<float> arrY;  // Вектор игреков
    vector<float> arrX;  // Вектор иксов


    for(int i = 0; i <= 1; ++i)
    {
        arrY.push_back(rand() % 145 +1);
        //arrY.push_back(i);

    }

    for(int i = 0; i <= 1; ++i)
    {
        arrX.push_back(rand() % 145 +1);
        //arrX.push_back(i);

    }



    X = new float[arrX.size()];  // Создание масива с х
    Y = new float[arrY.size()];  // Создание масива с У


    for(int j = 0; j < arrX.size(); j++)
    {

            // диапазона в массив Х
            X[j] = arrX[j];

    }

    for(int j = 0; j < arrY.size(); j++)
    {

        // диапазона в массив Y
        Y[j] = arrY[j];

    }

    _count = (int)arrX.size();
    glutDisplayFunc(display);
    display();
    //    glutMainLoop();
    delete [] X;
    delete [] Y;
}