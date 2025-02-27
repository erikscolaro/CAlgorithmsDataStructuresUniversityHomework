#include "pgList.h"

typedef struct node_s{
    pg_t pg;
    struct node_s *next;
}*node_t;

struct pgList_s{
    node_t head;
    node_t tail;
    int nPg;
};

/* creatore e distruttore */
pgList_t pgList_init(){
    pgList_t temp=malloc(sizeof(struct pgList_s));
    temp->nPg=0;
    temp->head=NULL;
    temp->tail=temp->head;
    return temp;
}

void pgList_free(pgList_t pgList) {
    node_t del = pgList->head, temp=del->next;

    if (del == NULL) return;

    for (;temp != NULL; del=temp, temp=temp->next) {
        pg_clean(&(del->pg));
        free(del);
        pgList->nPg--;
    }
    pg_clean(&(pgList->tail->pg));
    free(pgList->tail);
    free(pgList);
}

/* lettura e scrittura su file */
void pgList_read(FILE *fp, pgList_t pgList){

    if(pgList->nPg==1) pgList->tail=pgList->head;

    node_t temp=malloc(sizeof(struct node_s));
    if (pg_read(fp, &(temp->pg))!=0){
        pgList->nPg++;
        temp->next=pgList->head;
        pgList->head=temp;
        pgList_read(fp, pgList);
    }
}


void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    node_t temp=pgList->head;

    if (pgList->head!=NULL){
        pg_print(fp, &(temp->pg) ,invArray);
        do {
            temp=temp->next;
            pg_print(fp, &(temp->pg) ,invArray);
        } while (temp!=pgList->tail);
    } else{
        fprintf(fp, "Empty pgList.\n");
    }
}

/* inserimento di un nuovo personaggio */
void pgList_insert(pgList_t pgList, pg_t pg){
    node_t ins=malloc(sizeof(struct node_s));
    ins->pg=pg;
    ins->next=pgList->head;
    pgList->head=ins;
    pgList->nPg++;
}

/* cancellazione con rimozione */
void pgList_remove(pgList_t pgList, char* cod){
    node_t del=pgList->head, temp=NULL;

    if (del==NULL) return;

    for (;del!=NULL; temp=del, del=del->next){
        if (strcmp(cod, del->pg.cod)==0){
            if (del==pgList->head){
                pgList->head=del->next;
            } else if (del==pgList->tail) {
                pgList->tail=temp;
            } else {
                temp->next = del->next;
            }
            pg_clean(&(del->pg));
            free(del);
            pgList->nPg--;
            return;
        }
    }
}

/* ricerca per codice, ritornando il puntatore */
pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    node_t temp=pgList->head;

    if (strcmp(cod, temp->pg.cod)==0) return &(temp->pg);
    do {
        temp=temp->next;
        if (strcmp(cod, temp->pg.cod)==0) return &(temp->pg);
    } while (temp!=pgList->tail);

    return NULL; //se non trova
}

/* Si possono aggiungere altre funzioni se ritenute necessarie */
