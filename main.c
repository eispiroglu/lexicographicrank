#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

void entering_word (char *string)
{
    printf("Please enter the word.\n");
    scanf("%s",string);
}
void printing_word (char *string)
{
    printf("You have entered word ` %s ` \n",string);
}

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

unsigned long long greater_than(char *string, unsigned long long n, unsigned long long len)
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

void determining_repetition(unsigned long long *repetition, char *string, unsigned long long len)
{
    char repeats[30];
    unsigned long long sum = 0;

    int j = 0, m = 0, flag;

    for (int i = 0; i < len; i++)
    {
        while (j < m && flag == 0) {
            if (repeats[j] == string[i])
            {
                flag = 1;
            }
            j++;
        }
        j = 0;

        if (flag == 0)
        {
            for (int k = i; k < len; k++)
            {
                if(string[i] == string[k])
                {
                    repetition[i]++;
                    repeats[m] = string[i];
                    m++;
                }
            }
        }
    }

    for (int i = 0; i < m; i++)
    {
        sum = 0;
        for (int k = i; k < m; k++)
        {
            if (repetition[k] > 1)
            {
                sum += repetition[k];
            }
        }
        if (sum != 0)
            repetition[i] = sum;
    }
}



unsigned long long ranking(char *string)
{

    unsigned long long len = strlen(string);
    unsigned long long rank = 1, count, rep;

    unsigned long long repetition[52];
    determining_repetition(repetition, string, len);

    for (unsigned long long i = 0; i < len; i++)
    {
        unsigned long long temp =  1;

        count = greater_than(string, i, len - 1);

        temp *=  count * fac(len - i - 1);

        if (repetition[i] != 0)
            temp /= repetition[i];

        rank += temp;
    }
    return rank;
}

void lexicographic_rank (double *times, int count)
{
    char string[5000];
    unsigned long long rank;


    entering_word(string);

    clock_t begin = clock();    // From this line algorithm is executing.

    rank = ranking(string);
    for (int i = 0; i < 999999; i++)
    {
        ranking(string);
    }

    clock_t end = clock();      // From this line algorithm has stopped.

    printf("\n\n---------------------------------------------------------------------------------------------------\n");
    printing_word(string);
    printf("Rank of your word is %llu\n", rank);
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("||||||||||||||||||||||||||||||||||\n");



    double time_sp = (double)(end - begin);
    time_sp /= 1000000;
    times[count] = time_sp;

    printf("---------------------------------------------------------------------------------------------------\n");
    printf("This program executed for %llu indexed array on average %lf miliseconds.\n", strlen(string), time_sp);
    printf("---------------------------------------------------------------------------------------------------\n\n\n");
}

graphic(double *times, int count)
{

    printf("Let us compare the execution times!! \n");
    printf("---------------------------------------------------------------------------------------------------\n");
    for (int i = 1; i <= count; i++)
    {
        times[i] = times[i] * 100000;
    }

    for(int i = 1; i <= count; i++)
    {
        printf("For word %d |", i);
        for(int j = 0; j < times[i]; j++)
        {
            printf("*");
        }
        printf("|\n");
    }

}


int main() {
    int i, count = 0;
    double times[5000];

    do {
        count++;

        printf("---------------------------------------------------------------------------------------------------\n");
        lexicographic_rank(times, count);
        printf("---------------------------------------------------------------------------------------------------\n");


        printf(" For exiting the program please enter -1 \n For resuming enter the word. \n");
        scanf("%d", &i);

    }while(i != -1);

    printf("\n\n---------------------------------------------------------------------------------------------------\n");
    graphic(times, count);
    printf("---------------------------------------------------------------------------------------------------\n");


    printf("Thanks for using the program. \n");

    return 0;
}