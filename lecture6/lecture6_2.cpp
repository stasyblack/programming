//Задание к лекции 6.2 Реализовать свой шаблонный класс для умного указателя и программу для демонстрации, что он работает.

#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
using namespace std;

class Book
{
    int cost;
    char *name;
    char *author;
public:
    Book(char* b_name, char* b_author,int b_cost)
    {   
        name = new char[strlen(b_name)+1];
        author = new char[strlen(b_author)+1];
        memcpy(name, b_name, strlen(b_name) + 1);//копируем строку name и сохраняем в b_name
        memcpy(author, b_author, strlen(b_author) + 1);
        cost = b_cost;
    }
    ~Book()
    {
        
        delete [] name;
        delete [] author;
        
    }
    void show()
    {
        cout << "Автор: " << author<<endl;
        cout << "Название книги: " << name << endl;
        cout << "Цена: " << cost << endl;
    }
};

template<typename T>

class My_pointer
{
private:
    T* ptr;

public:
    My_pointer(T* ptr)
    {
        this->ptr = ptr;
    }

    ~My_pointer()
    {
        delete ptr;
    }

    T& operator*()
    {
        return *ptr;
    }

    T* operator->()
    {
        return ptr;
    }
};


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);  
    int b_cost = 250;
    char b_author[20] = "Пушкин";
    char b_name[30] = "Капитанская дочка";
    My_pointer<Book> n(new Book(b_author, b_name, b_cost));
    n->show();
    return 0;
}
