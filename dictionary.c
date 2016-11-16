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

#include "dictionary.h"

node* root =  NULL;
unsigned int* countWord = NULL;
//char* tempWord = NULL;

/*
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    node* root2 = root;
    int wordIndex;
    while (true)
    {
        if (*word == '\'')
        {
            wordIndex = 26;
        }
        else
        {
            wordIndex = tolower(*word) - 'a';
        }
        if(root2 -> children[wordIndex] == NULL)
        {
            return false;
        }
        else
        {
            root2 = root2-> children[wordIndex];
        }
        word++;
        if(*word == '\0')
        {
            if (root2 -> is_word == true)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    //return false;
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
    root = malloc(sizeof(node));
    node* root2 = root;
    //printf("Start loading dictionary");
    FILE* fdic = fopen(dictionary, "r");
    if (fdic == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        fclose(fdic);
        return false;
    }
    //printf("File Opened");
    char* tempHead = malloc(sizeof(char)*LENGTH);
    char* tempWord = tempHead;
    int wordIndex;
    while (fscanf(fdic, "%s",tempWord) != EOF)
    {
         //build the tries
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
    }
    //printf("load complete");
    free(tempHead);
    //printf("tempWord freed");
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

void freeNode(node* cursor)
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
