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
        if (str[i]==a[0])//Ïîèñê âõîæäåíèÿ ïåðâîé áóêâû ñòðîêè â èñõîäíîé ñòðîêå
        {
            position = i;
            for (j = 1; j < m; j++)//ïðîâåðêà âõîæäåíèÿ ñòðîêè äëÿ ïîèñêà â èñõîäíîé ñòðîêå
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
