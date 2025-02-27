#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHAR 30
#define NOME_LOG "..//corse.txt"

typedef enum {
    stampa_log,
    ord_data,
    ord_codice,
    ord_part,
    ord_arr,
    ric_part,
    new_file,
    r_fine,
    r_err = -1
} comando_e;

typedef struct {
    char codice_tratta[MAX_CHAR];
    char nome_partenza[MAX_CHAR];
    char nome_destinazione[MAX_CHAR];
    char data[MAX_CHAR];
    char ora_partenza[MAX_CHAR];
    char ora_arrivo[MAX_CHAR];
    char ritardo[MAX_CHAR];
} info;

//prototipi funzioni

comando_e leggiComando(void);

int leggiLog(info ***fermate, char nome_log[MAX_CHAR]);

void menuComando(info ***ptr, info ***p_ord_cod, info ***p_ord_data, info ***p_ord_part, info ***p_ord_dest, comando_e comando, int *numero_log);

void collega_log(info **fermate, info ***ptr, int n);

void f_stampa_log(info **ptr, int maxi);

void f_ric(info **ptr, int numero_log);

unsigned long long int conv_data(info *ptr);

int dic_search(info **ptr, int l, int r, char nome[]);

void f_ord(info *ptr[], int op, int numero_log);

void init_ptrs(int *nlog, info ***ptr0,info ***ptr1,info ***ptr2,info ***ptr3,info ***ptr4, char nome_file[MAX_CHAR]);

//*******************PRINCIPALE******************
int main() {
    //dichiarazione variabili
    comando_e comando_N = 0;
    int numero_log = 0;
    info **fermate, **p_ord_data,**p_ord_cod,**p_ord_part,**p_ord_dest;

    init_ptrs(&numero_log, &fermate,&p_ord_cod,&p_ord_data,&p_ord_part,&p_ord_dest, NOME_LOG);

    do {
        comando_N = leggiComando();
        menuComando(&fermate ,&p_ord_cod, &p_ord_data, &p_ord_part, &p_ord_dest, comando_N, &numero_log);
    } while (comando_N != r_fine);

    return 0;
}

//***************DEF FUNZIONI******************

void init_ptrs(int *nlog, info ***ptr0,info ***ptr1,info ***ptr2,info ***ptr3,info ***ptr4, char nome_file[MAX_CHAR]){
    if (*nlog!=0){
        for (int i=0; i<*nlog; i++){
            free((*ptr0)[i]);
        }
    }

    *nlog=leggiLog(ptr0, nome_file);
    collega_log(*ptr0, ptr1, *nlog);
    collega_log(*ptr0, ptr2, *nlog);
    collega_log(*ptr0, ptr3, *nlog);
    collega_log(*ptr0, ptr4, *nlog);
}

int dic_search(info **ptr, int l, int r, char nome[]){
    int  m=l+(r-l)/2;
    char temp[MAX_CHAR];
    strcpy(temp, ptr[m]->nome_partenza);
    strlwr(temp);
    if (memcmp(nome, temp, strlen(nome))==0){
        return m;
    } else if (memcmp(nome, temp, strlen(nome))>0){
        return dic_search(ptr, m+1, r, nome);
    } else {
        return dic_search(ptr, l, m-1, nome);
    }
}

unsigned long long int conv_data(info *ptr){
    int yyyy,mm,gg,hh,ii,ss;
    sscanf(ptr->data,"%d/%d/%d",&yyyy,&mm,&gg);
    sscanf(ptr->ora_partenza,"%d:%d:%d",&hh,&ii,&ss);
    return ss+100*ii+hh*10000+gg*1000000+mm*100000000+yyyy*10000000000;
}

int leggiLog(info ***fermate, char nome_log[MAX_CHAR]) {
    FILE *fp;
    fp = fopen(nome_log, "r");
    int i=0, maxn;
    fscanf(fp,"%d", &maxn);

    *fermate=(info **) malloc(maxn*sizeof (info *));

    if (*fermate == NULL){
        printf("Errore di allocazione\n");
        exit(1);
    }

    (*fermate)[i]=(info *) malloc(sizeof (info));

    if ((*fermate)[i] == NULL){
        printf("Errore di allocazione\n");
        exit(1);
    }

    while (fscanf(fp, "%s%s%s%s%s%s%s",
                  (*fermate)[i]->codice_tratta,
                  (*fermate)[i]->nome_partenza,
                  (*fermate)[i]->nome_destinazione,
                  (*fermate)[i]->data,
                  (*fermate)[i]->ora_partenza,
                  (*fermate)[i]->ora_arrivo,
                  (*fermate)[i]->ritardo)==7){
        i++;
        (*fermate)[i]=(info *) malloc(sizeof (info));
        if ((*fermate)[i] == NULL){
            printf("Errore di allocazione\n");
            exit(1);
        }
    }
    fclose(fp);

    return maxn;
}

void collega_log(info **fermate, info ***ptr, int n){
    *ptr=(info **) malloc(n*sizeof (info *));

    if (*ptr == NULL){
        printf("Errore di allocazione\n");
        exit(1);
    }

    int i=0;
    while (i<n){
        (*ptr)[i]=&(*(fermate[i]));
        i++;
    }
}

