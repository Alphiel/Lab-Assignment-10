#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// use calloc when intializing trie
// for each word in pWords, add it to the trie

typedef struct Trie {
    int flag;
    struct Trie *children[26];
} Trie;

void insert(struct Trie **ppTrie, char *word) {
    if(*ppTrie == NULL) 
        return;
    
    Trie *temp = *ppTrie;
    int length = strlen(word);
    for(int i = 0; i < length; i++) {
        int index = word[i] - 'a';

        if(temp->children[index] == NULL) {
            // allocate memory for that child
            temp->children[index] = (Trie*) calloc(1, sizeof(Trie));
        }
        temp = temp->children[index];
    }
    temp->flag++;
};
int numberOfOccurances(struct Trie *pTrie, char *word) {
    if(pTrie == NULL) 
        return 0;

    Trie *temp = pTrie;
    int index;
    int length = strlen(word);
    for(int i = 0; i < length; i++) {
        index = word[i] - 'a';

        if(temp->children[index] == NULL)
            return 0;

        temp = temp->children[index];
    }
    
    return temp->flag;
};
struct Trie *deallocateTrie(struct Trie *pTrie) {
    for(int i = 0; i < 26; i++)
        if(pTrie->children[i] != NULL)
            pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    free(pTrie);
    return NULL;
};

int main(void)
{
    Trie* trie = (Trie*) calloc(1, sizeof(Trie)); 
    
    //read the number of the words in the dictionary
    // parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    
    for(int i = 0; i < 5; i++)
        insert(&trie, pWords[i]);
    
    for (int i=0;i<5;i++)
    {
        printf("\t%s : %d\n",pWords[i], numberOfOccurances(trie, pWords[i]));
    }

    trie = deallocateTrie(trie);
    if (trie != NULL)
       printf("There is an error in this program\n");

    return 0;
}