/*1. Разработать собственный шаблонный класс для работы с хеш таблицей. Класс должен позволять:
- Добавлять пары ключ, значение
- Позволять искать значение по ключу
- Позволять изменять значение по ключу
- Позволять удалять значение по ключу
Вариант 1
В случае возникновения коллизии (два ключа указывают на одно место в таблице) значения помещаются в односвязный список
2. Написать программу определения частоты слов в тексте. Программа должна:
- Принимать имя текстового файла для анализа в качестве параметра командной строки
- Читать файл
- Выделять слова (слово - последовательность симоволов, отделяемая разделителями пробел, табуляция, точка, запятая и т.д.)
- Инкрементировать счетчик слов, для данного слова, используя в качестве контейнера хеш таблицу, разработанную в задании 1
   - слово - ключ, число упоминаний в тексте - значение
- Выести слова и число вхождений в тексте
*/

#include <iostream>
#include <Windows.h>
#include <fstream>

using namespace std;

int errorFileOpen(fstream& file);
int errorInputData(fstream& file);

struct Str_table
{
    char value[20];
    int count=1;
    int key;
    Str_table* next;
};


class List
{
    Str_table* head;
public:
    List() :head(NULL) {};
    char* val;
    int k;
    void addElement(char *mas, int k_key);
    void showList();
    void delList();
    int delListElement(int k);
    void findListElement(int key);
    void changeElement(int key, char * word);
};

//добавление в список
void List::addElement(char *mas, int k_key)
{
    Str_table* temp, *temp1;
    temp = new Str_table;
    temp->next = NULL;
    temp->key = k_key;
    strcpy_s(temp->value, mas);
    if (head == NULL)
    {
        head = temp;
    }
    else
    {
        temp1 = head;
        if (strcmp(temp->value, temp1->value) == 0)
        {
            temp1->count++;
            delete temp;
            return;
        }
        while (temp1->next != NULL)
        {
            if (strcmp(temp->value, temp1->value)==0)
            {
                temp1->count++;
                delete temp;
                return;
            }
            temp1 = temp1->next;
        }
        temp->next = NULL;
        temp1->next = temp;
    }
    cout << "Добавление = " << temp->value <<endl;
}

template<class T>

class Hesh_table
{
    
    T** arr;
public:
    int N = 20;
    Hesh_table()
    {
        arr = new T * [N];
        for (int i = 0; i < N; i++)
        {
            arr[i] = NULL;
        }
    }
    ~Hesh_table()
    {
        delete[] arr;
    }
    int addStr(char* mas, int k_key, List& lst);
    int searchStr();
    int changeStr();
    int delStr();
    int countKey(char *mas);
    void showTable();
    void delAllList();
    int hKey(int key);
};


//подсчет ключа
template <typename T>
int Hesh_table <T>::countKey(char *mas)
{
    int s = strlen(mas);
    int sum = 0;
    for (int i = 0; i < s; i++)
    {
        sum = sum + int(mas[i]);
    }
    return sum;
}

template <typename T>
int Hesh_table<T>::hKey(int key)
{
    return key % N;
}


//добавление строки
template <typename T>
int Hesh_table <T>::addStr(char *mas, int key, List &lst)
{
    if (arr[hKey(key)] == NULL)
    {
        arr[hKey(key)] = new List;
    }
    arr[hKey(key)]->addElement(mas, key);
    return 0;
}


//поиск строки
template <typename T>
int Hesh_table <T>::searchStr()
{
    int key;
    cout << "Введите значение ключа: ";
    cin >> key;
    if (key < 0)
    {
        cout << "Ошибка: такого ключа не существует"<<endl;
        return -1;
    }
    if (arr[hKey(key)] == NULL)
    {
        cout << "Значения с таким ключем не существует" << endl;
        return -1;
    }
    arr[hKey(key)]->findListElement(key);
    return 0;
}

//изменение значения
template <typename T>
int Hesh_table <T>::changeStr()
{
    int key;
    char word[30];
    cout << "Введите значение ключа для изменения значения: ";
    cin >> key;
    if (key < 0)
    {
        cout << "Ошибка: такого ключа не существует" << endl;
        return -1;
    }
    if (arr[hKey(key)] == NULL)
    {
        cout << "Значения с таким ключем не существует" << endl;
        return -1;
    }
    cout << "Введите новое значение: ";
    cin >> word;
    arr[hKey(key)]->changeElement(key,word);
    cout << "Таблица с измененным значением" << endl;
    showTable();
    return 0;
}


//удаление строки
template <typename T>
int Hesh_table <T>::delStr()
{
    int key;
    cout << "Введите значение ключа для удаления: ";
    cin >> key;
    if (key < 0)
    {
        cout << "Ошибка: такого ключа не существует" << endl;
        return -1;
    }
    if (arr[hKey(key)] == NULL)
    {
        cout << "Значения с таким ключем не существует" << endl;
        return -1;
    }
    int a = arr[hKey(key)]->delListElement(key);
    if (a == -1)
        return -1;
    if (a == 2)
    {
        arr[hKey(key)] = NULL;
    }
    showTable();
    return 0;
}

