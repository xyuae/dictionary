/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (27)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) (c - 'a')

TrieNode* root =  NULL;
unsigned int* countWord = NULL;
//char* tempWord = NULL;

// Returns new trie node (initialized to NULLs)
TrieNode *getNode(void)
{
    TrieNode *pNode = NULL;
 
    pNode = malloc(sizeof(struct TrieNode));
 
    if (pNode)
    {
        int i;
 
        pNode->isLeaf = false;
 
        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }
 
    return pNode;
}


/*
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    TrieNode *pCrawl = root;
    int level;
    int length = strlen(word);
    int index;
    
    for (level = 0; level < length; level++)
    {
        if (word[level] == '\'')
        {
            index = 26;
        }
        else
        {
            index = CHAR_TO_INDEX(tolower(word[level]));
        }
        
        if (pCrawl->children[index] == NULL)
            return false;
 
        pCrawl = pCrawl->children[index];
    }
 
    return (pCrawl != NULL && pCrawl->isLeaf);
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
 
    struct TrieNode *pCrawl = root;
 
    for (level = 0; level < length; level++)
    {
        if (key[level] == '\'')
        {
            index = 26;
        }
        else
        {
            index = CHAR_TO_INDEX(tolower(key[level]));
        }
        if (pCrawl->children[index] == NULL)
            pCrawl->children[index] = getNode();
 
        pCrawl = pCrawl->children[index];
    }
 
    // mark last node as leaf
    pCrawl->isLeaf = true;
}


/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    //initiat countWord
    countWord = malloc(sizeof(unsigned int));
    *countWord = 0;
    // TODO
    root = getNode();
    //TrieNode* root2 = root;
    //printf("Start loading dictionary");
    FILE* fdic = fopen(dictionary, "r");
    if (fdic == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        fclose(fdic);
        return false;
    }
    
    char* tempHead = malloc(sizeof(char)*LENGTH);
    //char* tempWord = tempHead;
    //int wordIndex;
    // read the next word and store its pointer in tempWord
    while (fscanf(fdic, "%s", tempHead) != EOF)
    {
        //build the tries
        insert(root, tempHead);
        //free(tempWord);
        *countWord = *countWord +1;
        //tempWord = tempHead;
    /**     
         while (true)
         {
             if (*tempWord == '\'')
             {
                 wordIndex = 26;
             }
             else
             {
                 
                 wordIndex = tolower(*tempWord) - 'a';
             }
             //printf("%d", wordIndex);
             //traverse through the tempWord and build the tries
             if(root2 -> children[wordIndex] == NULL)
             {
                 root2 ->children[wordIndex] = malloc(sizeof(node));
             }
             root2 = root2 -> children[wordIndex];
             tempWord ++;
             if (*tempWord == '\0')
             {
                 root2 -> is_word = true;
                 *countWord = *countWord +1;
                 tempWord = tempHead;
                 root2 = root;
                 break;
             }
         }
    **/
    }
    free(tempHead);
    
    fclose(fdic);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return *countWord;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */

void freeNode(TrieNode* cursor)
{
    for (int index = 0; index < 27; index++)
    {
        if (cursor ->children[index] != NULL)
        {
            freeNode(cursor -> children[index]);    
        }
    }
    free(cursor);
    return;
}

bool unload(void)
{
    // TODO
    free(countWord);
    freeNode(root);
    //free(root);
    return true;
}
