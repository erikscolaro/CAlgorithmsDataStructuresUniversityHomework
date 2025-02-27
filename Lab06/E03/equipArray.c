#include "equipArray.h"

struct equipArray_s{
    int inUse;
    int array[EQUIP_SLOT]; //riferimento tramite indici a invArray
};

/* creatore e disruttore */
equipArray_t equipArray_init(){
    equipArray_t temp;
    temp=calloc(1, sizeof(struct equipArray_s));
    temp->inUse=0;
    return temp;
}

void equipArray_free(equipArray_t equipArray){
    free(equipArray);
}

/* quanti equipaggiamenti sono in uso */
int equipArray_inUse(equipArray_t equipArray){
    return equipArray->inUse;
}

/* scrittura su file */
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    for (int i=0; i< equipArray_inUse(equipArray); i++){
        fprintf(fp, "\t%d.", i+1);
        invArray_printByIndex(fp, invArray, equipArray_getEquipByIndex(equipArray, i));
    }
}

/* modifica equipaggiamento scegliendo un oggetto da inventario */
void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    int i_equipArray= equipArray_inUse(equipArray);

    printf("Inventario attivo del personaggio:\n");
    equipArray_print(stdout, equipArray, invArray);

    if (equipArray_inUse(equipArray)==EQUIP_SLOT){
        do{
            printf("Digita numero elemento da sostituire: ");
            scanf("%d", &i_equipArray);
        }while (i_equipArray<1 || i_equipArray>EQUIP_SLOT);
        i_equipArray--;
        equipArray->inUse--;
    }

    int i_invArr;

    invArray_print(stdout, invArray);
    do{
        printf("Scegli il nuovo equipaggiamento: ");
        scanf("%d", &i_invArr);
    }while(i_invArr<0 || i_invArr> invArray_getMaxindex(invArray));

    equipArray->array[i_equipArray]=i_invArr-1;
    equipArray->inUse++;
}

/* torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray */
int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    if (0<=index && index <=EQUIP_SLOT-1) return equipArray->array[index];
    else return -1;
}
