#include "elements.h"

elements_t mallocList(){
    elements_t temp;
    temp=malloc(sizeof(struct elements_s));
    temp->n_el=0;
    return temp;
}

elements_t startList(char *fileName){
    elements_t list=mallocList();

    FILE *fp;
    fp= fopen(fileName, "r");

    fscanf(fp, "%d", &(list->n_el));
    list->arr=malloc(list->n_el*sizeof(struct element_s));
    for (int i=0; i<list->n_el; i++){
        readElement(fp, &(list->arr[i]));
    }

    fclose(fp);
    return list;
}

void deleteList(elements_t target){
    free(target->arr);
    free(target);
}

void printElementFromIndex(elements_t list, int index, FILE *stream){
    printElement(stream, &(list->arr[index]));
}

char *getName(elements_t list, int index){
    return list->arr[index].name;
}

int getIntOp(elements_t list, int index, int op){
    switch (op){
        case 1: return list->arr[index].type;
        case 2: return list->arr[index].dirIn;
        case 3: return list->arr[index].dirOut;
        case 4: return list->arr[index].prec;
        case 5: return list->arr[index].fin;
        case 6: return list->arr[index].diff;
        default: exit(1);
    }
}

float getVal(elements_t list, int index){
    return list->arr[index].val;
}

int getElNum(elements_t list){
    return list->n_el;
}

