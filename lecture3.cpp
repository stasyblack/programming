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
    int readData();
    int addProtocol(char* ndata, int len, int i, Protocol** a);
    int sendAll(Protocol** a, int num);
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

int Protocol::addProtocol(char* ndata, int len, int i, Protocol**a)
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

int Protocol::sendAll(Protocol** a, int num)
{
    char imput[20];
    cout << "Введите название протокола: ";
    cin.getline(imput, 20);
    if (num == 0)
        num++;
    if (addProtocol(imput, strlen(imput), num, a)==-1)
        return -1;
    return 0;
}

int Protocol::readData()
{
    char ndata[20];
    char fname[40];
    int k = 100;//максимальный размер массива
    int s = 0;
    int n = 20;//максимальная длина строки
    Protocol** a;
    cout << "Введите название файла: ";
    cin.getline(fname, 40);
    fstream file;//поток из файла
    file.open(fname, ios::in);//открытие файла
    if (errorFileOpen(file) == -1)
        return -1;
    a = new Protocol* [k];
    int i = 0;
    while (!file.eof())//пока не конец файла
    {
        file>> ndata;
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
        if (addProtocol(ndata, s,i,a)==-1)
            return -1;
        i++;
    }
    file.close();//закрытие файла
    if (sendAll(a, i) == -1)
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

int Protocol::errorFileOpen(fstream& file)
{
    if (!file)//проверка на правильность открытия файла
    {
        cout << "\nОшибка открытия файла исходных данных";
        return -1;
    }
    else
        return 0;
}

int Protocol::errorInputData(fstream& file)
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
    int num;
    Protocol pr;
    if (pr.readData() == -1)
        return -1;
    return 0;

}

