/******************************************************************************
* (c) 2010-2019 AED Team
* Last modified: abl 2019-04-02
*
* NAME
*   word.c
*
* DESCRIPTION
*   Data structure to hold word and useage count
*	Auxiliary functions to read and write text files
*		functions to allocate and manipulate structures
*		functions to sort abstract structures
*		implementations of "less" functions for different criteria
*
* COMMENTS
*   Code for preliminary distribution, to be completed
******************************************************************************/
#define MAX_CHARS 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>    /* strcasecmp() */

#include "word.h"

struct t_palavra {              /* structure for word */
    char *nome;
    int ocorrencias;
};



/******************************************************************************
* ExitErrorMemoria ()
*
* Arguments:    k - exit status to use
* Returns:      (void)
* Side-Effects: executions ends
*
* Description: general function for memory allocation error and exit
*****************************************************************************/
void ExitErroMemoria(int k)
{
    fprintf(stderr, "ERROR: Not enough memory.\n");
    exit(k);
}


/******************************************************************************
* LePalavra ()
*
* Arguments:    fp - file pointer to read from
* Returns:      char * - pointer to word read, NULL if read fails
* Side-Effects: none
*
* Description:
*   Reads a word from open file, returns pointer to local static buffer
*   Words in file are assumed to not exceed MAX_CHARS-1 in length
*****************************************************************************/
char *LePalavra(FILE * fp)
{
    static char palavra[MAX_CHARS];         /* buffer for caller to copy */

    if (fscanf(fp, "%s", palavra) == 1)
        return palavra;
    else
        return NULL;
}


/******************************************************************************
* AbreFicheiro ()
*
* Arguments: nome - pointer to string containing name of file to open
*            mode - mode to use to open the file
* Returns: FILE * - handle to file opened
* Side-Effects: input file is opened
*
* Description: Open file for reading, returns handle, or exits if it fails
*****************************************************************************/
FILE *AbreFicheiro(char *nome, char *mode)
{
    FILE *fp;

    fp = fopen(nome, mode);
    if (fp == NULL) {
        fprintf(stderr, "Error: Unable to open file '%s'\n.", nome);
        exit(1);
    }
    return fp;
}


/******************************************************************************
* AlocaTabelaPalavras ()
*
* Arguments: t - pointer to word table
*            ficheiro - handle for input file
* Returns: int - number of words read
* Side-Effects: words are read, word table is allocated; input file is closed
*
* Description: Reads the input file, counts the total number of words and
*		allocates the memory for the table structure
*****************************************************************************/
int AlocaTabelaPalavras(t_tabela * t, char *ficheiro)
{
    FILE *fp;
    char *palavra;

    int nt_palavras = 0;

    fp = AbreFicheiro(ficheiro, "r");
    while ((palavra = LePalavra(fp)) != NULL)
        nt_palavras++;

    fclose(fp);

    (*t) = (t_tabela) malloc(nt_palavras * sizeof(t_palavra *));

    if (*t == NULL)
        ExitErroMemoria(2);

    return nt_palavras;
}


/******************************************************************************
* NovaPalavra ()
*
* Arguments:    t - pointer to word table
*               palavra - pointer to string containing word
*               n_palavras - number of distinct words found so far
* Returns:      int - index/status regarding word being new
* Side-Effects: none
*
* Description: Search table for word, return index or -1 if not found
*****************************************************************************/
int NovaPalavra(t_tabela * t, char *palavra, int n_palavras)
{
    int i = 0;

    while (i < n_palavras) {
        if (strcasecmp((*t)[i]->nome, palavra) == 0)
            return i;
        i++;
    }
    return -1;
}


