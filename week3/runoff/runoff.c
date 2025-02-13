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
    // Look for a candidate called name
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            // If name is a match update the global preferences array
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Clear previous votes
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
    }

    // Iterate over each voter
    for (int i = 0; i < voter_count; i++)
    {
        // Iterate over each voter's preferences
        for (int j = 0; j < candidate_count; j++)
        {
            int candidate_index = preferences[i][j];

            // Check if the candidate is not eliminated
            if (!candidates[candidate_index].eliminated)
            {
                // Increment the vote count for the candidate
                candidates[candidate_index].votes++;
                break; // Move to the next voter
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Ensure voter_count is treated as a float
    float all_votes = (float) voter_count;

    // If a candidate has majority of votes, print candidate as winner
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > (all_votes / 2))
        {
            printf("Winner is: %s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Initialize the minimum vote to a high value (maximum number of voters)
    int min_vote = MAX_VOTERS;

    // Iterate through every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Only consider non-eliminated candidates
        if (!candidates[i].eliminated && candidates[i].votes < min_vote)
        {
            // Update the minimum vote if the current candidate's votes are lower
            min_vote = candidates[i].votes;
        }
    }
    return min_vote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if any non-eliminated candidate's votes are not equal to the minimum vote
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            // If any candidate has a vote count other than min, election is not a tie
            return false;
        }
    }
    // If all remaining candidates have the minimum vote, election is a tie
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if any non-eliminated candidate's votes are equal to the minimum vote
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            // If any candidate has vote count min, eliminate
            candidates[i].eliminated = true;
        }
    }
}