comando_e leggiComando(void) {
    int i=-1;
    printf("Digitare comando a scelta tra i disponibili:\n"
           "1 stampa contenuti del log;\n"
           "2 ordinamento del vettore per data, e a parità di date per ora;\n"
           "3 ordinamento del vettore per codice di tratta;\n"
           "4 ordinamento del vettore per stazione di partenza;\n"
           "5 ordinamento del vettore per stazione di arrivo;\n"
           "6 ricerca di una tratta per stazione di partenza;\n"
           "7 acquisisci nuovo file;\n"
           "8 esci.\n\n");

    if (scanf("%d", &i)==1) return i-1;
    return -1;
}

void menuComando(info ***ptr, info ***p_ord_cod, info ***p_ord_data, info ***p_ord_part, info ***p_ord_dest, comando_e comando, int *numero_log) {

    switch (comando) {
        case stampa_log:
            f_stampa_log(*ptr, *numero_log);
            break;
        case ord_data:
            f_ord(*p_ord_data, 0, *numero_log);
            f_stampa_log(*p_ord_data, *numero_log);
            break;
        case ord_codice:
            f_ord(*p_ord_cod, 1, *numero_log);
            f_stampa_log(*p_ord_cod, *numero_log);
            break;
        case ord_part:
            f_ord(*p_ord_part, 2, *numero_log);
            f_stampa_log(*p_ord_part, *numero_log);
            break;
        case ord_arr:
            f_ord(*p_ord_dest, 3, *numero_log);
            f_stampa_log(*p_ord_dest, *numero_log);
            break;
        case ric_part:
            f_ric(*p_ord_part, *numero_log); //0 lineare, 1 dicotomica
            break;
        case new_file:
            printf("Inserisci nome del nuovo file:\t");
            char file_att[MAX_CHAR];
            scanf("%s", file_att);
            printf("Leggo il file %s ...\t", file_att);
            init_ptrs(numero_log, ptr,p_ord_cod,p_ord_data,p_ord_part,p_ord_dest, file_att);
            printf("Lettura completata con successo.\n\n");
            break;
        case r_fine:
            exit(1);
        case r_err:
            printf("Inserito commando errato. Riprova.");
            break;
        default:
            break;
    }
}

void f_stampa_log(info **ptr, int maxi){
    for (int i=0; i<maxi;i++){
        printf("%s %s %s %s %s %s %s\n", ptr[i]->codice_tratta, ptr[i]->nome_partenza, ptr[i]->nome_destinazione, ptr[i]->data, ptr[i]->ora_arrivo, ptr[i]->ora_partenza, ptr[i]->ritardo);
    } puts("");
}

void f_ord(info *ptr[], int op, int numero_log){
    for(int i=1; i < numero_log; i++){
        info *tmp = ptr[i];
        int j = i-1;

        switch (op) {
            case 0:
                while(j>=0 && conv_data(ptr[j])> conv_data(tmp)){
                    ptr[j + 1] = ptr[j];
                    j--;
                }
                break;
            case 1:
                while(j>=0 && strcmp(ptr[j] -> codice_tratta, tmp -> codice_tratta) > 0){
                    ptr[j + 1] = ptr[j];
                    j--;
                }
                break;
            case 2:
                while(j>=0 && strcmp(ptr[j] -> nome_partenza, tmp -> nome_destinazione) > 0){
                    ptr[j + 1] = ptr[j];
                    j--;
                }
                break;
            case 3:
                while(j>=0 && strcmp(ptr[j] -> nome_destinazione, tmp -> nome_destinazione) > 0){
                    ptr[j + 1] = ptr[j];
                    j--;
                }

        }
        ptr[j + 1] = tmp;
    }
}

void f_ric(info **ptr, int numero_log){
    char nome[MAX_CHAR], temp[MAX_CHAR];
    int k, op=0;
    printf("\nInserisci parte o tutto il nome della stazione di partenza:");
    scanf("%s", nome);
    printf("\n0 per ricerca lineare, 1 per dicotomica:");
    scanf("%d", &op);
    strlwr(nome);
    if (op==0){
        for (int i=0;i<numero_log;i++){
            strcpy(temp,ptr[i]->nome_partenza );
            strlwr(temp);
            if (memcmp(nome, temp, strlen(nome))==0){
                printf("%s %s %s %s %s %s %s\n", ptr[i]->codice_tratta, ptr[i]->nome_partenza, ptr[i]->nome_destinazione, ptr[i]->data, ptr[i]->ora_arrivo, ptr[i]->ora_partenza, ptr[i]->ritardo);
            }
        }
    } else {
        f_ord(ptr, 2, numero_log);
        k=dic_search(ptr, 0, numero_log-1, nome);
        printf("%s %s %s %s %s %s %s\n", ptr[k]->codice_tratta, ptr[k]->nome_partenza, ptr[k]->nome_destinazione, ptr[k]->data, ptr[k]->ora_arrivo, ptr[k]->ora_partenza, ptr[k]->ritardo);
    }
    puts("");
}