/******************************************************************************
* PreencheTabelaPalavras ()
*
* Arguments:    t - pointer to word table
*               ficheiro - name of input file
* Returns:      int - number of distinct words in file
* Side-Effects: prints message with distinct word count
*
* Description: Opens file, fills table with distinct words found
*****************************************************************************/
int PreencheTabelaPalavras(t_tabela * t, char *ficheiro)
{
    FILE *f;
    int n;
    char *palavra;
    int n_palavras = 0;

    f = AbreFicheiro(ficheiro, "r");
    while ((palavra = LePalavra(f)) != NULL) {
        if ((n = NovaPalavra(&(*t), palavra, n_palavras)) == -1) {
            /* word has not been seen; add to table */
            (*t)[n_palavras] = (t_palavra *) malloc(sizeof(t_palavra));

            if ((*t)[n_palavras] == NULL)
                ExitErroMemoria(3);
            (*t)[n_palavras]->nome = (char *) malloc(
                                sizeof(char) * (strlen(palavra) + 1));

            if ((*t)[n_palavras]->nome == NULL)
                ExitErroMemoria(4);
            strcpy((*t)[n_palavras]->nome, palavra);
            (*t)[n_palavras]->ocorrencias = 1;
            n_palavras++;
        }
        else {
            /* word is not new; increment occurrence count */
            (*t)[n]->ocorrencias++;
        }
    }
    fclose(f);

    return n_palavras;
}


/******************************************************************************
* EscreveFicheiro ()
*
* Arguments: t - pointer to word table
*            ficheiro - handle for output file
*            n_palavras - number of distinct words seen
* Returns: (void)
* Side-Effects: output file is written
*
* Description: Writes table to file
*****************************************************************************/
void EscreveFicheiro(t_tabela * t, char *ficheiro, int n_palavras)
{
    FILE *f;
    char *nome;
    int i = 0;

    nome = (char *) malloc(
                (strlen(ficheiro) + strlen(".palavras") + 1) * sizeof(char));
    if (nome == NULL) {
        fprintf(stderr,
            "ERROR: allocation of output filename. Not enough memory.\n");
        exit(2);
    }
    strcpy(nome, ficheiro);
    strcat(nome, ".palavras");

    f = AbreFicheiro(nome, "w");
    for (i = 0; i < n_palavras; i++) {
        fprintf(f, "%d: %s\n", (*t)[i]->ocorrencias, (*t)[i]->nome);
    }

    fclose(f);
    free(nome);

    return;
}


/******************************************************************************
* LibertaTabelaPalavras ()
*
* Arguments: t_tabela - pointer to word table
*            nt_palavras - total number of words
* Returns: (void)
* Side-Effects: free memory allocated for word table
*
* Description: Frees the memory allocated in t_tabela
*****************************************************************************/
void LibertaTabelaPalavras(t_tabela *t, int nt_palavras)
{
    /** -- free all memory allocated for table of words -- */

    /*==== TODO ====*/

    return;
}


/******************************************************************************
* LessAlfabetica ()
*
* Arguments: a, b - items to be compared
* Returns: int - result of comparison
* Side-Effects: none
*
* Description: Implements the comparision for alphabetic ordering
*****************************************************************************/
int lessAlfabetica(Item a, Item b)
{
    if (strcasecmp(((t_palavra *) a)->nome, ((t_palavra *) b)->nome) < 0)
        return 1;
    else
        return 0;
}

int moreAlfabetica(Item a, Item b)
{
    if (strcasecmp(((t_palavra *) a)->nome, ((t_palavra *) b)->nome) > 0)
        return 1;
    else
        return 0;
}

int moreOcorrencias(Item a, Item b)
{
    if ( ((t_palavra *) a)->ocorrencias > ((t_palavra *) b)->ocorrencias)
        return 1;
    else
        return 0;
}

int lessOcorrencias (Item a, Item b)
{
    if ( ((t_palavra *) a)->ocorrencias < ((t_palavra *) b)->ocorrencias)
        return 1;
    else
        return 0;
}

int moreComprimento(Item a, Item b)
{
    if ( strlen(((t_palavra *) a)->nome) > strlen(((t_palavra *) b)->nome))
        return 1;
    else
        return 0;
}

int lessComprimento (Item a, Item b)
{
    if ( strlen(((t_palavra *) a)->nome) < strlen(((t_palavra *) b)->nome))
        return 1;
    else
        return 0;
}


/*************************************************************************
**  -- Add comparison functions for the remaining criteria --
*************************************************************************/

    /*==== TODO ====*/

