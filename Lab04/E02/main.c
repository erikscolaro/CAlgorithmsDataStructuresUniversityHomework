#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAR 50

typedef struct{
    int day;
    int month;
    int year;
} data_t;

typedef struct node *link;
struct node{
    int key;
    data_t born;
    char name[MAX_CHAR + 1];
    char surname[MAX_CHAR + 1];
    char street[MAX_CHAR + 1];
    char city[MAX_CHAR + 1];
    int cap;
    link next;
};

//funzioni
void InsElement(link head, link new);
void PrintScreen(link temp);

int DataComparison(data_t data1, data_t data2);

link KeyDel(link prev);
link KeyScan(link head, char key[6]);
link DateScan(link head, data_t date_in, data_t date_fin);

//wrapper
void NewElementKeyboard(link head);
void NewElementFile(link head);
void PrintOut(link head);

int main() {
    link head, temp;
    int op=-1;
    char t_key[6];
    data_t date_in, date_fin;
    head = malloc(sizeof (struct node));
    (head->next)=NULL;

    //il primo elemento della lista non verrà considerato.

    do{
        printf("Seleziona comando:\n"
               "1 -> k_read\n"
               "2 -> f_read\n"
               "3 -> key_find\n"
               "4 -> key_del\n"
               "5 -> data_del\n"
               "6 -> PrintOut\n"
               "7 -> exit\n");
        for (scanf("%d", &op);op<1 || op>7;scanf("%d", &op)) printf("Il comando selezionato non e' disponibile, riprova.\n");

        switch (op){
            case 1:
                NewElementKeyboard(head);
                //OrderByData(head);
                break;
            case 2:
                NewElementFile(head);
                break;
            case 3:
                printf("Digita il codice da cercare:\t");
                scanf("%5s", t_key);
                temp= KeyScan(head, t_key);
                if (temp!=NULL) PrintScreen(temp->next);
                else PrintScreen(temp);
                break;
            case 4:
                printf("Digita il codice della persona da cancellare:\t");
                scanf("%5s", t_key);
                temp=KeyDel(KeyScan(head, t_key)); //restituisce l'elemento prima
                PrintScreen(temp);
                if (temp!=NULL){
                    free(temp);
                }
                break;
            case 5:
                printf("Digita il valore della data iniziale (formato: <gg/mm/aaaa>):\n");
                scanf("%d/%d/%d", &(date_in.day), &(date_in.month), &(date_in.year));
                printf("Digita il valore della data finale (formato: <gg/mm/aaaa>):\n");
                scanf("%d/%d/%d", &(date_fin.day), &(date_fin.month), &(date_fin.year));

                for (temp=DateScan(head, date_in, date_fin); temp!=NULL; temp = DateScan(head, date_in, date_fin)){
                    temp= KeyDel(temp);
                    PrintScreen(temp);
                }
                break;
            case 6:
                PrintOut(head); //da cambiare con scrittura su file
                break;
            case 7:
                exit(1);
            default:exit(1);
        }

    } while (op!=7);

    return 0;
}

link NewNode(){
    link newnode;
    newnode=malloc(sizeof (struct node));
    return newnode;
}

void NewElementKeyboard(link head){
    link temp;
    char t_key[6];
    temp=(link) malloc(sizeof(struct node));

    printf("Inserisci i dati del nuovo soggetto:\n<codice> <nome> <cognome> <data_di_nascita gg/mm/aaaa> <via> <citta'> <cap>\n");
    scanf("%s%s%s%d/%d/%d%s%s%d", t_key, temp->name, temp->surname, &(temp->born.day), &(temp->born.month), &(temp->born.year), temp->street, temp->city, &(temp->cap));

    t_key[0]='0';
    temp->key=strtol(t_key, NULL , 10);

    InsElement(head, temp);
}

void NewElementFile(link head){
    char dir[MAX_CHAR+1],t_key[6];
    link temp;
    FILE *fp;

    printf("Specifica il nome del file:\n");
    scanf("%s", dir);

    fp= fopen(dir,"r");

    if (fp!=NULL) {
        while (!feof(fp)){
            temp = NewNode();
            fscanf(fp, "%s%s%s%d/%d/%d%s%s%d", t_key, temp->name, temp->surname, &(temp->born.day),&(temp->born.month), &(temp->born.year), temp->street, temp->city, &(temp->cap));
            t_key[0]='0';
            temp->key=strtol(t_key, NULL , 10);
            InsElement(head,temp);
        }
        fclose(fp);
    } else {
        printf("Il file non è stato trovato. Riprova. \n");
    }

}

int DataComparison(data_t data1, data_t data2){ //data1 > data2? 1=vero, 0=uguali, -1=falso
    if (data1.year > data2.year){
        return 1;
    } else if (data1.year == data2.year){
        if (data1.month > data2.month){
            return 1;
        } else if (data1.month == data2.month){
            if (data1.day > data2.day){
                return 1;
            } else if (data1.day == data2.day){
                return 0;
            }
        }
    }

    return -1;
}

void InsElement(link head, link new){
    link temp;
    int ok=0;

    if (head->next==NULL) {
        temp = head->next;
        head->next = new;
        new->next = temp;
    } else {
        temp=head;
        while (ok==0){
            if (temp->next!=NULL && DataComparison(new->born, temp->next->born)>=0){
                temp=temp->next;
            } else {
                new->next=temp->next;
                temp->next=new;
                ok++;
            }
        }
    }
}

void PrintOut(link head){
    link temp;
    temp=head->next;

    FILE *fout;
    fout=fopen("..//anag0.txt", "w");

    while (temp!=NULL){
        fprintf(fout,"A%.4d %s %s %.2d/%.2d/%.4d %s %s %.5d\n", temp->key, temp->name, temp->surname, temp->born.day, temp->born.month, temp->born.year, temp->street, temp->city, temp->cap);
        temp=temp->next;
    }

    fclose(fout);
}

void PrintScreen(link temp){
    if (temp!=NULL) printf("A%.4d %s %s %.2d/%.2d/%.4d %s %s %.5d\n", temp->key, temp->name, temp->surname, temp->born.day, temp->born.month, temp->born.year, temp->street, temp->city, temp->cap);
    else printf("Elemento non trovato.\n");
}

link KeyDel(link prev){
    if (prev==NULL) return NULL;
    link temp=prev->next;
    if (temp->next!=NULL){
        prev->next=temp->next;
    } else {
        prev->next=NULL;
    }
    return temp;
}

link KeyScan(link head, char key[]){
    key[0]='0';
    link prev=head;
    int d_key=strtol(key, NULL, 10);

    while (prev->next!=NULL){ //la lista non è vuota
        if (prev->next->key == d_key){
            return prev;
        } else {
            prev=prev->next;
        }
    }

    return NULL;
}

link DateScan(link head, data_t date_in, data_t date_fin){
    link prev=head;

    while (prev->next!=NULL){ //la lista non è vuota
        if (DataComparison(prev->next->born,date_in)>=0 && DataComparison(date_fin, prev->next->born)>=0){
            return prev;
        } else if (DataComparison(date_fin, prev->next->born)==-1){
            return NULL;
        } else {
            prev=prev->next;
        }
    }

    return NULL;
}