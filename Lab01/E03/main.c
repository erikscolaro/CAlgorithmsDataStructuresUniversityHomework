#include <stdio.h>
#include <string.h>

#define MAX_STOP 1000
#define MAX_CHAR 30
#define NOME_LOG "..//corse.txt"

typedef enum {
    stampa_log,
    ord_data,
    ord_codice,
    ord_part,
    ord_arr,
    ric_part,
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

void leggiLog(info fermate[], int *numero_log);

void menuComando(info **ptr, comando_e comando, int numero_log);

void collega_log(info fermate[], info **ptr, int n);

void f_stampa_log(info **ptr);

void f_ord(info **ptr, int op, int numero_log);

void f_ric(info **ptr, int numero_log);

unsigned long long int conv_data(info *ptr);

int dic_search(info **ptr, int l, int r, char nome[]);

//*******************PRINCIPALE******************
int main() {
    //dichiarazione variabili
    comando_e comando_N = 0;
    int numero_log = 0;
    info fermate[MAX_STOP];
    info *p_fermate[MAX_STOP];

    leggiLog(fermate, &numero_log);
    collega_log(fermate, p_fermate, numero_log);


    do {
        comando_N = leggiComando();
        menuComando(p_fermate, comando_N, numero_log);
    } while (comando_N != r_fine);

    return 0;
}

//***************DEF FUNZIONI******************

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

void leggiLog(info fermate[], int *numero_log) {
    FILE *fp;
    fp = fopen(NOME_LOG, "r");
    fscanf(fp, "%d", numero_log);
    for (int i = 0; *numero_log > i; i++) {
        fscanf(fp, "%s%s%s%s%s%s%s",
               fermate[i].codice_tratta,
               fermate[i].nome_partenza,
               fermate[i].nome_destinazione,
               fermate[i].data,
               fermate[i].ora_partenza,
               fermate[i].ora_arrivo,
               fermate[i].ritardo);
    }
        fclose(fp);
}

void collega_log(info fermate[], info **ptr, int n){
    int i=0;
    while (i!=n){
        ptr[i]=&fermate[i];
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
           "7 esci.\n\n");

    if (scanf("%d", &i)==1) return i-1;
    return -1;
}

void menuComando(info **ptr, comando_e comando, int numero_log) {

    switch (comando) {
        case stampa_log:
            f_stampa_log(ptr);
            break;
        case ord_data:
            f_ord(ptr, 0, numero_log);
            break;
        case ord_codice:
            f_ord(ptr, 1, numero_log);
            break;
        case ord_part:
            f_ord(ptr, 2, numero_log);
            break;
        case ord_arr:
            f_ord(ptr, 3, numero_log);
            break;
        case ric_part:
            f_ric(ptr, numero_log); //0 lineare, 1 dicotomica
            break;
        case r_err:
            printf("Inserito commando errato. Riprova.");
        default:
            break;
    }
}

void f_stampa_log(info **ptr){
    int i=0;
    while (ptr[i]!=NULL){
        printf("%s %s %s %s %s %s %s\n", ptr[i]->codice_tratta, ptr[i]->nome_partenza, ptr[i]->nome_destinazione, ptr[i]->data, ptr[i]->ora_arrivo, ptr[i]->ora_partenza, ptr[i]->ritardo);
        i++;
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

