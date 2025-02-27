#include <stdio.h>
#include <stdlib.h>

#define DIR "..//att1.txt"
#define DBG 0

typedef struct {
    int s;
    int f;
} job;

typedef struct {
    int nj;
    job *jobs;
} *JL; //Job list

JL readJobs(void);

void LISDPVar(JL list);

int duration(JL list, int i);

int overlap(JL list, int i, int j);

void displaySol(JL list, int *P, int last);

int main() {
    JL job_list= malloc(sizeof (JL));

    job_list=readJobs();

    //funzione ordinamento lavori

    LISDPVar(job_list);

    return 0;
}

JL readJobs(void){
    JL temp=malloc(sizeof (JL));
    FILE *fp;
    fp=fopen(DIR, "r");
    fscanf(fp, "%d", &(temp->nj));

    temp->jobs=(job*) malloc(temp->nj * sizeof(job));
    for (int i=0; i<temp->nj; i++){
        fscanf(fp, "%d %d", &(temp->jobs[i].s),&(temp->jobs[i].f));
    }
    fclose(fp);
    return temp;
}

int duration(JL list, int i){
    return list->jobs[i].f-list->jobs[i].s;
}

int overlap(JL list, int i, int j){//1 true, 0 false
    // si suppone che gli elementi siano ordinati e che quindi list->jobs[i].s <=list->jobs[j].s
    if (list->jobs[i].f<=list->jobs[j].s) return 0;
    return 1;
}

void LISDPVar(JL list){
    int ris=1, last=1,*L=malloc(list->nj*sizeof(int)),*P=malloc(list->nj*sizeof(int));
    L[0]=duration(list, 0);
    P[0]=-1;
    for (int i=1; i<list->nj; i++){
        L[i]=duration(list, 1);
        P[i]=-1;
        for(int j=0; j<i; j++){
            if (!overlap(list,j,i) && (L[i]<L[j]+duration(list, i))) {
                L[i] = L[j] + duration(list, i);
                P[i] = j;
            }
        }
        if (ris<L[i]) ris=L[i], last=i;
    }

#if DBG==1
    for (int i=0; i<list->nj; i++) printf("%d. L=%d\tP=%d\n",i,L[i],P[i]);
#endif
    printf("Una sequenza di attivita' che ne massimizza la durata e':\n");
    printf("{");displaySol(list, P, last);printf("}\n");
    printf("e la sua lunghezza e' %d.\n", ris);

}

void displaySol(JL list, int *P, int last){
    if (P[last]==-1){
        printf("(%d;%d)",list->jobs[last].s, list->jobs[last].f);
        return;
    }
    displaySol(list, P, P[last]);
    printf(",(%d;%d)",list->jobs[last].s, list->jobs[last].f);
}