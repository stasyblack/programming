// lecture2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h> 
#include <string.h>
#include <stdlib.h>
using namespace std;

int const MaxSize = 10;
class FooString
{
private:
    char* buf;
public:
    FooString();
    ~FooString();
    void show();
    int length();
    int testInput();
    void testData();
};
 
FooString::FooString()
{
    buf = new char[MaxSize];
    testData();
}

FooString::~FooString()
{
    delete[]buf;
}

void FooString::testData()//Функция ввода тестовой строки
{
    cout << "Введите строку: ";
    cin.getline(buf, MaxSize);
}

int FooString::length()//Функция подсчета количества символов в строке
{
    int i=0;
    while (true)
    {
        if (buf[i] == '\0')
            break;
        else
            i++;
    }
    i++;
    return i;
}

void FooString::show()//вывод строки на экран
{
    int l = length();
    cout << "Размер массива: " << l << endl;
    for (int i = 0; i < l; i++)
        cout << buf[i];
}



int FooString::testInput() //проверка правильности ввода данных
{
    if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
    {
        cin.clear(); // то возвращаем cin в 'обычный' режим работы
        cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
        cout << "Ошибка ввода данных." << endl;
        return -1;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    FooString mas;
    if (mas.testInput() == -1)
            return -1;
    mas.show();
}
