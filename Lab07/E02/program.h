#ifndef E02_PROGRAM_H
#define E02_PROGRAM_H

#include <stdio.h>
#include <stdlib.h>
#include "elements.h"

#define BONUS_THRESHOLD_DIFF 8
#define BONUS_MULTIPLIER 1.5

typedef struct program_s *program_t;

program_t mallocProgram(int diags, int maxElements, int DD, int DP);
program_t bestProgram(int diags, int maxElInDiag, int dd, int dp, elements_t list);

void deleteProgram(program_t program);
void printProgram(program_t program, elements_t list, FILE *stream);

#endif //E02_PROGRAM_H
