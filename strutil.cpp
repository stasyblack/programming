#include <iostream>
#include <string.h>

int strConteins(char *a, char *str)
{
    int position=-1;
    int i=0, j=0;
    i = 0;
    int n = strlen(str);
    int m = strlen(a);
    while (i<n)
    {
        if (str[i]==a[0])//ѕоиск вхождени€ первой буквы строки в исходной строке
        {
            position = i;
            for (j = 1; j < m; j++)//проверка вхождени€ строки дл€ поиска в исходной строке
            {
                //i = i + j;
                i++;
                if (str[i] != a[j])
                {
                    position = -1;
                    break;
                }
               
            }
        }
        i++;
        if (position != -1)
            break;
    }
    return position;
}
