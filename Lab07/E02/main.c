#include <stdio.h>
#include <stdlib.h>
#include "elements.h"
#include "program.h"

#define DD 9
#define DP 30
#define DIAGS 3
#define MAX_EL_IN_DIAG 5

/*a volte vuole essere riavviato alcune volte per funzionare*/

int main() {
    elements_t list= startList("..//elementi.txt");
    program_t program = bestProgram(DIAGS, MAX_EL_IN_DIAG, DD, DP, list);
    printProgram(program,list,stdout);

    deleteProgram(program);
    deleteList(list);

    return 0;
}

/*l'algoritmo calcola la diagonale con il migliore voto in base ad una certa difficolt°;
 * salva tale diagonale in vettore di diagonali ordinato per difficoltà della diagonale crescente;
 * calcola tutte le disposizioni con ripetizione dei valori di difficoltà e tramite questi valori
 * recupera i dati della diagonale dal vettore sopra descritto. Infine, se il programma trovato ha
 * valore maggiore del valore del programma precedente, lo salva. ritorna puntatore al programma,
 * stampato poi da printprogram.
 *
 * Controlli di precedenza, concordanza delle direzioni, elemento finale sono fatti dalla funzione
 * ricorsiva che calcola la diagonale miglire all'interno del modulo diagonal.
 *
 * Controlli di difficoltà, punteggio, bonus, e tutti quelli non ancora specificati
 * sono fatti nel modulo program da funzioni implementate distintamente e nascoste al main.
 * */