#include "inv.h"

/* funzioni di input/output delle statistiche */
void stat_read(FILE *fp, stat_t *statp){
    fscanf(fp, "%d %d %d %d %d %d", &(statp->hp), &(statp->mp), &(statp->atk), &(statp->def), &(statp->mag), &(statp->spr));
}

void stat_print(FILE *fp, stat_t *statp, int soglia){
    fprintf(fp, "%d %d %d %d %d %d",
            statp->hp>soglia?statp->hp:soglia,
            statp->mp>soglia?statp->mp:soglia,
            statp->atk>soglia?statp->atk:soglia,
            statp->def>soglia?statp->def:soglia,
            statp->mag>soglia?statp->mag:soglia,
            statp->spr>soglia?statp->spr:soglia);
}

void stat_cpy(stat_t *dest, stat_t *target){
    dest->atk=target->atk;
    dest->def=target->def;
    dest->spr=target->spr;
    dest->mag=target->mag;
    dest->mp=target->mp;
    dest->hp=target->hp;
}

/* funzioni di input/output di un oggetto dell'inventario */
void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp, "%s %s", invp->nome, invp->tipo);
    stat_read(fp, inv_getStat(invp));
}

void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp, "%s %s", invp->nome, invp->tipo);
    putc(' ', fp);
    stat_print(fp, inv_getStat(invp),INT_MIN);
    putc('\n', fp);
}

/* ritorna il campo stat di un oggetto dell'inventario */
stat_t *inv_getStat(inv_t *invp){
    return &(invp->stat);
}
