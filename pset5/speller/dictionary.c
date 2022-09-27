// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"
#include <cs50.h>
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;
unsigned int w_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_word = hash(word);

    node *list = table[hash_word];

    while (list != NULL)
    {
        //もし二つの文字が一致したら
        if (strcasecmp(list -> word, word) == 0)
        {
            return true;
        }
        //次のポインタへ
        list = list -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    long sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //ファイルを開く
    FILE *file = fopen(dictionary, "r");
    //ファイルが開けなかったらfalse
    if (file == NULL)
    {
        return false;
    }
    char d_word[LENGTH + 1];
    while (fscanf(file, "%s", d_word) != EOF)
    {
        node *d_node = malloc(sizeof(node));
        if (d_node == NULL)
        {
            return false;
        }
        //d_nodeのwordの中からd_wordを収納
        strcpy(d_node -> word, d_word);

        d_node -> next = NULL;
        int i = hash(d_word);
        //もしtableの中が空だったらd_nodeをいれる
        if (table[i] == NULL)
        {
            table[i] = d_node;
        }
        else
        {
            //次のポインタを指定
            d_node -> next = table[i];
            table[i] = d_node;
        }

        w_count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return w_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {

        node *temp = table[i];
        node *a = NULL;
        while (temp != NULL)
        {
            a = temp;
            temp = temp -> next;
            free(a);
        }
    }
    return true;
}