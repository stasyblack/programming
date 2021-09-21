// Task1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h> 
#include <string.h>
#include <stdlib.h>
#include "strutil.h"
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const int nMax = 100;
    const int mMax = 20;
    char str[100];
    char a[20];
    int pos;
    cout << "Введите фразу: ";
    cin.getline(str, nMax);
    while (cin.fail()) // если предыдущее извлечение оказалось неудачным,
    {
        cin.clear(); // то возвращаем cin в 'обычный' режим работы
        cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
        cout << "\nСлишком много символов" << endl;
        cout << "Повторите ввод ";
        cin.getline(str, nMax);
    }
    cout << "Введите фразу для поиска: ";
    cin.getline(a, mMax);
    while (cin.fail()) // если предыдущее извлечение оказалось неудачным,
    {
        cin.clear(); // то возвращаем cin в 'обычный' режим работы
        cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
        cout << "\nСлишком много символов" << endl;
        cout << "Повторите ввод ";
        cin.getline(a, mMax);
    }
    if (strlen(a) > strlen(str))
    {
        cout << "Строка для поиска больше исходной строки";
        return -1;
    }
    if ((strlen(a) == 0) || (strlen(str) == 0))
    {
        cout << "Введена пустая строка";
        return -1;
    }
    pos = strConteins(a, str);
    if (pos == -1)
    {
        cout << "Строка а отсутствует в строке str";
    }
    else
        cout << "Строка а начинатеся в строке std c позиции номер " << pos+1;
    return 0;
}
