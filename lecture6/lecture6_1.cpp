// lecture6_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
using namespace std;

class Arr
{
private:
static int i;//описание счетчика как статической переменной класса
public:
    Arr()
    {
        cout << i<<" ";
        i++;
    }
};

int Arr::i = 1;//Задание начального значения для счетчика

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int N;
    cout << "Введите количество элементов: ";
    cin >> N;
    Arr *a;
    a = new Arr[N];
    delete[] a;
}

