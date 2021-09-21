/*Задание лекция 3 - Software.
Написать программу, которая:
- умеет читать тектосвый файл, который может быть указан ей в качестве аргумента коммандной строки и содержит названия протоколов (одно на строке)
Пример файла: 
BinaryProtocol 
HexProtocol 
HexProtocol
- Реализует классы Protocol, BinaryProtocol, HexProtocol
- Классы BinaryProtocol, HexProtocol являются наследниками Protocol
- Класс Protocol определяет виртуальный метод void send(char* buf, int len), который ничего не делает
- Классы BinaryProtocol, HexProtocol переопределяют виртуальный метод void send(char* buf, int len)
  - void BinaryProtocol::send(char* buf, int len) - печатает на экран содержимое строки buf в виде бинарного кода (т.е. при помощи "0101 0101 0100 1000")
  - void HexProtocol::send(char* buf, int len)    - печатает на экран содержимое строки buf в виде шестнатеричного кода (т.е. так "0xff 0xff")
Вариант 3.
- Создать динамический массив указателей (размер равен числу протоколов в файле) на класс Animal и функцию 
для добавления туда классов, соответствующих протоколам, считанным из файла
- Написать функцию для печати отправки введенного с клавиатуры сообщения при помощи всех протоколов void sendAll(Protocol *p, int number_of_prorocols)
*/

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <bitset>


using namespace std;
const char HexData[20] = "HexProtocol\0";
const char BinaryData[20] = "BinaryProtocol\0";

class Protocol
{
public:
    
    virtual void send(char* buf, int len);
};

class ProtocolList
{
public:
    Protocol** a;
    int readData();
    int readFromFile(fstream& file, int i);
    int addProtocol(char* ndata, int len, int i);
    int sendAll(int num);
    int errorFileOpen(fstream& file);
    int errorInputData(fstream& file);
};

class HexProtocol :public Protocol
{
public:
    virtual void send(char* buf, int len);
};

class BinaryProtocol :public Protocol
{
public:
    virtual void send(char* buf, int len);
};

int ProtocolList::addProtocol(char* ndata, int len, int i)
{
    if (strstr(ndata, HexData) != NULL)
    {
        a[i] = new HexProtocol[len];
        a[i]->send(ndata, len);
    }
    else
        if (strstr(ndata, BinaryData) != NULL)
        {
            a[i] = new BinaryProtocol[len];
            a[i]->send(ndata, len);
        }
        else
        {
            cout << "Неправильное название протокола" << endl;
            return - 1;
        }
    return 0;
}

int ProtocolList::sendAll(int num)
{
    char imput[20];
    cout << "Введите название протокола: ";
    cin.getline(imput, 20);
    if (num == 0)
        num++;
    if (addProtocol(imput, strlen(imput), num)==-1)
        return -1;
    return 0;
}

int ProtocolList::readFromFile(fstream& file, int i)//чтение данных из файла
{
    char ndata[20];
    int s = 0;
    int n = 20;//максимальная длина строки
    while (!file.eof())//пока не конец файла
    {
        file >> ndata;
        if (file.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            file.clear(); // то возвращаем cin в 'обычный' режим работы
            file.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
            cout << "Ошибка: могу быть введены только цифры." << endl;
            file.close();
            return -1;
        }
        s = strlen(ndata);
        if (s > n)
        {
            cout << "Слишком длинное название протокола";
            for (int j = 0; j < i; j++)
                delete[]a[j];
            delete[] a;
            return -1;
        }
        if (errorInputData(file) == -1)
        {
            file.close();
            for (int j = 0; j < i; j++)
                delete[]a[j];
            delete[] a;
            return -1;
        }
        if (addProtocol(ndata, s, i) == -1)
            return -1;
        i++;
    }
    return 0;
}

int ProtocolList::readData()
{
    char fname[40];
    int k = 100;//максимальный размер массива
    cout << "Введите название файла: ";
    cin.getline(fname, 40);
    fstream file;//поток из файла
    file.open(fname, ios::in);//открытие файла
    if (errorFileOpen(file) == -1)
        return -1;
    a = new Protocol* [k];
    int i = 0;
    if (readFromFile(file, i) == -1)
        return -1;
    file.close();//закрытие файла
    if (sendAll(i) == -1)
        return -1;
    for (int j = 0; j < i; j++)
        delete[]a[j];
    delete[] a;
    return i;
}


void Protocol::send(char* buf, int len)
{
    cout << "Protocol" << endl;
}

void HexProtocol::send(char *buf,int len)
{
    cout << "HexProtocol:  "<<endl;
    for (int i = 0; i < len; i++)
    {
        cout <<"0x"<< hex << uppercase << (int)buf[i] << " ";
    }
    cout << endl;
}

void BinaryProtocol::send(char* buf, int len)
{
    cout << "BinaryProtocol:   " << endl;
    for (int i = 0; i < len; i++)
    {
        bitset<8> x(buf[i]);
        cout << x << ' ';
    }
    cout << endl;
}

int ProtocolList::errorFileOpen(fstream& file)
{
    if (!file)//проверка на правильность открытия файла
    {
        cout << "\nОшибка открытия файла исходных данных";
        return -1;
    }
    else
        return 0;
}

int ProtocolList::errorInputData(fstream& file)
{
    if (file.fail())
    {
        cout << "\nОшибка данных в файле";
        return -1;
    }
    return 0;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ProtocolList pr;
    if (pr.readData() == -1)
        return -1;
    return 0;

}

