/******************************************************************************
* (c) 2010-2019 AED Team
* Last modified: abl 2019-04-02
*
* NAME
*   word.h
*
* DESCRIPTION
*   Abstract interface for word item and table data and functions
*    (word item expected to hold string pointer and int counter)
*   File reading, table building, etc. functions, in particular:
*   - AllocaTabelaPalavras() scans the file to find number of words, alloc table
*   - PreencheTabelaPalavras() re-reads file, filling table with unique words
*
* COMMENTS
*   Needs defs.h for Item definition
******************************************************************************/
#ifndef _WORD_H_
#define _WORD_H_

#include "defs.h"

typedef struct t_palavra t_palavra;
typedef struct t_palavra **t_tabela;


char *LePalavra(FILE * f);
FILE *AbreFicheiro(char *nome, char *mode);

void ExitErroMemoria(int k);
int  AlocaTabelaPalavras(t_tabela *t, char *ficheiro);
int  NovaPalavra(t_tabela * t, char *palavra, int n_palavras);
int  PreencheTabelaPalavras(t_tabela *t, char *ficheiro);
void EscreveFicheiro(t_tabela *t, char *ficheiro, int n_palavras);
void LibertaTabelaPalavras(t_tabela *t, int nt_palavras);

int  lessAlfabetica(Item a, Item b);
int moreAlfabetica(Item a, Item b);
int moreOcorrencias(Item a, Item b);
int lessOcorrencias (Item a, Item b);
int moreComprimento(Item a, Item b);
int lessComprimento (Item a, Item b);


#endif
