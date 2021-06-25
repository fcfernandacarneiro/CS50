#include <stdio.h>
#include <cs50.h>

//Prompt for start population size

int main (void)
{
    int start;
    do
     {
        start = get_int("Population start size:");
      }
    while (start < 9);

//Prompt for end population size

    int end;
    do
    {
        end = get_int("Population end size:");
    }
    while (end < start);


//Calculation years required
    int years = 0;
    while (start<end)
    {
     start = start + start/3 - start/4;
     years++;
    }

//Print numbers of years required

    printf("Years: %i\n", years);

}
