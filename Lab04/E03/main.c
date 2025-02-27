#include <stdio.h>
#include <stdlib.h>

#define DBG 1

int perm_ripet(int pos, char *dist_val, char *sol, int *mark, int n, int n_dist, int count);

void perm_ripet_wrapper(int **data, int n_data);

int check_all(char *sol, int n);

int check_prev_one(char *sol, int i);

int main() {
    int n_trial = 0;
    int **data;
    FILE *fp;

#if DBG == 0
    char nome_file[30];
    printf("Digitare nome file contenente i dati:");
    scanf("%s", nome_file);
    fp=fopen(fp, "r");
#endif
#if DBG == 1
    fp = fopen("..//hard_test_set.txt", "r");
#endif

    fscanf(fp, "%d", &n_trial);

    data = (int **) malloc(sizeof(int *) * n_trial);

    for (int i = 0; i < n_trial; i++) {
        data[i] = (int *) malloc(sizeof(int) * 4);
        if (data[i] == NULL) exit(1);
        fscanf(fp, "%d %d %d %d", &(data[i][0]), &(data[i][1]), &(data[i][2]), &(data[i][3]));
    }

    fclose(fp);

    perm_ripet_wrapper(data, n_trial);

    //simple free
    for (int i = 0; i < n_trial; i++) free(data[i]);
}

int perm_ripet(int pos, char *dist_val, char *sol, int *mark, int n, int n_dist, int ok) {
    int i;
    if (pos >= n /*&& check_all(sol, n) == 1*/) { //disabilitato perchè controllo integrato nel pruning
        for (i = 0; i < n; i++)
            printf("%c ", sol[i]);
        printf("\nNumero di pietre massimo: %d\n\n", n);
        return 1;
    }

    for (i = 0; i < n_dist && ok != 1; i++) {

        if (pos != 0) {
            switch (sol[pos - 1]) {
                case 'z':
                    if (i > 1) return ok;
                    break;
                case 's':
                    if (i<2) i = 2;
                    break;
                case 'r':
                    if (i<2) i = 2;
                    break;
                case 't':
                    if (i > 1) return ok;
                    break;
            }
        }

        if (mark[i] > 0) {
            mark[i]--;
            sol[pos] = dist_val[i];
            ok = perm_ripet(pos + 1, dist_val, sol, mark, n, n_dist, ok);
            mark[i]++;
        }

    }

    return ok;
}

void perm_ripet_wrapper(int **data, int n_data) {
    char dist_val[5] = "zrts";
    char *sol;
    int nr_prez;
    int ok;
    for (int i = 0; i < n_data; i++) {
        ok = 0;
        printf("TEST nr. %d, z=%d, r=%d, t=%d, s=%d\n", i + 1, data[i][0], data[i][1], data[i][2], data[i][3]);
        nr_prez = data[i][0] + data[i][1] + data[i][2] + data[i][3];
        sol = (char *) malloc(sizeof(char) * nr_prez);
        for (int j = nr_prez; ok != 1 && j >= 1; j--) {
            printf("Calcolando per %d elementi...\n", j);
            ok = perm_ripet(0, dist_val, sol, data[i], j, 4, ok);
        }
        free(sol);
    }
}

int check_all(char *sol, int n) {
    int ok = 1; //all'inizio va tutto bene, se viene modificato questo valore allora qualcosa non va
    for (int i = 1; i < n && ok != 0; i++) {
        ok = check_prev_one(sol, i);
    }
    return ok;
}

int check_prev_one(char *sol, int i) {
    if (i != 0) {
        switch (sol[i - 1]) {
            case 'z':
                if (sol[i] == 'z' || sol[i] == 'r') return 1;
                break;
            case 's':
                if (sol[i] == 's' || sol[i] == 't') return 1;
                break;
            case 'r':
                if (sol[i] == 's' || sol[i] == 't') return 1;
                break;
            case 't':
                if (sol[i] == 'z' || sol[i] == 'r') return 1;
                break;
            default:
                break;
        }
        return 0;
    }
    return 1;
}
