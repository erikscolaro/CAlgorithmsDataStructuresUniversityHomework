#include "element.h"
#include <stdio.h>
#include <stdlib.h>

void readElement(FILE *stream, element_t target){
    fscanf(stream, "%s %d %d %d %d %d %f %d",
           target->name,
           &(target->type),
           &(target->dirIn),
           &(target->dirOut),
           &(target->prec),
           &(target->fin),
           &(target->val),
           &(target->diff)
    );
}

void printElement(FILE *stream, element_t target){
    fprintf(stream, "%25.25s\t%d\t%d\t%d\t%d\t%d\t%.2f\t%d\n",
           target->name,
           target->type,
           target->dirIn,
           target->dirOut,
           target->prec,
           target->fin,
           target->val,
           target->diff
    );
}