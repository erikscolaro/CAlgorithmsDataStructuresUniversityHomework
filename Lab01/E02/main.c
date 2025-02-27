#include <stdio.h>
#include <string.h>

#define MAX_STOP 1000
#define MAX_CHAR 30
#define MAX_COMMAND 20
#define NOME_LOG "..//log.txt"

typedef enum {
    r_date,
    r_partenza,
    r_capolinea,
    r_ritardo,
    r_ritardo_tot,
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
    int ritardo;
} info;

//prototipi funzioni

comando_e leggiComando(void);

void leggiLog(info fermate[], int *numero_log);

void menuComando(info fermate[], comando_e comando, int numero_log);

void f_date(info fermate[], int numero_log, int ritardo);

void f_partenze_o_arrivi(info fermate[], int numero_log, int opzione);

void fRitardo_tot(info fermate[], int numero_log);

void pulisciBuffer(void);

//*******************PRINCIPALE******************
int main() {
    //dichiarazione variabili
    comando_e comando_N = 0;
    int numero_log = 0;
    info fermate[MAX_STOP];

    leggiLog(fermate, &numero_log);

    do {
        comando_N = leggiComando();
        menuComando(fermate, comando_N, numero_log);
    } while (comando_N != r_fine);

    return 0;
}

//***************DEF FUNZIONI******************

void leggiLog(info fermate[], int *numero_log) {
    FILE *fp;
    fp = fopen(NOME_LOG, "r");
    fscanf(fp, "%d", numero_log);
    for (int i = 0; *numero_log > i; i++)
        fscanf(fp, "%s%s%s%s%s%s%d",
               fermate[i].codice_tratta,
               fermate[i].nome_partenza,
               fermate[i].nome_destinazione,
               &fermate[i].data,
               &fermate[i].ora_partenza,
               &fermate[i].ora_arrivo,
               &fermate[i].ritardo);
    fclose(fp);
}

comando_e leggiComando(void) {
    char lista_comandi[r_fine + 1][MAX_COMMAND] = {
            "date",
            "partenze",
            "capolinea",
            "ritardo",
            "ritardo_tot",
            "esci"
    };
    char cmd[MAX_COMMAND];
    printf("Digitare comando a scelta tra i disponibili:\n"
           "- date yyyy/mm/gg yyyy/mm/gg;\n"
           "- partenze <nome_partenza>;\n"
           "- capolinea <nome_destinazione>;\n"
           "- ritardo yyyy/mm/gg yyyy/mm/gg;\n"
           "- ritardo_tot <codice tratta>;\n"
           "- esci.\n\n");
    scanf("\n%s", cmd);
    strlwr(cmd);
    for (int i = 0; i <= r_fine; i++) {
        if (strcmp(cmd, lista_comandi[i]) == 0) {
            return i;
        }
    }
    return -1;
}

void menuComando(info fermate[], comando_e comando, int numero_log) {
    switch (comando) {
        case r_date:
            f_date(fermate, numero_log, 0);
            break;
        case r_partenza:
            f_partenze_o_arrivi(fermate, numero_log, 0);
            break;
        case r_capolinea:
            f_partenze_o_arrivi(fermate, numero_log, 1);
            break;
        case r_ritardo:
            f_date(fermate, numero_log, 1);
            break;
        case r_ritardo_tot:
            fRitardo_tot(fermate, numero_log);
            break;
        case r_err:
            printf("Inserito commando errato. Riprova.");
        default:
            break;
    }
    pulisciBuffer();
    puts("");
}

void f_date(info fermate[], int numero_log, int ritardo) {
    char data_iniziale[MAX_CHAR], data_finale[MAX_CHAR];
    if (scanf("%s %s", data_iniziale, data_finale) == 2) {
        for (int i = 0; i < numero_log; i++) {
            if (strcmp(data_iniziale, fermate[i].data) <= 0 && strcmp(fermate[i].data, data_finale) <= 0 && ritardo == 0
                ? 1 : (fermate[i].ritardo != 0)) {
                printf("%s %s %s %s %s %s\n",
                       fermate[i].codice_tratta,
                       fermate[i].nome_partenza,
                       fermate[i].nome_destinazione,
                       fermate[i].data,
                       fermate[i].ora_partenza,
                       fermate[i].ora_arrivo);
            }
        }
    } else {
        printf("Non hai inserito tutti i dati richiesti. Riprova.\n");
        pulisciBuffer();
    }
}

void f_partenze_o_arrivi(info fermate[], int numero_log, int opzione) {
    char nome_stazione[MAX_CHAR];
    int notFound = 0;
    scanf("%s", nome_stazione);
    printf("Tratte con %s %s:\n", opzione == 0 ? "partenza" : "capolinea", nome_stazione);
    for (int i = 0; i < numero_log; i++) {
        if (strcmp(opzione == 0 ? fermate[i].nome_partenza : fermate[i].nome_destinazione, nome_stazione) == 0) {
            printf("%s %s %s\n",
                   fermate[i].codice_tratta,
                   fermate[i].data,
                   fermate[i].ora_partenza);
        } else {
            notFound++;
        }
    }
    if (notFound == numero_log) {
        printf("Nessuna corrispondenza trovata. %s non presente nel database. Riprova.\n",
               opzione == 0 ? "Partenza" : "Capolinea");
    }
    puts("");
}

void fRitardo_tot(info fermate[], int numero_log) {
    char codice_tratta[MAX_CHAR];
    int ritardo_tot = 0;
    if (scanf("%s", codice_tratta) == 1) {
        for (int i = 0; i < numero_log; i++) {
            if (strcmp(fermate[i].codice_tratta, codice_tratta) == 0) {
                ritardo_tot += fermate[i].ritardo;
            }
        }
        printf("Ritardo totale della tratta %s: %d minuti.\n",codice_tratta, ritardo_tot );
    } else { printf("Hai dimenticato di inserire il codice tratta. Riprova.\n"); }
}

void pulisciBuffer(void) {
    while (getc(stdin) != '\n') {}
}