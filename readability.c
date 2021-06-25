#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

float count_letters(string inputtext);
float count_words(string inputtext);
float count_sentences(string inputtext);
double index(string inputtext);


int main (void)
{
//GETTING USER INPUT
    string text = get_string("Text:");
//CALCULATING COLEMAN LIAU INDEX
    float nletter = count_letters(text);
    float nword = count_words(text);
    float nsentence = count_sentences(text);
    int CLi = index(text);
//PRINTING TO USER
    if (CLi <= 16)
    {
        printf("Index: %d\n", CLi);
    }
    else
    {
        printf("Index: 16+\n");
    }
}


//FUNCTION -COMPUTING NUMBER OF LETTERS
float count_letters(string inputtext)
{
    int nletter = 0;

    for(int i = 0, n = strlen(inputtext); i <= n; i++)
    {
        if(inputtext[i]>=60 && inputtext[i]<=90)
        {
          nletter = nletter + 1;

        }
        else if (inputtext[i] >= 97 && inputtext[i] <= 122)
        {
            nletter = nletter + 1;
        }
        else
        {

        }
    }
    return nletter;

}

//FUNCTION -COMPUTING NUMBER OF WORDS
float count_words(string inputtext)
{
    int nwords = 0;

    for (int j = 0; inputtext[j] != '\0'; j++)
    {
        if (inputtext[j] == 32)
        {
            nwords = nwords + 1;
        }
        else
        {

        }
    }
    return nwords + 1;
}

float count_sentences(string inputtext)
{
    int nsentences = 0;
    for (int k = 0; inputtext[k] != '\0'; k++)
    {
        if (inputtext[k] == 33)
        {
            nsentences = nsentences + 1;
        }
        if (inputtext[k] == 46)
        {
            nsentences = nsentences + 1;
        }
        if(inputtext[k] == 63)
        {
            nsentences = nsentences + 1;
        }
        else
        {

        }
    }
    return nsentences;
}

//FUNCTION - CALCULATING Coleman-Liau index

double index(string inputtext)
{
    double L = count_letters(inputtext) * 100 / count_words(inputtext);
    double S = count_sentences(inputtext) * 100 / count_words(inputtext);

    double index = round(0.0588 * L - 0.296 * S - 15.8);
    return index;
}

