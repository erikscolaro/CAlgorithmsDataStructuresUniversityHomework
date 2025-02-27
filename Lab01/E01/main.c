#include "stdio.h"
#include "string.h"
#include "ctype.h"

char *cercaRegexp(char *src, char *regexp);

int main() {
    char src[100]="Ai fini dell'esercizio si consideri di valutare solamente stringhe composte da caratteri.";
    char regexp[10]="[aei]oto";
    char *i;

    //printf("Inserisci la stringa da cercare:");
    //scanf("%9s",&regexp);

    i=cercaRegexp(src, regexp);

    printf("Posizione: %i", i!=NULL? (i-src)/sizeof(char):-1);

    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    int match=0, nr_match=0, regexpLen=strlen(regexp), i=0;
    char *src_i=src;
    const char *regexp_b=regexp;
    while (*src != '\0'){
        match=0; i=0;

        if (*regexp=='\0'){
            match= 2;
        } else if (*regexp==*src){
            match= 1; regexp++;
        } else if (*regexp=='.'){
            match= 1; regexp++;
        } else if (*regexp=='\\'){
            if (*(regexp+1)=='a'){
                if (islower(*src)){
                    match= 1; regexp+=2;
                } else {
                    match=0;
                }
            } else if (*(regexp+1)=='A'){
                if ( isupper(*src)){
                    match= 1; regexp+=2;
                } else {
                    match=0;
                }
            } else {
                match= -1;
            }
        } else if (*regexp=='['){
            if (*(regexp+1)=='^'){
                i=2;
                match=1;
                while (*(regexp+i)!=']'){
                    if (*(regexp+i)==*src){
                        match=0;
                    }
                    i++;
                }
                if (match==1) regexp+=i+1;
            } else {
                i=1;
                while (*(regexp+i)!=']'){
                    if (*(regexp+i)==*src){
                        match=1;
                    }
                    i++;
                }
                if (match==1) regexp+=i+1;
            }
        }

        if (match==0) regexp=regexp_b;

        switch (match) {
            case 0: //ricomincia
                nr_match = 0;
                break;
            case 1: //continua
                if (nr_match==0) src_i=src;
                nr_match++;
                break;
            case 2: //risultato
                return src_i;
            default:
                printf("Errore nella formattazione.");
                return NULL;
        }
        src++;
    }
    return NULL;
}
