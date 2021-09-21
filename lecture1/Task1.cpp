// Task1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h> 
#include <string.h>
#include <stdlib.h>
using namespace std;

void findVarNoumber(char surname[], int kol)
{
    int count=strlen(surname);
    int var, sum;
    sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum = sum + (int)surname[i];
    }
    var = sum % kol + 1;
    cout << "Variant: " << var;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char surname[20];
    int kol;
    cout << "Input surname: ";
    cin.getline(surname, 20);
    while (cin.fail()) // если предыдущее извлечение оказалось неудачным,
    {
        cin.clear(); // то возвращаем cin в 'обычный' режим работы
        cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
        cout << "\nToo many symbols" << endl;
        cout << "Re-enter ";
        cin.getline(surname, 20);
    }
    cout << "\nInput number of variants: ";
    cin >> kol;
    findVarNoumber(surname, kol);
    return 0;
}
