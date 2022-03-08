//Napisz program, który:
// 1) pozwala użytkownikowi na wprowadzenie dowolnej liczby ciągów znakowych (zdań)

// 2) odwraca kolejność wyrazów w każdym z ciągów (od ostatniego do pierwszego wyrazu)

// 3) wyprowadza przetworzone ciągi w kolejności od najkrótszego do najdłuższego z informacją
// jako który z kolei był początkowo wprowadzony, liczby wyrazów z których jest złożony
// oraz ile razy każdy znak wystąpił w danym ciągu

// 4) umożliwia użytkownikowi zmianę kolejności wyświetlania ciągów (tj. od najdłuższego do najkrótszego)





#include <stdio.h>      //предоставляет: fgetc, stdin, printf, puts
#include <stdlib.h>     //sizeof, free, realloc, malloc
#include <string.h>     //strncpy


char* getString (void);
void reverseString(char *str);
int is_space(char c);
int is_not_space(char c);
int count_start_if(char* str, int (*pred)(char));
int countWords(char* str);
int countSymbols(char* str)    ;
int myCompare(const char* a, const char* b);
int myCompare_reverse(const char* a, const char* b);
void stringSort(char* str[], int arrSize);
void stringSort_reverse(char* str[], int arrSize);



int main (void)
{

    int numOfSrt = 100; //the number of strings user can type xD
    int i;

    char * string[numOfSrt];   //массив указателей на будущие строки


    for(i=0; ;i++)
    {
        printf("\nInput string #%d: (or enter an empty string to quit)\n", i+1);

        if ((string[i] = getString()) == NULL)
            break;       // ввод символов с клавиатуры


        printf("\nOutput string:\n");
        puts(string[i]);       // выводим строку на экран
        printf("\nReversed string:\n");
        reverseString(string[i]);
        puts(string[i]);
        printf("\nNumber of words: ");
        printf("%d", countWords(string[i]));
        countSymbols(string[i]);

    }

    printf("Sort order: from Big to Small. Type (B/S): ");
    char answ;
    scanf("%c",&answ);

    if(answ == 'B' || answ == 'B')
        stringSort_reverse(string, i);
    else
        stringSort(string, i);

    for(int j=0; j<i; j++)
    {
        puts(string[j]);
    }



    return 0;
}



char* getString (void)
{
    char* buffer = NULL;                    //character buffer
    unsigned int capacity = 0;              //buffer size
    unsigned int n = 0;                     //how many characters are in the buffer
    int bitofchar = sizeof(char);           //how many bits are in one char
    int MAX_LEN = 2048;                     //1 line max 4 MB (MAX_LEN*2)
    char c;                                  //write symbols here

    // получаем символы
    while ((c = fgetc(stdin)) != '\n' && c != EOF)
    {

        if (n + 1 > capacity)               //check buffer size
        {
            if (!capacity) capacity = 32;   //default 32 characters
            else if (capacity <= MAX_LEN) capacity *= 2;
            else                            //buffer overflow threat
            {
                free(buffer);
                return NULL;
            }
            // change buffer size in memory
            char* temp = (char*) realloc(buffer, capacity * bitofchar);
            if (temp == NULL)
            {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }
        // put character into buffer
        buffer[n++] = c;
    }
    if (n == 0 && c == '\n') return NULL;        //if empty string, return NULL

    // minimizing the buffer size
    char* minimal = (char*) malloc((n + 1) * bitofchar);
    strncpy(minimal, buffer, n);
    free(buffer);                               //free memory
    minimal[n] = '\0';                          //add the end of the line
    return minimal;                             //return the resulting string
}

void reverseString(char *str)
{
    // declare variable
    int i, len, temp;
    len = strlen(str); // use strlen() to get the length of str string

    // use for loop to iterate the string
    for (i = 0; i < len/2; i++)
    {
        // temp variable use to temporary hold the string
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int is_space(char c)  //auxiliary
{
    return c == ' ';
}

int is_not_space(char c)  //auxiliary
{
    return 0 == is_space(c);
}

int count_start_if(char* str, int (*pred)(char))  //auxiliary
{
    int count = 0;

    while (*str != 0)
    {
        if (pred(*str))
        {
            count++;
            str++;
        }
        else
            break;
    }
    return count;
}

int countWords(char* str)
{
    int length = strlen(str);

    int count = 0;
    int i = 0;
    while (1)
    {
        int spaces_count = count_start_if(&str[i], is_space);
        i += spaces_count;
        if (i >= length)
        {
            break;
        }

        int word_length = count_start_if(&str[i], is_not_space);
        if (word_length > 0)
        {
            count++;
        }

        i += word_length;
        if (i >= length)
        {
            break;
        }
    }
    return count;
}

int countSymbols(char* str)
{
    int s[256] = { 0 };
    char c;

    while (c = *str++)
    {
        ++s[c+128];
    }

    for (c = -128; c < 127; ++c)
    {
        if (s[c+128] )
        {
            printf("\nSymbol %c was seen %d times", c, s[c+128]);
        }
    }
    printf("\n\n\n");
}

int myCompare(const char* a, const char* b)
{
    return *(const char**)b - *(const char**)a;
}

int myCompare_reverse(const char* a, const char* b)
{
    return *(const char**)a - *(const char**)b;
}

void stringSort(char* str[], int arrSize)
{
    qsort(str, arrSize, sizeof( char*), myCompare);
}

void stringSort_reverse(char* str[], int arrSize)
{
    qsort(str, arrSize, sizeof( char*), myCompare_reverse);
}

