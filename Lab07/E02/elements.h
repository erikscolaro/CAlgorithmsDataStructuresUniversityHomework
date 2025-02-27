#ifndef E02_ELEMENTS_H
#define E02_ELEMENTS_H

#include <stdio.h>
#include <stdlib.h>
#include "element.h"

struct elements_s{
    int n_el;
    element_t arr;
};
typedef struct elements_s *elements_t;

//funzioni del modulo

elements_t mallocList();
elements_t startList(char *fileName);
void deleteList(elements_t target);
void printElementFromIndex(elements_t list, int index, FILE *stream);

//Ritorna campo nome dell'elemento i-esimo della lista
char *getName(elements_t list, int index);

/*Ritorna il campo op dell'elemento i-esimo della lista
 * 1 type, 2 dirIn, 3 dirOut, 4 prec, 5 fin, 6 diff*/
int getIntOp(elements_t list, int index, int op);

//Ritorna campo val dell'elemento i-esimo della lista
float getVal(elements_t list, int index);

int getElNum(elements_t list);

#endif //E02_ELEMENTS_H
