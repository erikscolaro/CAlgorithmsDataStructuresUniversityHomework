#ifndef E02_DIAGONAL_H
#define E02_DIAGONAL_H

#include "elements.h"

struct diagonal_s{
    int diff, maxDiff, nEl, maxElms;
    float val;
    int *elms;
};
typedef struct diagonal_s *diagonal_t;

void mallocDiag(diagonal_t temp, int maxElements);
//cancella anche maxDiff, non cancella maxElements
void cleanDiag(diagonal_t diagonal);
void deleteDiag(diagonal_t diagonal);
void cpyDiag(diagonal_t copied, diagonal_t toCopy);

void printDiag(diagonal_t diagonal, elements_t list, FILE *stream);
void bestDiagRec(diagonal_t diagonal, struct diagonal_s temp, elements_t list, float *bestValue, int *found);

#endif //E02_DIAGONAL_H
