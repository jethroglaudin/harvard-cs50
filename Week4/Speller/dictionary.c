// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// node *head = NULL;

// Represents a hash table
node *hashtable[N];

// Keeps track of total words
unsigned int count = 0;

bool isloaded = false;
// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table by making elements NULL
    // N is the total size of the Hash Table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // TODO
        // for every word that we scan we want to malloc a node for it
        node *new_node = malloc(sizeof(node));
        // check to see if malloc is not null
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        // copy dictionary word to new_node word
        strcpy(new_node->word, word);
        // set next to NULL
        new_node->next = NULL;


        //To insert word into linked list
        // get hashed value so we can get which bucket to place nodes in
        //this is essentially a pointer to each key value pair
        int hashkey = hash(new_node->word);

        // create a head node and assign it to the first node of each bucket

        node *head = hashtable[hashkey];


        // check to see if the first word in the bucket isn't there
        // meaning that the bucket is empty
        if (head == NULL)
        {
            hashtable[hashkey] = new_node;
        }

        // if the bucket is not empty, add the node to the front
        else
        {
            new_node->next = hashtable[hashkey];
            hashtable[hashkey] = new_node;
        }


        // increment count for each word found in the dictionary
        count++;


    }

    // dictionary is loaded
    isloaded = true;

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (isloaded == true)
    {
        return count;
    }
    else
    {
        // not yet loaded;
        return 0;
    }


}

// Returns true if word is in dictionary else false
bool check(const char *word)
{

    unsigned int result;
    // hash value / bucket location
    int hashkey = hash(word);

    //  assign cursor node
    node *cursor = hashtable[hashkey];
    if (cursor == NULL)
    {
        return false;
    }
    else
    {

        // Traverse Linked lists until EOF list
        while (cursor != NULL)
        {

            result = strcasecmp(cursor->word, word);
            if (result == 0)
            {
                // if we return true then word is in the dictionary
                return true;
            }

            else
            {
                // check for the next node
                cursor = cursor->next;
            }
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)

    {
        node *cursor = hashtable[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true;
}

