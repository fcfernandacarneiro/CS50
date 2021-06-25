#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

/////// END OF MAIN, FUNCTIONS BELLOW/////////



// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{

    for (int k = 0; k < candidate_count; k++) //Preenchendo matriz preferências ...
    {
        if (strcmp(name, candidates[k].name) == 0)
        {
            preferences[voter][rank] = k; //... com o valor do índice do candidato escolhido
            return true;
        }
    }
    return false;
}



// Tabulate votes for non-eliminated candidates - FOI UM PARTO FAZER ESSA FUNÇÃO FUNCIONAR EM TODOS OS CASOS, MAS FINALMENTE, NO DIA 24/5/21 AS 15:24 ELA FUNCIONOU COMO DEVIA \O/
void tabulate(void)
{

    for (int m = 0; m < voter_count; m++) //olhando para cada eleitor m
    {
        int highest_preference = 0;// preferência mais alta é o rank 0 (inicialmente)

        while(candidates[preferences[m][highest_preference]].eliminated == true)// Chacar se status do candidato é eliminado. Caso esse candidato já esteja eliminado....
        {
            highest_preference++; //entramos no WHILE LOOP até encontrar a preferência cujo o "eliminated" seja "false"
        }

        candidates[preferences[m][highest_preference]].votes++;//altera-se a matriz candidatos somando um voto para a preferência mais alta daquele eleitor m
    }
    return;
}



// Print the winner of the election, if there is one
bool print_winner(void)
{
    float min_votes = voter_count / 2;
    int max_votes = 0;
    string winner;

    for(int n = 0; n <= candidate_count; n++)
    {
        if (candidates[n].votes > max_votes)
        {
            max_votes = candidates[n].votes;
            winner = candidates[n].name;
        }
    }

    if (max_votes > min_votes)
    {
        printf("The winner is %s\n", winner);
        return true;
    }
    else
    {
    return false;
    }
}



// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = candidates[0].votes; //supondo que o mínimo é o n° de votos do candidato 0

    for (int a = 1; a < candidate_count; a++) //iterando entre os candidatos válidos para encontrar valores menores
    {
        if (candidates[a].eliminated == false && candidates[a].votes < min)
        {
            min = candidates[a].votes;//atualizando min caso haja pontuação menor
        }
    }
    return min;
}



// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int check = 0; // variável para checar empate, inicialmente é 0 (verdade)

    for(int b = 0; b<candidate_count; b++)// iterando entre os candidatos
    {
        if(candidates[b].eliminated == false && candidates[b].votes != min) // caso o candidato válido tenha votos diferente do min....
        {
            check = 1;//.. então encontramos um caso que invalida o empate
        }
    }

    if(check == 0) // retorna true caso check seja 0
    {
        return true;
    }
    else // retorna false caso check seja 1
    {
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for(int c = 0; c < candidate_count; c++)
    {
        if(candidates[c].eliminated == false && candidates[c].votes == min)
        {
            candidates[c].eliminated = true;
        }
    }
    return;
}
