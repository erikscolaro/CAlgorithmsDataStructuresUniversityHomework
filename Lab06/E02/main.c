#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int z, s, r, t;
}set_info;

typedef struct{
    int nr_collections;
    set_info *sets ;
} info_file;

info_file readFile();

int setLen(set_info set);

void chainCreate(set_info set);

void fZ(set_info set, char *sol, int i);
void fR(set_info set, char *sol, int i);
void fS(set_info set, char *sol, int i);
void fT(set_info set, char *sol, int i);

int main() {
    info_file sets_list= readFile();

    for (int i=0; i < sets_list.nr_collections; i++) chainCreate(sets_list.sets[i]);

}

info_file readFile(){
    info_file temp;

    FILE *fp;
    fp = fopen("..//very_easy_test_set.txt", "r");
    fscanf(fp, "%d", &temp.nr_collections);

    temp.sets=malloc(temp.nr_collections*sizeof(set_info));

    for (int i=0; i<temp.nr_collections; i++){
        fscanf(fp, "%d %d %d %d", &(temp.sets[i].z), &(temp.sets[i].s), &(temp.sets[i].r), &(temp.sets[i].t));
    }

    fclose(fp);

    return temp;
}

int setLen(set_info set){
    return set.z+set.s+set.r+set.t;
}

void chainCreate(set_info set){
    int nr_elmements= setLen(set);
    char *sol=calloc(nr_elmements+1, sizeof(char));
    char *solZ=calloc(nr_elmements+1, sizeof(char));
    char *solS=calloc(nr_elmements+1, sizeof(char));
    char *solR=calloc(nr_elmements+1, sizeof(char));
    char *solT=calloc(nr_elmements+1, sizeof(char));

    fZ(set, solZ, 0);

    //nota: per fare sta cosa posso ausare le verie FX solo come wapper, e riciclare la soluizoine dell'esercizio 4 per altricalcoli dopo aver impostato il primo valore a quello desiderato

    //inizializza una stringa temporanea
    for (int i=0;i<nr_elmements; i++) {
        //dai in pasto la stinga temporanea a una di queste funzioni
        //se la lunghezza è maggiore di quella ufficiale, allora sovrascrivi. Altrimenti, fermati(?)
    }

    fS(set, solS, 0);
    fR(set, solR, 0);
    fT(set, solT, 0);

    //dopo aver calcolato tutte le soluzioni parziali, scrivi l'algoritmo che le usa per trovare la soluzione vera

}

void fZ(set_info set, char *sol, int i){

}

void fR(set_info set, char *sol, int i){}

void fS(set_info set, char *sol, int i){}

void fT(set_info set, char *sol, int i){}
