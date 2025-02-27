#include "diagonal.h"
#include <stdlib.h>

void mallocDiag(diagonal_t temp, int maxElements){
    temp->val=0; temp->diff=0; temp->nEl=0; temp->maxDiff=0; temp->maxElms=maxElements;
    temp->elms=calloc(maxElements, sizeof(int));
}

void cleanDiag(diagonal_t diagonal){
    diagonal->val=0; diagonal->diff=0; diagonal->nEl=0; diagonal->maxDiff=0;
    for (int i=0; i<diagonal->maxElms; i++){
        diagonal->elms[i]=0;
    }
}

void deleteDiag(diagonal_t diagonal){
    free(diagonal->elms);
    //free(diagonal);
}

void printDiag(diagonal_t diagonal, elements_t list, FILE *stream){
    for (int i=0; i<diagonal->nEl;i++){
        printElementFromIndex(list, diagonal->elms[i],stream);
    }
}

void cpyDiag(diagonal_t copied, diagonal_t toCopy){
    copied->diff=toCopy->diff;
    copied->maxDiff=toCopy->maxDiff;
    copied->nEl=toCopy->nEl;
    copied->maxElms=toCopy->maxElms;
    copied->val=toCopy->val;
    for (int i=0; i<toCopy->nEl; i++) copied->elms[i]=toCopy->elms[i];
}

/* calcola la diagonale con il punteggio più trovata
 * avente difficoltà esattamente maxDiff
 * ritorna 1 se la trova, 0 se non la trova
 * infine copia i valori in diagonal_t diagonal*/

void bestDiagRec(diagonal_t diagonal, struct diagonal_s temp, elements_t list, float *bestValue, int *found){
    if (temp.nEl==1){
        if (getIntOp(list, temp.elms[temp.nEl-1], 2)==0){ //l'elemento iniziale non ha direzione di entrata frontale come richiesto
            return;
        }
        if (getIntOp(list,temp.elms[temp.nEl-1],4)==1){
            return; //se l'elemento è il primo ma ha bisogno di un precedente prima di lui, backtrack
        }
    } else if (temp.nEl>1){
        if (getIntOp(list, temp.elms[temp.nEl-2], 3)!=getIntOp(list, temp.elms[temp.nEl-1], 2)){ //la dirOut dell'elemento precedente non concorda con la dirIn di quello appena salvato in temp
            return; //backtrack
        }
    }

    //calcola il nuovo valore di difficoltà della diagonale
    if (temp.nEl>0){
        temp.diff= temp.diff+getIntOp(list, temp.elms[temp.nEl-1], 6);
    }

    if (temp.diff>temp.maxDiff) { //superata la difficoltà massima!
        return; //non va bene, continua il ciclo
    } else if (temp.diff==temp.maxDiff){
        temp.val=0; //giusto per essere sicuri
        for(int iEl=0; iEl<temp.nEl; iEl++){
            temp.val+= getVal(list,temp.elms[iEl]);
        }
        if (temp.val>*bestValue) {
            cpyDiag(diagonal, &temp);
            //printDiag(diagonal, list, stdout);
            *bestValue=temp.val;
            *found=(*found)+1; //setta il flag a 1 per dirmi che ha trovato una diagonale che va bene
            //fprintf(stdout, "\n");
        }
        return; //ho trovato una diagonale di difficoltà data con valore maggiore di quello massimo, continuo a ciclare.
    }

    if(temp.nEl>=temp.maxElms) return; //se c'è già il numero massimo di elementi, backtrack

    //ho già escluso l'ipotesi che la diagonale abbia la difficoltà richiesta, quindi se ho una diagonale con ultimo elemento terminale backtrack
    if (temp.nEl>0 && getIntOp(list,temp.elms[temp.nEl-1], 5)==1) return;

    for (int i=0; i<list->n_el; i++){
        temp.elms[temp.nEl]=i;
        temp.nEl++;
        bestDiagRec(diagonal, temp, list, bestValue, found);
        temp.nEl--;
    }

    return; //implicito, solo per chiarezza
}