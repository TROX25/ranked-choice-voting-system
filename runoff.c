#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
} candidate;

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

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    //#1 Sprawdzam czy istnieje kandydant o nazwie name
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0) //#2 Jeśli isntieje to dla każdego votera przypisuje mu range jaką mu przydzielił
        {
            preferences[voter][rank] = i; // dla każdego kandydata [i] przypisuje numer głosujacego [voter] oraz range jaką mu ten voter przydielił [rank]
            return true; // Przykład preference [0][0] = 0, czyli pierwszy głos, pierwszego kandydata został oddany na pierwszego kandydata z listy
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        if (candidates[preferences[i][0]].eliminated == false)
        {
            candidates[preferences[i][0]].votes += 1;
        }

        else if (candidates[preferences[i][0]].eliminated == true)
        {
            for (int j = 1; j < candidate_count; j++)
            {
               if (candidates[preferences[i][0+j]].eliminated == false)
               {
                candidates[preferences[i][0+j]].votes += 1;
                break;
               }
            }
        }
     }
     return;
    }

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int suma_glosow = 0;
    for ( int i = 0; i < candidate_count; i++)
    {
        suma_glosow += candidates[i].votes;
    }
    for ( int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > (suma_glosow /2))
        {
        printf("%s\n",candidates[i].name);
        return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = 999;
    for ( int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == true)
        {
            continue;
        }
        else if (candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int tie_counter = 0;
    int eliminated_counter = 0;
    for ( int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == true)
        {
            eliminated_counter += 1;
            continue;
        }
        if (candidates[i].votes == min)
        {
            tie_counter += 1;
        }
    }
    if (tie_counter == (candidate_count - eliminated_counter))
    {
    return true;
    }
    else
    {
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == true)
        {
            continue;
        }
        else if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}




// test
/*
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        if (candidates[preferences[i][0]].eliminated == false)
        {
            candidates[preferences[i][0]].votes += 1;
        }

        else if (candidates[preferences[i][0]].eliminated == true)
        {
            for (int j = 1; j < candidate_count; j++)
            {
               if (candidates[preferences[i][0+j]].eliminated == false)
               {
                candidates[preferences[i][0+j]].votes += 1;
                break;
               }
            }
        }
     }

    }
*/
