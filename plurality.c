#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }

    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{for (int j = 0; j <= candidate_count - 1; j++)
    {
        if (strcmp(name, candidates[j].name) == 0)
        {
            candidates[j].votes ++;
            return true;
        }
    }
return false;
}


// Print the winner (or winners) of the election
void print_winner(void)
{
    int votes_winner = candidates [0].votes; //variável numero de votos do vencedor, supondo que o primeiro candidato[0] é o vencedor

    for (int k = 1; k <= candidate_count; k++) // loop em todos os votos para ver qual é o maio valor e atualizar votes_winner
    {
        if (candidates[k].votes > votes_winner)
        {
            votes_winner = candidates[k].votes;
        }
    }

    if(votes_winner == 0)
    {
        printf("Election not valit\n");
    }

    else
    {
         for (int m = 0; m <= candidate_count; m++) //loop para encontrar candidatos com o máximo de pontos
        {
            if(candidates[m].votes == votes_winner)
            {
                printf("%s\n", candidates[m].name);
            }
        }
    }
    return;
}

