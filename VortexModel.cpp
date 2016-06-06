// TestDLL.cpp : Defines the exported functions for the DLL application.
//
#include "VortexModel.h"
//#include <root/TRandom.h>
using namespace std;

Vortex * ptr_UpVortex;
Vortex * ptr_DownVortex;

int 	    ArraySize 	= 600;	// Размер массива
int 		counter 	= 1;	// Счетчик
int 		_count 		= 0;    // Размер масива У,Х
double* 	X;           		// масив для хранение х-ов
double* 	Y;           		// масив для хранения у-ов

int			DisplayX 	= 1600;
int 		DisplayY	= 800;

double      d_maximal_reliability = 0; // максимальная надежность


CumulativeVector _CumulativeContainer;

//--
//--Инициализация вихря
//--
void InitializeVortex(
        int 	ArrSize 		 , 		//
        int 	Generation 		 , 		// Поколение
        double 	Step 			 , 		// Шаг в процентах между полюсами
        int 	MaxSizeOfRing 	 , 		// Максимальный размер кольца
        double 	EasingRatio 	 , 	    // Коэффициент ослабления
        double 	strengthen_step  		// Шаг укрепления связи
                     )
{
    if(ArrSize > 0)
    {
        ArraySize = ArrSize;
    }

    ptr_UpVortex 	= new Vortex(ArraySize, Generation, Step, MaxSizeOfRing, EasingRatio,  strengthen_step);
    //ptr_DownVortex 	= new Vortex(ArraySize, 1);

	//--
    //-- Стандартное создание окна в OpenGl
    //--
	int argc = 0;
    char ** argv = nullptr;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(DisplayX, DisplayY);
    glutInitWindowPosition(20, 810);
    glutCreateWindow("vortex model");
    glClearColor(0.0, 0.0, 0.0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 100.5, -2, ArraySize/2 + 0.5, -100, 100);

}

//--
//--Заводит значение в вихрь
//--
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

//--
//--Функция формирования графика из куммулятивного вектора прогноза
//--
int DrawChart(CumulativeVector * _CumuCon)
{
    
	vector<double> arrY;  // Вектор х-ов
    vector<double> arrX;  // Вектор y-ов


	//--
	//--Формируем координаты для куммулятивного вектора прогноза
	//--
	for(int i = 0; i < _CumuCon->size()-1 && _CumuCon->size() > 0; ++i)
    {
		if( ((CumulativeVector)(*_CumuCon))[i]->getValue() > 0	&&	((CumulativeVector)(*_CumuCon))[i]->getReliability() > 0)
		{		
			
			arrY.push_back(((CumulativeVector)(*_CumuCon))[i]->getDistance() );				// Формируем уровни треугольной матрицы на графике
			arrX.push_back(((CumulativeVector)(*_CumuCon))[i]->getReliability()  );	// Формируем уровни надежности на графике
            
			//--
			//--Получаем максимальную надежность за проход
			//--
			if(((CumulativeVector)(*_CumuCon))[i]->getDistance() > d_maximal_reliability)
            {
                d_maximal_reliability = ((CumulativeVector)(*_CumuCon))[i]->getDistance();
            }
		}
    }
	

    X = new double[arrX.size()];  // Создание масива с х
    Y = new double[arrY.size()];  // Создание масива с У


    for(int j = 0; j < arrX.size(); j++)
    {
		//--
        //--Запись диапазона в массив Х
		//--
        X[j] = arrX[j];
    }

    for(int j = 0; j < arrY.size(); j++)
    {
		//--
        //--Запрсь диапазона в массив Y
		//--
        Y[j] = arrY[j];
    }

    _count = (int)arrX.size();
    glutDisplayFunc(DisplayChart);
	
	//--
	//--Отрисовываем график на экране
	//--
    DisplayChart();

    
	//    glutMainLoop();
	
    delete [] X;
    delete [] Y;

    return 0;
}

//--
//--Функция перерисовки экрана
//--
void DisplayChart()
{                    

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);

    glColor3f(1.0, 1.0, 1.0);
	
	//--
	//--Рисование системы координат
    //--
	glVertex3f(0, ArraySize, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(100, 0, 0);

//    glVertex3f(50, 100, 0);
//    glVertex3f(50, 0, 0);



    for(int i = -10; i < 20; i++)
	{
        glVertex3f(10 + i * 5, -0.5, 0);
        glVertex3f(10 + i * 5, 0.5, 0);


    }

    for(int i = -10; i < ArraySize/5; i++)
	{
        glVertex3f(-0.5, 10 + i * 5 , 0);
        glVertex3f(0.5, 10 + i * 5 , 0);
    }
	
    glEnd();


    glLineWidth(0.01);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LINE_STIPPLE); 	// разрешаем рисовать
								// прерывистую линию
    glLineStipple(2,6);    		// устанавливаем маску
    // пояснения см. ниже
    glBegin(GL_LINE_LOOP);
    glColor3d(0,0,1);
        glVertex3f(50, 300, 0);
        glVertex3f(50, 0, 0);
    glEnd();

    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_LINE_STIPPLE);

    //--
	//-- Рисование точек графика функции
	//--
	glBegin(GL_POINTS); // 
    //glColor3f(0.13, 0.67, 0.82);
    glColor3f(1.0, 1.0, 1.0);
    
	float y;
    
	//--
	//--Отрисовываем куммулятивный вектор
	//--
	for(int i = 0; i < _count; i++)
    {
        if(X[i] > 50)
        {
            glColor3f(0.0, 1.0, 0.0);
        }
        else
        {
            glColor3f(1.0, 0.0, 0.0);
        }

        glVertex3f(X[i], Y[i], 0);
    }
    
	glEnd();



    glColor3f(1,1,0);
	
	//--
	//--Отрисовываем подпись графика
	//--
    string text = "dynamic plot";				// текст подписи

    glRasterPos2f(100 - 6, ArraySize/2 - 3 );	// положение текста

	//--
	//-- Отрисовка букв подписи
	//--
    for (int it=0; it<text.size(); it++)
        glutBitmapCharacter((int*)GLUT_BITMAP_8_BY_13, (int)text[it]);


	//--
	//--Отрисовываем циферное обозначение координат X-ов
	//--
    for(int i = 1; i < 20; i++)
    {
        string text = to_string(i*5);
		
        glRasterPos2f(i * 5, 0.5);

        for (int it=0; it<text.size(); it++)
            glutBitmapCharacter((int*)GLUT_BITMAP_8_BY_13, (int)text[it]);

    }

	//--
	//--Отрисовываем циферное обозначение координат Y-ов
	//--
    for(int i = 1; i < ArraySize/5; i++)
    {
        string text = to_string(i*10);

        glRasterPos2f( 0.5, i * 5);

        for (int it=0; it<text.size(); it++)
            glutBitmapCharacter((int*)GLUT_BITMAP_8_BY_13, (int)text[it]);
    }

	//--
	//--Выводим на экран
	//--
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


