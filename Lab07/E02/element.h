#ifndef E02_ELEMENT_H
#define E02_ELEMENT_H

#include <stdio.h>

struct element_s{
    char name[100];
    int type, dirIn, dirOut, prec, fin, diff;
    float val;
};
typedef struct element_s *element_t;

void readElement(FILE *fp, element_t target);
void printElement(FILE *stream, element_t target);

#endif //E02_ELEMENT_H
