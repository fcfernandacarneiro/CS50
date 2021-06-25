#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main (int argc, string argv[])
{
    if (argc == 2)
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isdigit(argv[1][i]))
            {
                string plain = get_string("Plaintext: ");
                int k = atoi (argv [1]);
                string ciphertext = plain;
                for(int j = 0, m = strlen(plain); j < m; j++)
                    {
                        if (isalpha(plain[j]))
                        {
                           if (islower(plain[j]))
                           {
                                ciphertext[j] = (plain[j] - 97 + k) % 26 + 97;
                           }
                           else
                           {
                                ciphertext[j] = (plain[j] - 65 + k) % 26 + 65;
                           }
                        }
                        else
                        {
                            ciphertext[j] = plain[j];
                        }
                    }


                printf ("Ciphertext: %s\n", ciphertext);
                return 0;
            }
            else
            {
                printf("You should insert a positive number in prompt\n");
                return 1;
            }
        }
    }
    else
    {
        printf("You should insert a single key in prompt\n");
        return 1;
    }
}

