#include "pg.h"

/* lettura e scrittura su file */
int pg_read(FILE *fp, pg_t *pgp){
    if (fscanf(fp, "%s %s %s", pgp->cod, pgp->nome, pgp->classe)==3) {
        pgp->equip = equipArray_init();
        stat_read(fp, &(pgp->b_stat));
        stat_cpy(&(pgp->eq_stat), &(pgp->b_stat));
        return 1;
    } else {
        return 0;
    }
}

/* non essendo struct dinamica, pulisce chiamando il distruttire di equipArray */
void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    fprintf(fp, "%s %s %s ", pgp->cod, pgp->nome, pgp->classe);
    stat_print(fp, &(pgp->eq_stat), MIN_STAT);
    putc('\n', fp);
    equipArray_print(fp, pgp->equip, invArray);
}

/* modifica personaggio aggiungendo/togliendo un equipaggiamento selezionato da inventario:
di fatto e' sufficiente chiamare l'opportuna funzione dal modulo equipArray */
void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    equipArray_update(pgp->equip, invArray);
    stat_t temp;
    pgp->eq_stat=pgp->b_stat;

    for (int i=0; i< equipArray_inUse(pgp->equip); i++){
        temp = *inv_getStat(invArray_getByIndex(invArray, equipArray_getEquipByIndex(pgp->equip,i)));
        pgp->eq_stat.hp+=temp.hp;
        pgp->eq_stat.spr+=temp.spr;
        pgp->eq_stat.atk+=temp.atk;
        pgp->eq_stat.def+=temp.def;
        pgp->eq_stat.mag+=temp.mag;
        pgp->eq_stat.mp+=temp.mp;
    }
}