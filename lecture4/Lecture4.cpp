// Lecture4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*1. Для класса Image реализовать:
class Image {
  int* img;
  int mx,int my;
public:
  Image(int tmx, int tmy):mx(tmx),my(tmy){
    img = new int[mx*my]();
  }
  vitual ~Image(); // Реализовать
  int get(int x,int y) {
    return img[y*my+x];
  } // Добавить обработку ошибок при помощи исключений - выбрасывать целочисленное исключение при выходе за границы массива
  int set(int x,int y,int color) { // Добавить обработку ошибок при помощи исключений  - выбрасывать целочисленное исключение при выходе за границы массива
    img[y*my+x]=color;
  }
  Image operator=(const Image& v)                                          // Реализовать для варианта  1
  
};
2. Реализовать перегрузку одной из операций
3. Реализовать функцию main и показать использование класса Image
*/

#include <iostream>
#include <Windows.h>

using namespace std;

class Image
{
    int* img;
    int mx;
    int my;
public:
    Image(int tmx, int tmy) :mx(tmx), my(tmy)
    {
        img = new int[mx * my](); //выделение памяти и инициализация массива нулями
    }
    virtual ~Image()
    {
        delete[] img;
    }
    int get(int x, int y);
    int set(int x, int y, int color);
    void show();
    Image& operator=(const Image& v)
    {
        int size = v.mx * v.my;
        cout << "Операция присвоения" << endl;
        for (int i = 0; i < size; i++)
        {
            img[i] = v.img[i];
            mx = v.mx;
            my = v.my;
        }
        return *this;
    }
};
int Image::set(int x, int y, int color)
{
    try
    {
        if ((x >= mx) || (y >= my) || (x < 0) || (y < 0))
            throw 204;
        if (mx * my < y * my + x)
            throw 205;
    }
    catch (int error)
    {
        cout << "Ошибка: выход за границы массива" << endl;
        exit(-1);
    }
    img[y * my + x] = color;
    return color;
}

int Image::get(int x, int y)
{
    try
    {
        if ((x >= mx) || (y >= my) || (x < 0) || (y < 0))
            throw 204;
        if (mx * my < y * my + x)
            throw 205;
    }
    catch (int error)
    {
        cout << "Ошибка: выход за границы массива" << endl;
        exit(-1);
    }
    return img[y * my + x];
}

void Image::show()
{
    int g;
    for (int i = 0; i < my; i++)
    {
        for (int j = 0; j < mx; j++)
        {
            cout << img[i * my + j] << " ";
        }
        cout << endl;
    }
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Image pict(3,2);
    pict.set(0,0,0);
    pict.set(1, 0, 0);
    pict.set(2, 0, 5);
    pict.set(0, 1, 5);
    pict.set(1, 1, 5);
    pict.set(2, 1, 0);
    pict.show();
    pict.get(2, 1);
    Image pict1(3,2);
    pict1 = pict;
    pict1.show();
}

