// lecture8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*1. Разрабоать программe, которая включает два потока один поток моделирует полет шарика, второй отображает
в текстовом виде полжение шарика на экране с заданной частотой.
Информация о траектории полета (координаты и метка времени) должны заносится в std::vector
Масса, начальная скорость и положение шарика должны задаваться в качестве параметров командной строки.
Вариант 1
Моделируем полет брошенного в вертикально вверх со скоростью v шарика массой m. При соударении с землей шарик прилипает к поверхности.
Программа должна иметь функции:
- Вычисления положения (h) и параметров движения шарика (v, a) через заданный промежуток времени
- Позволять записывать параметы движения шарика и метку времении в односвязный спискок
- Печатать на экран информацию о траектории движения шарика за заданный промежуток времени
*/

#include <iostream>
#include <Windows.h>
#include <thread>
#include <vector>
#include <sstream>
#include <chrono>
#include <mutex>

using namespace std;

const double g = 9.8;

struct Ball
{
	double h=0;
	double t=0;
	double v=0;
	double a=g;
};

vector <Ball> ballVector;



Ball flight(double v0, double h0, double t)
{
	Ball b;
	b.h = h0 + v0 * t - g * t * t / 2;
	b.v = v0 - g * t;
	b.a = -g;
	return b;
}

void print()
{
	this_thread::sleep_for(chrono::milliseconds(10));//задержка выполнения
	//cout << "print" << this_thread::get_id()<<endl;   печать идентификатора текущего потока
	cout << "  t       h      v      a"<<endl;
	for (int i = 0; i < ballVector.size(); i++)
	{
		cout << ballVector[i].t<<"   "<< ballVector[i].h << "   "<<ballVector[i].v << "   "<< ballVector[i].a << "   ";
		cout << endl;
	}
}

mutex mtx;//объявление объекта класса motex
void modelFligth( double m, double v0, double h0)
{
	mtx.lock();//блокировка вызывающего потока
	double dt = 0.1;
	double t = 0;
	Ball b;
	cout << "m = " << m << "   v0 = " << v0 << "   h0 = " << h0 << endl;
	b = flight(v0, h0, t);
	while (b.h >= 0)
	{
		
		b = flight(v0, h0, t);
		if (b.h > 0)
			ballVector.push_back({ b.h,t,b.v,b.a });
		t = t + dt;
	}
	mtx.unlock();//освобождение прав владения объекта
}

int main(int argc, char *argv[])//задание аргументов из командной строки (три аргумента)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	double m, h0, v0;
	if (argc != 4)
	{
		cout << "Ошибка количества аргументов";
		return -1;
	}
	stringstream convertm{ argv[1] };//считывание первого аргумента из командной строки и его конвертация 
	if (!(convertm >> m))
	{
		cout << "Ошибка исходных данных: m";
		return -1;
	}
	stringstream convertv0{ argv[2] };
	if (!(convertv0 >> v0))
	{
		cout << "Ошибка исходных данных: v0";
		return -1;
	}
	stringstream converth0{ argv[3] };
	if (!(converth0 >> h0))
	{
		cout << "Ошибка исходных данных: h0";
		return -1;
	}
	thread th(modelFligth, m, v0, h0);//объявление потока
	thread th1(print);
	th.join();
	th1.join();
	ballVector.clear();
	return 0;
}