void List::changeElement(int key, char* word)
{
    Str_table* temp;
    temp = head;// указатель на начало списка
    bool flag = true;
    while (temp != NULL) //пока не дошли до конца списка
    {
        if (temp->key == key)
        {
            strcpy_s(temp->value, word);
            flag = false;
        }
        temp = temp->next; // указываем на следующий адрес из списка
    }
    if (flag)
        cout << "Элемента с таким кодом не существует";
}


//поиск элемента списка
void List::findListElement(int key)
{
    Str_table* temp;
    temp = head;// указатель на начало списка
    bool flag = true;
    while (temp != NULL) //пока не дошли до конца списка
    {
        if (temp->key == key)
        {
            cout << temp->value;
            cout << "  Ключ: " << temp->key;
            cout << "    Количество элементов " << temp->count << endl;
            flag = false;
        }
        temp = temp->next; // указываем на следующий адрес из списка
    }
    if (flag)
        cout << "Элемента с таким кодом не существует"<<endl;
}


//вывод списка на экран
void List::showList()
{
    Str_table* temp;
    temp = head;// указатель на начало списка
    while (temp != NULL) //пока не дошли до конца списка
    {
        //вывод элементов структуры
        cout << temp->value;
        cout << "  Ключ: " << temp->key;
        cout << "    Количество элементов " << temp->count << endl;
        temp = temp->next; // указываем на следующий адрес из списка
    }
    cout << endl;
}

//вывод таблицы на экран
template<typename T>
void Hesh_table<T>::showTable()
{
    cout << "Вывод таблицы" << endl;
    for (int i = 0; i < N; i++)
    {
        if (arr[i] != NULL)
        {
            cout << i << " \n";
            arr[i]->showList();
        }
    }
}


//удаление элемента списка
int List::delListElement(int key)
{  
    Str_table* temp, *temp1; 
    temp = head;// указатель на начало списка
    temp1 = temp;
    if (temp->next == NULL)
    {
        if (key == temp->key)
        {
            delete temp;
            head = NULL;
            cout << "Удаление единственного элемента" << endl;
            return 2;
        }
        else
        {
            cout << "Такого элемента для удаления нет";
            return -1;
        }
    }
    else
    {
        temp1 = temp->next;
        while (temp1 != NULL) //пока не дошли до конца списка
        {
            if (temp==head)
                if (temp->key == key)
                {
                    head = temp1;
                    delete temp;
                    cout << "Удаление первого элемента" << endl;
                    return 0;
                }
            if (temp1->key == key)
            {
                temp->next = temp1->next;
                delete temp1;
                cout << "Удаление элемента в середине" << endl;
                return 0;
            }

            temp1 = temp1->next;
            temp = temp->next;
        }

    }
}


//удаление списка
void List::delList()
{
    Str_table* temp;
    
    while (head != NULL)                //Пока по адресу есть хоть что-то
    {

        temp = head->next;     //Сразу запоминаем указатель на адрес следующего элемента структуры
        delete head;                    //Освобождаем память по месту начала списка
        head = temp;                    //Меняем адрес начала списка
    }
}


//удаление всех списков
template<typename T>
void Hesh_table<T>::delAllList()
{
    for (int i = 0; i < N; i++) 
    {
        if (arr[i] != NULL)
        {
            arr[i]->delList();
        }
    }
}

//чтение файла и вызов функций
template<typename T>
int readFromFile(fstream& file)//чтение данных из файла
{
    char ndata[20];
    List lst;
    Str_table n_str;
    Hesh_table <List> ht;
    int k_key;
    while (!file.eof())//пока не конец файла
    {
        file >> ndata;
        if (errorInputData(file) == -1)
        {
            file.close();
            return -1;
        }
        k_key = ht.countKey(ndata);
        ht.addStr(ndata, k_key, lst);
    }
    ht.showTable();
    if (ht.searchStr() == -1)
        return -1;
    if (ht.delStr() == -1)
        return -1;
    if (ht.changeStr()==-1)
        return -1;
    ht.delAllList();
    return 0;
}


//чтение файла
template<typename T>
int readData()
{
    char fname[40];
    cout << "Введите название файла: ";
    cin.getline(fname, 40);
    fstream file;//поток из файла
    file.open(fname, ios::in);//открытие файла
    if (errorFileOpen(file) == -1)
        return -1;
    if (readFromFile<int>(file) == -1)
        return -1;
    file.close();//закрытие файла
    return 0;
}


//проверка на правильность открытия файла
int errorFileOpen(fstream& file)
{
    if (!file)//проверка на правильность открытия файла
    {
        cout << "\nОшибка открытия файла исходных данных";
        return -1;
    }
    else
        return 0;
}

//проверка на пустой файл
int errorInputData(fstream& file)
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
    if (readData<int>() == -1)
        return -1;
}


