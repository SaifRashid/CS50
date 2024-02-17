// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

int size_count = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *cursor = table[hash(word)]->next;
    while (strcasecmp(word, cursor->word) != 0)
    {

        if (cursor->next == NULL)
        {
            return false;
        }
        cursor = cursor->next;
    }
    return true;


}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *d = fopen(dictionary, "r");
    if (d == NULL)
    {
        return false;
    }
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char *word_copy[LENGTH + 1];
    while (fscanf(d, "%ms", word_copy) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        strcpy(new_node->word, *word_copy);
        if (table[hash(word_copy[0])] != NULL)
        {
            new_node->next = table[hash(word_copy[0])]->next;
            table[hash(word_copy[0])]->next = new_node;
        }
        else
        {
            node *head = malloc(sizeof(node));
            if (head == NULL)
            {
                return false;
            }
            table[hash(word_copy[0])] = head;
            table[hash(word_copy[0])]->next = new_node;
        }
        size_count++;
        free(*word_copy);
    }
    free(*word_copy);
    fclose(d);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return size_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = cursor;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }

    }
    return true;
}
