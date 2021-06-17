#include <stdio.h>
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

// Factorial func
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


// The function that returns the number of smaller characters on right side of the string[i]
unsigned long long greater_than(char *string, unsigned long long n, unsigned long long len)
{
    unsigned long long count = 0;
    for (unsigned long long i = n + 1; i <= len; i++)
    {
        if (string[i] < string[n]) // Basic comparison
        {
            count++;
        }
    }
    return count;
}

// The function that returns the repeatitions at right side of the string[i]
/*
 * this function returns each letter's factorial of repetition count
 */
unsigned long long repetition(char *string, unsigned long long len, unsigned long long n)
{
    unsigned long long count, repetition = 1;
    char repeats[30];
    int j = 0, m = 0, flag;

    for (unsigned long long i = n; i < len; i++)
    {
        count = 0; flag = 0;

        while (j < m && flag == 0) {
            if (repeats[j] == string[i]) {    // At this part, we are checking the already counted letter for blocking the overflow
                flag = 1;                     // If we already counted the same letter, we are not going to count it again.
            }                                 // flag = 0 means the letter has not counted already.
            j++;                              // flag = 1 means we already counted it.
        }
        j = 0;
        if (flag == 0)
        {
            for (unsigned long long k = n; k < len ;k++)
            {
                if (string[i] == string[k])
                {
                    repeats[m] = string[i];    // In this section we are counting the letter if it is same with our letter.
                    m++;                       // And storing it in repeats array to check in future steps.
                    count++;
                }
            }
        }

        repetition *= fac(count);              // We are done with just one letter. So we are going to calculate its
    }                                          // factorial of repetition count.
    return repetition;
}

unsigned long long ranking(char *string)
{

    unsigned long long len = strlen(string);
    unsigned long long rank = 1, count;


    for (unsigned long long i = 0; i < len; i++)
    {
        unsigned long long temp =  1;              // For every letter we are going to run greater_than func and
                                                   // repetition func. The main formula is :
        count = greater_than(string, i, len - 1);  // ( Smaller character count * factorial of the remaining letter count )
        temp *=  count * fac(len - i - 1);          // divided by factorial of repetition count of each letter.
        temp /= repetition(string, len, i);        // We have already clarified it in project report.

                                                    // For every letters count we are increasing the rank.
        rank += temp;
    }
    return rank;
}

void lexicographic_rank (double *times, int count)
{
    char string[5000];
    unsigned long long rank;


    entering_word(string);

    clock_t begin = clock();                             // From this line algorithm is executing.

    rank = ranking(string);
    for (int i = 0; i < 999999; i++)
    {
        ranking(string);                           // For a healthier result, we are executing the program million times.
    }

    clock_t end = clock();                                      // From this line algorithm has stopped.

    printf("\n\n---------------------------------------------------------------------------------------------------\n");
    printing_word(string);
    printf("Rank of your word is %llu\n", rank);              // Printing results of the program.
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("||||||||||||||||||||||||||||||||||\n");



    double time_sp = (double)(end - begin);
    time_sp /= 1000000;                                     // For an average result we are dividing spent time
    times[count] = time_sp;                                 // by million

    printf("---------------------------------------------------------------------------------------------------\n");
    printf("This program executed for %llu indexed array on average %lf miliseconds.\n", strlen(string), time_sp);
    printf("---------------------------------------------------------------------------------------------------\n\n\n");
}

void graphic(double *times, int count)
{

    printf("Let's compare the execution times!! \n");
    printf("---------------------------------------------------------------------------------------------------\n");
    for (int i = 1; i <= count; i++)
    {
        times[i] = times[i] * 20000;        // Due to times are so low, we are going to multiply times by ten thousand
    }

    for(int i = 1; i <= count; i++)
    {
        printf("For word %d |", i);
        for(int j = 0; j < times[i]; j++)
        {
            printf("*");                     // Making a bar for times that every word has consumed.
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