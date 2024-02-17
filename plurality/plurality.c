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
{
    // TODO
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

int recursion_count = 1;

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Temp var to switch candidates
    candidate temp;
    int swap_counter = -5;

    // Bubble sort to see largest votes for candidate
    for (int i = 0, n = candidate_count; i < n - recursion_count; i++)
    {
        swap_counter = 0;
        if (candidates[i].votes < candidates[i + 1].votes)
        {
            temp = candidates[i];
            candidates[i] = candidates[i + 1];
            candidates[i + 1] = temp;
            swap_counter += 1;
        }
        if (swap_counter == 0)
        {
            printf("%s\n", candidates[0].name);
            for (int j = 1, k = candidate_count; j < k; j++)
            {
                if (candidates[0].votes == candidates[j].votes)
                {
                    printf("%s\n", candidates[j].name);
                }
            }
            return;
        }
    }
    print_winner();
}