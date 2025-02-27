#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 255

typedef struct {
    int ncanzoni;
    char **canzoni_scelte;
} canz_amico;

int princ_molt(int pos, canz_amico **val, char **sol, int n, int cnt);

int main() {
    FILE *fp;
    fp = fopen("..//brani.txt", "r");

    canz_amico **amici;
    int n_amici;
    char t_string[MAXC];
    char **sol;


    fscanf(fp, "%d", &n_amici);
    amici = (canz_amico **) malloc(n_amici * sizeof(canz_amico *));
    if (amici == NULL) exit(1);

    for (int i_amici = 0; i_amici < n_amici; i_amici++) {
        amici[i_amici] = (canz_amico *) malloc(sizeof(canz_amico));
        if (amici[i_amici] == NULL) exit(1);
        fscanf(fp, "%d", &(amici[i_amici]->ncanzoni));
        amici[i_amici]->canzoni_scelte = (char **) malloc(amici[i_amici]->ncanzoni * sizeof(char **));
        if (amici[i_amici]->canzoni_scelte == NULL) exit(1);
        for (int icanzoni = 0; icanzoni < amici[i_amici]->ncanzoni; icanzoni++) {
            fscanf(fp, "%255s", t_string);
            amici[i_amici]->canzoni_scelte[icanzoni] = (char *) malloc(sizeof(char) * strlen(t_string) + 1);
            if (amici[i_amici]->canzoni_scelte[icanzoni] == NULL) exit(1);
            strcpy(amici[i_amici]->canzoni_scelte[icanzoni], t_string);
        }
    }

    sol = (char **) malloc(sizeof(char **) * n_amici);
    if (sol == NULL) exit(1);
    for (int i = 0; i < n_amici; i++) {
        sol[i] = (char *) malloc(sizeof(char) * MAXC);
        if (sol[i] == NULL) exit(1);
    }

    int n_opzioni = princ_molt(0, amici, sol, n_amici, 0);

    printf("Si sono calcolate %d playlist possibili.", n_opzioni);

    //free

    for (int i_amici = 0; i_amici < n_amici; i_amici++) {
        for (int icanzoni = 0; icanzoni < amici[i_amici]->ncanzoni; icanzoni++) {
            free(amici[i_amici]->canzoni_scelte[icanzoni]);
        }
        free(amici[i_amici]->canzoni_scelte);
        free(amici[i_amici]);
    }
    free(amici);

    return 0;
}

int princ_molt(int pos, canz_amico **val, char **sol, int n, int cnt) {
    if (pos >= n) {
        printf("Playlist nr.%d\n", cnt + 1);
        for (int i = 0; i < n; i++) {
            printf("- %d. %s\n", i + 1, sol[i]);
        }
        puts("");
        return ++cnt;
    }

    for (int i = 0; i < val[pos]->ncanzoni; i++) {
        strcpy(sol[pos], val[pos]->canzoni_scelte[i]);
        cnt = princ_molt(pos + 1, val, sol, n, cnt);
    }
    return cnt;
}
