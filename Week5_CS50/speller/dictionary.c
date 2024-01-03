// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Global count of dictionary words
int amount_of_words = 0;
//global bool if the dictionary was loaded
bool loaded = false;

bool check(const char *word) // Returns true if word is in dictionary, else false
{
    int index = hash(word); // Getting the spot for where to find the word in the hash table

    // making variable to copy over the text word
    char *copy_word = (char *) malloc(strlen(word) + 1);
    if (copy_word == NULL)
    {
        return false; // if no memory available
    }
    strcpy(copy_word, word);
    int length = strlen(copy_word);

    for (int i = 0; i < length; i++) // making it lowercase so I can compare with dictionary
    {
        copy_word[i] = tolower(copy_word[i]);
    }


    // Time to compare the copied word with the dictionary words in the hash table
    node *ptr = table[index];
    while (ptr != NULL)
    {

        char *dict_word_lower = (char *) malloc(strlen(ptr->word) + 1); // Making a variable to copy over the dict word
        if (dict_word_lower == NULL)
        {
            free(copy_word);
            return false; // If nor memory available
        }
        strcpy(dict_word_lower, ptr->word);
        int length_dict_word = strlen(dict_word_lower);
        for (int i = 0; i < length_dict_word; i++)
        {
            dict_word_lower[i] = tolower(dict_word_lower[i]); // turning it into lowercase
        }

        //  compareing to the words in the dictionary
        if (strcmp(dict_word_lower, copy_word) == 0)
        {
            free(copy_word);
            free(dict_word_lower);
            return true;
        }
        ptr = ptr->next; // moving to the next node in the list
        free(dict_word_lower); // always free the dictionary words for each loop itteration
    }
    free(copy_word);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // A simple hash table. Could Probably made a cooler one but this is the easier way.
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

    // Checking the first letter of each word to place it at the correct index in the table
    for (int j = 0; j < 26; j++)
    {
        if (word[0] == alphabet[j])
        {
            return j;
        }
    }

   return toupper(word[0]) - 'A'; // Dont really know whtat this is but works with it here.
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open the file
    FILE *f = fopen(dictionary, "r");
    // check if you have enough memory
    if (f == NULL)
    {
        return false;
    }

    char word_from_dict[46]; // making a variable to store the dictionary word in

    while (fscanf(f, "%s", word_from_dict) != EOF) // read strings from file one at a time
    {
        // Create a new node for each word
        node *n = (struct node *) malloc(sizeof(struct node));
        if (n == NULL)
        {
            return false; // if no memory
        }

        int index = hash(word_from_dict); // takes the string and returns the index

        strcpy(n->word, word_from_dict); // copies over the word to the new node

        n->next = table[index]; // first pointing the new node to the old node
        table[index] = n;       // making it so the head has the address of n
        amount_of_words++; // making the global word counter increase for each itteration
    }

    // THIS ELOW BROKE THE CHECK FUNCTION BY DELETING ALL THE VALUES

    /*while (table[0] != NULL) // prints out the words in index 0 to see if it works.
    {
        printf("Words in linked list; %s\n", table[0]->word);
        table[0] = table[0]->next;
    }*/

    fclose(f);
    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Here I use the global counter and return it if the global value loaded is true
    if (loaded == true)
    {
        return amount_of_words;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Goes thorugh each index in the table and removes the linked list untill its end
    for (int i = 0; i < 26; i++)
    {
        struct node *next; // to save the next node address
        while (table[i] != NULL)
        {
            next = table[i]->next;
            free(table[i]); // kills the node
            // if (free(table[i]) = ! -->  false)
            table[i] = next; // makes it so we head to the next one
        }
    }
    return true;
}
