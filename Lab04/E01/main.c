#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n_val;
    int n_con;
    int *val;
    int **con;
} grafo_t;

int checkVertexCover(grafo_t grafo, int *sol, int posm);

int powerset(grafo_t grafo, int *sol);

int powerset_r(grafo_t grafo, int *sol, int j, int pos, int start);


int main() {
    FILE *fp;
    fp = fopen("..//grafo.txt", "r");

    grafo_t grafo;
    int *sol, n=1;

    fscanf(fp, "%d %d", &(grafo.n_val), &(grafo.n_con));

    sol = (int *) malloc(sizeof(int) * grafo.n_val);
    grafo.val = (int *) malloc(sizeof(int) * grafo.n_val);
    for (int n = 0; n < grafo.n_val; n++) (grafo.val)[n] = n;

    grafo.con = (int **) malloc(sizeof(int *));
    for (int i = 0; i < grafo.n_con; i++) {
        (grafo.con)[i] = (int *) malloc(sizeof(int) * 2);
        fscanf(fp, "%d %d", &(grafo.con[i][0]), &(grafo.con[i][1]));
    }
    fclose(fp);

    n= powerset(grafo, sol);

    printf("Sono stati trovati %d possibili vertex cover.\n", n);

    return 0;
}

//l'idea è usare l'algoritmo del powerset per generare tutte le partizioni
// dell'insieme dei nodi per poi contollare ad uno ad uno se corrispondono
// ai criteri del vertex cover con la funzione di checkVertexCover.


int powerset(grafo_t grafo, int *sol) {//int n, int *val, int *sol
    int cnt = 0; //escludo l'insieme vuoto che non è interessante
    printf("Elenco vertici dei possibili vertex cover:\n");
    for (int j = 1; j <= grafo.n_val; j++) {
        cnt += powerset_r(grafo, sol, j, 0, 0);
    }
    return cnt;
}

int powerset_r(grafo_t grafo, int *sol, int j, int pos, int start) {
    int cnt = 0, i;
    if (pos >= j) {
        if (checkVertexCover(grafo, sol, j) == 1) {
            printf("{ ");
            for (i = 0; i < j; i++) {
                printf("%d ", sol[i]);
            }
            printf("}\n");
            return 1;
        } else {
            return 0;
        }
    }
    for (i = start; i < grafo.n_val; i++) {
        sol[pos] = grafo.val[i];
        cnt += powerset_r(grafo, sol, j, pos + 1, i + 1);
    }
    return cnt;
}

int checkVertexCover(grafo_t grafo, int *sol, int posm) {
    int check;
    for (int i = 0; i < grafo.n_con; i++) { //considero la iesima tupla rappresentante la connessione uvi
        check = 0;
        for (int j = 0; j < posm; j++) { //considero il jesimo elemento del vettore pos
            if (grafo.con[i][0] == sol[j] || grafo.con[i][1] == sol[j]) {
                check++;
            }
        }
        if (check == 0)
            return 0; //caso in cui gli elementi della soluzione non sono presenti nell'iesima connessione del vc
    }
    return 1;
}