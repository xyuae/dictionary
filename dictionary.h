/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

#endif // DICTIONARY_H

typedef struct node
{
    bool is_word;
    struct node* children[27];
} node;

// Trie node
typedef struct TrieNode
{
    // first 26 space for alphabet
    // last space for "'"
     struct TrieNode *children[27];
     

     // isLeaf is true if the node represents
     // end of a word
     bool isLeaf;
} TrieNode;

TrieNode *getNode(void);

void insert(struct TrieNode *root, const char *key);