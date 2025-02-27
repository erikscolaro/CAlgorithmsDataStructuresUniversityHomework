#include "invArray.h"

struct invArray_s {
    int nInv;
    int maxInv;
    inv_t *array;
};

/* creatore e disruttore */
invArray_t invArray_init(){
    invArray_t temp = malloc(sizeof(struct invArray_s)); //sicuro?
    temp->maxInv=0; temp->nInv=0;
    return temp;
}

void invArray_free(invArray_t invArray){
    for (int i=invArray->maxInv; i>0; i--){
        free(&(invArray->array[i]));
    }
    free(invArray);
}

/* lettura e scrittura su file */
void invArray_read(FILE *fp, invArray_t invArray){
    fscanf(fp, "%d", &(invArray->maxInv));
    invArray->array=calloc(invArray->maxInv, sizeof(inv_t));
    for (int i=0; i<invArray->maxInv; i++){
        inv_read(fp, invArray_getByIndex(invArray, i));
    }
    invArray->nInv=invArray->maxInv;
}

void invArray_print(FILE *fp, invArray_t invArray){
    for (int i=0; i<invArray->nInv;i++) {
        fprintf(fp,"%d. ", i+1);
        invArray_printByIndex(fp, invArray, i);
    }
}

/* stampa un unico oggetto selezionato da indice (nel vettore) */
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    inv_print(fp, invArray_getByIndex(invArray, index));
}

/* ritorna puntatore a oggetto selezionato da indice (nel vettore) */
inv_t *invArray_getByIndex(invArray_t invArray, int index){
    if (index >=0 && index<invArray->maxInv){
        return &(invArray->array[index]);
    } else {
        return NULL;
    }
}

/* ritorna indice (nel vettore) a oggetto selezionato da nome */
int invArray_searchByName(invArray_t invArray, char *name){
    for (int i=0; i<invArray->maxInv;i++){
        if (strcmp(name, invArray_getByIndex(invArray, i)->nome)==0) return i;
    }
    return -1; //se non trova
}

int invArray_getMaxindex(invArray_t invArray){
    return invArray->maxInv-1;
}