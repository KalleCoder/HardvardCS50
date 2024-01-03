#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    int wrong = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) != 0)
        {
            wrong++;
        }

        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            //printf("%d\n", ranks[rank]);
        }
    }
    if (wrong == candidate_count)
    {
        wrong = 0;
        return false;
    }
    else
    {
        return true;
    }
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    typedef struct
    {
        int rank_value;
        int index;
    } rank_index;
    rank_index information[candidate_count];

    // making the array
    for (int i = 0; i < candidate_count; i++)
    {
        int x = ranks[i];
        // printf("Here x is: %d\n", x);
        int index = 0;
        for (int k = 0; k < candidate_count; k++)
        {
            if (ranks[k] == x)
            {
                information[i].index = k;
                information[i].rank_value = x;
            }
        }
    }

    // Adding preferences
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == information[j].rank_value)
            {
                for (int k = 0; k < candidate_count; k++ )
                {
                    if (information[k].index > information[j].index)
                    {
                        preferences[i][information[k].rank_value]++;
                    }
                }
            }
        }
    }

    //printing the 2d array
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%d", preferences[i][j]);
        }
        printf("\n");
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO

    pair_count=0;
    // getting the winners
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }


    // printing the pairs array

    for (int i = 0; i < pair_count; i++)
    {
        printf("List placement winner %d: %d\n", i, pairs[i].winner);
        printf("List placement loser  %d: %d\n", i, pairs[i].loser);
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    typedef struct
    {
        int difference;
        int index;
        int winner;
        int loser;

    }data;
    data differences[pair_count];

    // adding the differences between each pair
    for (int i = 0; i < pair_count; i++)
    {
        differences[i].difference = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        differences[i].index = i;
        differences[i].winner = pairs[i].winner;
        differences[i].loser = pairs[i].loser;
    }

    // printing the differences
    for (int i = 0; i < pair_count; i++)
    {
        printf("Here is the difference of the pair %d: %d\n", i, differences[i].difference);
    }

    // sorting the pairs
    int a, b, c, d;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (differences[i].difference > differences[j].difference)
            {
                // one for each collected data
                // differences
                a = differences[i].difference;
                differences[i].difference = differences[j].difference;
                differences[j].difference = a;
                // index
                b = differences[i].index;
                differences[i].index = differences[j].index;
                differences[j].index = b;
                // winner
                c = differences[i].winner;
                differences[i].winner = differences[j].winner;
                differences[j].winner = c;
                // loser
                d = differences[i].loser;
                differences[i].loser = differences[j].loser;
                differences[j].loser = d;
            }
        }
    }
    // printing the updated order in differences array
    printf("\n");
    for (int i = 0; i < pair_count; i++)
    {
        printf("Here is the difference of pair %d: %d\n", i, differences[i].difference);
    }

    // updating order in pairs array
    for (int i = 0; i < pair_count; i++)
    {
        pairs[i].winner = differences[i].winner;
        pairs[i].loser = differences[i].loser;
    }


    // printing the new order
    for (int i = 0; i < pair_count; i++)
    {
        printf("List placement winner %d: %d\n", i, pairs[i].winner);
        printf("List placement loser  %d: %d\n", i, pairs[i].loser);
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        // trying to make it not go in circles
        bool found_loop = false;
        for (int z = 0; z < candidate_count; z++)
        {
            for (int k = 0; k < candidate_count; k++)
            {
                if (locked[z][k] == locked[pairs[i].winner][pairs[i].loser])
                {

                    if (locked[pairs[i].loser][k] == true)
                    {

                        for (int f = 0; f < candidate_count; f++)
                        {
                            if (locked[k][f] == true)
                            {
                                locked[pairs[i].winner][pairs[i].loser] = false;
                                //printf("i = %d, k = %d, z = %d\n", i, k, z);
                                found_loop = true;
                                printf("Found loop!");
                            }
                            else
                            {
                                if (found_loop == true)
                                {
                                    continue;
                                }
                                else
                                {
                                    locked[pairs[i].winner][pairs[i].loser] = true;
                                }
                                found_loop = false;
                            }
                        }
                    }
                    else
                    {
                        if (found_loop == true)
                        {
                            continue;
                        }
                        else
                        {
                            locked[pairs[i].winner][pairs[i].loser] = true;
                        }
                        found_loop = false;
                    }
                }
            }
        }
        printf("\n");
     }

    // print locked array
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%d", locked[i][j]);
        }
        printf("\n");
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int winner_index = 7;

    for (int i = 0; i < pair_count; i++)
    {
        if (locked[pairs[i].winner][pairs[i].loser] == false)
        {
            continue;
        }
        else
        {
            for (int f = 0; f < candidate_count; f++)
            {
                if (locked[pairs[i].loser][f] == true)
                {
                    continue;
                }
                else
                {
                    winner_index = i;
                }
            }
        }
    }

    printf("The winner is: %s\n", candidates[pairs[winner_index].winner]);

    return;
}