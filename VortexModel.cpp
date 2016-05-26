// TestDLL.cpp : Defines the exported functions for the DLL application.
//
#include "VortexModel.h"
//#include <root/TRandom.h>
using namespace std;

Vortex * ptr_UpVortex;
Vortex * ptr_DownVortex;

const int 	ArraySize 	= 130;	// Размер массива
int 		counter 	= 1;	// Счетчик

int 		_count 		= 0;    // Размер масива У,Х
float* 		X;           		// масив для хранение х-ов
float* 		Y;           		// масив для хранения у-ов
double      d_maximal_reliability = 0; // максимальная надежность

CumulativeVector _CumulativeContainer;

///--
///--Инициализация вихря
///--
void InitializeVortex()
{
    ptr_UpVortex 	= new Vortex(ArraySize, 1);
    //ptr_DownVortex 	= new Vortex(ArraySize, 1);

	///--
    ///-- Стандартное создание окна в OpenGl
    ///--
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



    CheckIfForecastIsEmty:
    for (auto it = _CumulativeContainer.begin(); it != _CumulativeContainer.end(); ++it)
    {
        delete *it;
        _CumulativeContainer.erase(it);
        goto CheckIfForecastIsEmty;
    }

    if(_CumulativeContainer.size() > 0)
    {
        _CumulativeContainer.clear();
    }




    Vortex * ptr_PrimalVortex = nullptr;

    Up ? ptr_PrimalVortex = ptr_UpVortex : ptr_PrimalVortex = ptr_DownVortex;

    double d_result = ptr_PrimalVortex->pushAgent(value, &_CumulativeContainer);
    DrawChart(&_CumulativeContainer);

    return d_result;
}

///--
///--Функция формирования графика из куммулятивного вектора прогноза
///--
int DrawChart(CumulativeVector * _CumuCon)
{
    
	vector<float> arrY;  // Вектор х-ов
    vector<float> arrX;  // Вектор y-ов


	//--
	//--Формируем координаты для куммулятивного вектора прогноза
	//--
	for(int i = 0; i < _CumuCon->size()-1 && _CumuCon->size() > 0; ++i)
    {
		if( ((CumulativeVector)(*_CumuCon))[i]->getValue() > 0 && ((CumulativeVector)(*_CumuCon))[i]->getReliability() > 0)
		{		
			arrY.push_back((int)((CumulativeVector)(*_CumuCon))[i]->getDistance()/3);
			arrX.push_back((int)((CumulativeVector)(*_CumuCon))[i]->getReliability());
            if(((CumulativeVector)(*_CumuCon))[i]->getReliability() > d_maximal_reliability)
            {
                d_maximal_reliability = ((CumulativeVector)(*_CumuCon))[i]->getReliability();
            }
		}
    }
	

    X = new float[arrX.size()];  // Создание масива с х
    Y = new float[arrY.size()];  // Создание масива с У


    for(int j = 0; j < arrX.size(); j++)
    {
		///--
        ///--диапазона в массив Х
		///--
        X[j] = arrX[j];
    }

    for(int j = 0; j < arrY.size(); j++)
    {
		///--
        ///--диапазона в массив Y
		///--
        Y[j] = arrY[j];
    }

    _count = (int)arrX.size();
    glutDisplayFunc(DisplayChart);
    DisplayChart();

    //    glutMainLoop();

    delete [] X;
    delete [] Y;
}

///--
///--Функция перерисовки экрана
///--
void DisplayChart()
{                    

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    glColor3f(1.0, 1.0, 1.0);
	
	///--
	///--Рисование системы координат
    ///--
	glVertex3f(0, 100, 0);		
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(100, 0, 0);

    for(int i = -10; i < 20; i++)
	{
        glVertex3f(10 + i * 5, -0.5, 0);
        glVertex3f(10 + i * 5, 0.5, 0);
    }

    for(int i = -10; i < 20; i++)
	{
        glVertex3f(-0.5, 10 + i * 5 , 0);
        glVertex3f(0.5, 10 + i * 5 , 0);
    }
	
    glEnd();

    ///--
	///-- Рисование точек графика функции
	///--
	glBegin(GL_POINTS); // 
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

double getAgent(int i, int j, bool Up)
{
    double size = 0;

    //Up ? size = AgentsUpTrend[i][j].InnerAgent->mutation_percentage : size = AgentsDownTrend[i][j].InnerAgent->mutation_percentage;

    size = ptr_UpVortex->getAgent(i, j);

    return size;
}

int GetDistance()
{
    int i = 0;
    i = ptr_UpVortex->getDistance();

    return i;
}

double GetBuf()
{
    double i = 0;
    i = ptr_UpVortex->getBuf();

    return i;
}


