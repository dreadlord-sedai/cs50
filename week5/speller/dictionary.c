// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>  // Include this for FILE and file operations
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

// Global variable to keep track of the number of words loaded into the dictionary
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Step 1: Hash the word to get its hash value (index in the table)
    unsigned int index = hash(word);

    // Step 2: Access the linked list at the computed hash table index
    node *cursor = table[index];

    // Step 3: Traverse the linked list
    while (cursor != NULL)
    {
        // Step 4: Compare the current word in the node to the given word
        // Use strcasecmp to perform a case-insensitive comparison
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;  // Word found in dictionary
        }

        // Move to the next node in the linked list
        cursor = cursor->next;
    }

    // If the word is not found, return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long hash_value = 0;
    int prime = 31;  // A small prime number commonly used in hash functions

    // Iterate through each character in the word
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash_value = (hash_value * prime + tolower(word[i])) % N;  // Use lowercase for case-insensitivity
    }

    return hash_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");

    // Check whether the file opened correctly
    if (source == NULL)
    {
        return false;
    }

    // Buffer to store each word
    char word[LENGTH + 1];

    // Read each word in the file
    while (fscanf(source, "%s", word) != EOF)
    {
        // Create a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(source);
            return false;
        }

        // Copy the word into the new node
        strcpy(new_node->word, word);

        // Hash the word to find the correct hash value
        unsigned int index = hash(word);

        // Insert the node into the hash table at the correct index
        new_node->next = table[index];
        table[index] = new_node;

        // Increase the word count (used for size() function)
        word_count++;
    }

    // Close the dictionary file
    fclose(source);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return the global word count
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over each bucket in the hash table
    for (int i = 0; i < N; i++)
    {
        // Pointer to the current node in the linked list at table[i]
        node *cursor = table[i];

        // Traverse the linked list and free each node
        while (cursor != NULL)
        {
            node *temp = cursor;  // Save the current node
            cursor = cursor->next;  // Move to the next node
            free(temp);  // Free the saved node
        }
    }

    // After freeing all nodes, return true to indicate success
    return true;
}
