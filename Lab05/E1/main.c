#include <stdio.h>
#include <stdlib.h>

#define DIR "..//att1.txt"

typedef struct {
    int s;
    int f;
} att;

void attSel(int N, att **v);

void comb_sempl(int pos, att **val,int *t_sol, int *sol, int n, int k, int start, int *maxt);

int main() {
    FILE *fp;
    fp=fopen(DIR, "r");
    int nr=0;
    fscanf(fp, "%d", &nr);

    att **v;
    v=(att**) malloc(sizeof (att*)*nr);
    for (int i=0; i<nr; i++){
        v[i]= (att*) malloc(sizeof (att));
        fscanf(fp, "%d %d", &(v[i]->s), &(v[i]->f));
    }

    fclose(fp);

    attSel(nr, v);
    //free to do


    return 0;
}

void attSel(int N, att **v){
    int max=0;
    int *t_sol, *sol;

    t_sol=calloc(N, sizeof (int));

    sol=calloc(N,sizeof (int));
    for (int i=0; i<N; i++){
        sol[i]=-1;
    }

    for (int k=1; k<N; k++){
        comb_sempl(0, v, t_sol, sol, N, k, 0, &max);
    }

    printf("L'insieme che massimizza la somma delle durate e':\n{");
    for (int i=0; i<N && sol[i] != -1; i++){
        printf("%s%d;%d)", i==0?"(":",(",v[sol[i]]->s,v[sol[i]]->f);
    }
    printf("}\ncon somma delle durate pari a %d.\n", max);

    free(sol);
}

void comb_sempl(int pos, att **val, int *t_sol, int *sol, int n, int k, int start, int *maxt) {
    int i; int time=0;
    if (pos >= k) {
        for (int j=0; j<k; j++){
            time+= (val[t_sol[j]]->f - val[t_sol[j]]->s);
        }
        if (time > (*maxt)){
            *maxt=time;
            for (int j=0; j<k; j++){
                sol[j]=t_sol[j];
            }
        }
        return;
    }
    for (i=start; i<n; i++) {
        if (pos==0 || (val[t_sol[pos-1]]->f <= val[i]->s || val[t_sol[pos-1]]->s >= val[i]->f)){
            t_sol[pos] = i;
            comb_sempl(pos + 1, val, t_sol, sol, n, k, i + 1, maxt);
        }
    }
    return;
}