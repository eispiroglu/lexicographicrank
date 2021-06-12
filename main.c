#include <stdio.h>
#include <stdlib.h>
#include "string.h"


unsigned long long fac(unsigned long long n)
{
    if (n == 0)
    {
        return 1;
    }

    else
    {
        return n * fac(n-1);
    }
}

unsigned long long greater_than(char string[5000], unsigned long long n, unsigned long long len)
{
    unsigned long long count = 0;
    for (unsigned long long i = n + 1; i <= len; i++)
    {
        if (string[i] < string[n])
        {
            count++;
        }
    }
    return count;
}

unsigned long long repetition(char *string, unsigned long long len, unsigned long long n)
{
    unsigned long long count, repetition = 1;
    char repeats[30];
    int j = 0, m = 0, flag;

    for (unsigned long long i = n; i < len; i++)
    {
        count = 0; flag = 0;

        while (j < m && flag == 0) {
            if (repeats[j] == string[i]) {
                flag = 1;
            }
            j++;
        }
        j = 0;
        if (flag == 0) {
            for (unsigned long long k = n; k < len ;k++)
            {
                if (string[i] == string[k])
                {
                    repeats[m] = string[i];
                    m++;
                    count++;
                }
            }
        }

        repetition *= fac(count);
    }

    return repetition;

}

unsigned long long ranking(char string[5000])
{
    unsigned long long len = strlen(string);
    unsigned long long rank = 1, count, rep;


    for (unsigned long long i = 0; i < len; i++)
    {
        unsigned long long temp =  1;

        count = greater_than(string, i, len - 1);
        temp *=  count * fac(len - i - 1);
        rep = repetition(string, len, i);
        temp /= rep;

        rank += temp;
    }
    return rank;
}



int main()
{
    char string[5000];

    printf("Please enter the string. \n");
    scanf("%s", string);
    printf("Rank of your word is %llu", ranking(string));
}