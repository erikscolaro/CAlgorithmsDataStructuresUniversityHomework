#include "program.h"
#include "diagonal.h"

struct program_s{
    int diff, nDiags, maxEl, dd, dp;
    float val, maxVal;
    diagonal_t diags;
};

//dichiarata qui in modo da essere non visibile al main
void dispRip_r(int pos, int *val, int *sol, int n, int k, program_t program, elements_t list, diagonal_t diag_arr);

//funzioni di supporto all'algoritmo
float calValProg(elements_t list, diagonal_t diag_arr, int *sol, int k);
int checkDiagonals(elements_t list, diagonal_t diag_arr, int *sol, int k);
void cpyProgram(program_t target, diagonal_t diag_arr, int *sol, int k);


//FUNZIONI DI I/O

//Riferimento tramite indice ad array di elementi
program_t mallocProgram(int diags, int maxElements, int DD, int DP){
    program_t program= malloc(sizeof (struct program_s));
    program->nDiags=diags;
    program->maxEl=maxElements;
    program->diff=0;
    program->val=0;
    program->maxVal=0;
    program->dd=DD;
    program->dp=DP;
    program->diags= malloc(diags * sizeof(struct diagonal_s));
    for (int i=0; i<diags; i++) {
        mallocDiag(&(program->diags[i]), maxElements);
    }
    return program;
}

void deleteProgram(program_t program){
    for (int i=program->nDiags-1; i >= 0; i--) {
        free((program->diags[i].elms));
    }
    free(program->diags); free(program);
}

void printProgram(program_t program, elements_t list, FILE *stream){
    fprintf(stream, "Il programma migliore trovato ha difficolta' (%d) e punteggio (%.2f).\n", program->diff, program->val);
    for (int i=0; i<program->nDiags; i++){
        fprintf(stream, "Diagonale %d\n", i+1);
        printDiag(&(program->diags[i]), list, stream);
    }
}


//ALGORITMO DI CALCOLO

program_t bestProgram(int diags, int maxElInDiag, int dd, int dp, elements_t list) {
    int found=0; float bestVal=0;

    program_t program = mallocProgram(diags, maxElInDiag, dd, dp);

    struct diagonal_s temp_diag;
    temp_diag.maxElms=program->maxEl;
    temp_diag.elms=malloc(sizeof(int)*temp_diag.maxElms);


    //printf("############################################\n");
    diagonal_t arr_diag=malloc(sizeof (struct diagonal_s) * dd);
    printf("Stampo le diagonali migliori trovate in base alla difficolta':");
    for (int i=0; i<dd; i++){
        found=0; bestVal=0;
        cleanDiag(&temp_diag);
        temp_diag.maxDiff=i+1;
        arr_diag[i].elms=malloc(sizeof(int) * program->maxEl);
        bestDiagRec(arr_diag + i, temp_diag, list, &bestVal, &found);
        printf("\n- difficolta' %d:\n", i+1);
        printDiag(arr_diag+i, list, stdout);
    }
    printf("####################################\nRisultati algoritmo\n");

    int *arr_diff=malloc(sizeof(int)*program->dd);
    int *arr_sol=calloc(program->nDiags, sizeof(int));

    for (int i=0; i<program->dd; i++) arr_diff[i]=i+1;

    dispRip_r(0, arr_diff, arr_sol, program->dd, program->nDiags, program, list, arr_diag);

    free(arr_diff); free(arr_sol); free(arr_diag);

    return program;
}

void dispRip_r(int pos, int *val, int *sol, int n, int k, program_t program, elements_t list, diagonal_t diag_arr){
    if (pos>=k){ //ho trovato un array di k indici riferiti a diagonali. Controllo se la loro somma è pari al numero massimo di difficoltà.
        int diff_prog=0;
        for (int i=0; i<k; i++){
            diff_prog+=sol[i]; //la difficoltà del programma è data dalle difficoltà delle diagonali, contenute in sol
        }
        if (diff_prog<=program->dp){ //la difficoltà rientra nei massimo previsto
            float tempVal= calValProg(list, diag_arr ,sol, k);
            if (tempVal>program->maxVal){
                if (checkDiagonals(list, diag_arr, sol, k)==1){
                    program->val=tempVal;
                    program->maxVal=tempVal;
                    program->diff=diff_prog;
                    cpyProgram(program, diag_arr, sol, k);
                    //printProgram(program, list, stdout);
                }
            }
        }

        return;
    }

    for (int i=0; i<n; i++){
        sol[pos]=val[i];
        dispRip_r(pos+1, val, sol, n, k, program, list, diag_arr);
    }
}

//funzioni di supporto all'algoritmo

float calValProg(elements_t list, diagonal_t diag_arr, int *sol, int k){
    float valProg=0;
    for (int i=0; i<k; i++){
        valProg+= diag_arr[sol[i]-1].val;
    }

    if (getIntOp(list,diag_arr[sol[k-1]-1].elms[diag_arr[sol[k-1]-1].nEl-1],6)>=BONUS_THRESHOLD_DIFF){
        valProg+=diag_arr[sol[k-1]-1].val*(BONUS_MULTIPLIER-1);
    }

    return valProg;
}

int checkDiagonals(elements_t list, diagonal_t diag_arr, int *sol, int k){
    int hasElementForward=0;
    int hasElementbackward=0;
    int maxElementsInDiag=0; //1 se c'è almeno una diagonale con due elementi
    int minElementsInDiag=INT_MAX;
    for (int i=0; i<k; i++){
        if (diag_arr[sol[i]-1].nEl>maxElementsInDiag) maxElementsInDiag=diag_arr[sol[i]-1].nEl;
        if (diag_arr[sol[i]-1].nEl<minElementsInDiag) minElementsInDiag=diag_arr[sol[i]-1].nEl;
        for (int j=0; j<diag_arr[sol[i]].nEl; j++){
            if (getIntOp(list, diag_arr[sol[i]-1].elms[j], 1)==2) hasElementForward=1;
            if (getIntOp(list, diag_arr[sol[i]-1].elms[j], 1)==1) hasElementbackward=1;
        }
    }

    if (hasElementForward==1 && hasElementbackward==1 && minElementsInDiag!=0 && maxElementsInDiag>1) return 1;

    return 0;
}

void cpyProgram(program_t target, diagonal_t diag_arr, int *sol, int k){
    for (int i=0; i<k;i++){
        for (int j=0; j<diag_arr[sol[i]-1].nEl;j++){
            target->diags[i].nEl=diag_arr[sol[i] - 1].nEl;
            target->diags[i].elms[j]=diag_arr[sol[i] - 1].elms[j];
        }
    }
}