#include <stdio.h>
#include <stdlib.h>

#define DIRBOARD "..//board.txt"
#define DIRTILES "..//tiles.txt"

typedef struct {
    int mark;
    char ca, cb;
    int va, vb;
} tile_t;

typedef struct{
    int n_tiles;
    tile_t *list;
} tiles_t;

typedef struct{
    int i;
    int r;
} tile_i;

typedef struct {
    int nr, nc;
    int marked;
    tile_i **mesh;
} board_t;

void printBoard(board_t board);
void readBoard(board_t *board);
void readTiles(tiles_t *tiles);
void markTaken(board_t *board,tiles_t *tiles);
void copyBoard(board_t  t_sol, board_t *sol);
int calcValue(board_t board, tiles_t tiles);
int findMaxComb_w(board_t orig_board, board_t *edit_board, tiles_t *tiles);
void disp_sempl(int pos, tiles_t *val, board_t t_sol, board_t *sol, int n, int k, int *maxv);

int main() {
    board_t orig_board, sol_board;
    tiles_t tiles;
    int maxv=0;

    readTiles(&tiles);
    readBoard(&orig_board);
    readBoard(&sol_board);
    markTaken(&orig_board, &tiles);

    maxv=findMaxComb_w(orig_board, &sol_board, &tiles);

    printBoard(sol_board);
    printf("Punteggio massimo trovato: %d", maxv);

    return 0;
}

void readBoard(board_t *board){
    FILE *fboard;
    fboard= fopen(DIRBOARD, "r");

    fscanf(fboard, "%d %d", &(board->nr), &(board->nc));

    board->mesh=(tile_i**) calloc(board->nr, sizeof(tile_i*));
    for (int i=0; i<board->nr; i++) {
        (board->mesh)[i]=(tile_i*) calloc(board->nc, sizeof(tile_i));
        for( int j=0; j<board->nc; j++){
            fscanf(fboard, "%d/%d", &((board->mesh)[i][j].i), &((board->mesh)[i][j].r));
        }
    }
    fclose(fboard);
}

void readTiles(tiles_t *tiles){
    FILE *ftiles;
    ftiles= fopen(DIRTILES, "r");

    fscanf(ftiles, "%d", &(tiles->n_tiles));

    tiles->list=(tile_t*) calloc(tiles->n_tiles, sizeof (tile_t));
    for (int i=0; i< tiles->n_tiles; i++){
        fscanf(ftiles, "\n%c %d %c %d",
               &(tiles->list[i].ca),
               &(tiles->list[i].va),
               &(tiles->list[i].cb),
               &(tiles->list[i].vb));
        tiles->list[i].mark=0;
    }

    fclose(ftiles);
}

void markTaken(board_t *board,tiles_t *tiles){
    board->marked=0;
    for (int i=0; i<board->nr; i++) {
        for( int j=0; j<board->nc; j++){
            if (board->mesh[i][j].i!=-1){
                tiles->list[board->mesh[i][j].i].mark=1;
                (board->marked)+=1;
            }
        }
    }
}

int findMaxComb_w(board_t orig_board, board_t *edit_board, tiles_t *tiles){
    int maxv=0;

    disp_sempl(0,
               tiles,
               orig_board,
               edit_board,
               tiles->n_tiles,
               (orig_board.nc)*(orig_board.nr)-orig_board.marked,
               &maxv);

    return maxv;
}

void disp_sempl(int pos, tiles_t *val, board_t t_sol, board_t *sol, int n, int k, int *maxv) {
    int i; int t;
    if (pos >= k) {
        t=calcValue(t_sol, *val);
        if (t>*maxv){
            *maxv=t;
            copyBoard(t_sol, sol);
        }
        return;
    }
    for (i=0; i<n; i++) {
        if (val->list[i].mark == 0) {
            val->list[i].mark = 1;
            for (int j=0; j<n; j++){
                if (t_sol.mesh[j/sol->nc][j%sol->nc].i==-1){
                    t_sol.mesh[j/sol->nc][j%sol->nc].i=i;
                    t_sol.mesh[j/sol->nc][j%sol->nc].r=0;
                    disp_sempl(pos+1, val, t_sol, sol, n, k, maxv);
                    t_sol.mesh[j/sol->nc][j%sol->nc].r=1;
                    disp_sempl(pos+1, val, t_sol, sol, n, k, maxv);
                    //reset to null state
                    t_sol.mesh[j/sol->nc][j%sol->nc].i=-1;
                    t_sol.mesh[j/sol->nc][j%sol->nc].r=-1;
                }
            }
            val->list[i].mark = 0;
        }
    }
}

void copyBoard(board_t  t_sol, board_t *sol){
    for (int i=0; i<sol->nr; i++){
        for (int j=0; j<sol->nc; j++){
            sol->mesh[i][j]=t_sol.mesh[i][j];
        }
    }
}

int calcValue(board_t board, tiles_t tiles){
    int ok=0;
    int punteggio=0, tot=0;
    char color;

    //calcolo punteggio righe
    for (int i=0; i<board.nr; i++){
        ok=1;
        if (board.mesh[i][0].r==0){
            color=tiles.list[board.mesh[i][0].i].ca;
        } else {
            color=tiles.list[board.mesh[i][0].i].cb;
        }
        for (int j=1; j<board.nc && ok==1; j++){
            if (board.mesh[i][j].r==0){
                if (tiles.list[board.mesh[i][j].i].ca==color){
                    punteggio+=tiles.list[board.mesh[i][j].i].va;
                } else {
                    punteggio=0;
                    ok=0;
                }
            } else {
                if (tiles.list[board.mesh[i][j].i].cb==color){
                    punteggio+=tiles.list[board.mesh[i][j].i].vb;
                } else {
                    punteggio=0;
                    ok=0;
                }
            }
        }
        tot+=punteggio;
    }

    for (int j=0; j<board.nc; j++){
        ok=1;
        if (board.mesh[0][j].r==0){
            color=tiles.list[board.mesh[0][j].i].cb;
        } else {
            color=tiles.list[board.mesh[0][j].i].ca;
        }
        for (int i=1; i<board.nr && ok==1; i++){
            if (board.mesh[i][j].r==0){
                if (tiles.list[board.mesh[i][j].i].cb==color){
                    punteggio+=tiles.list[board.mesh[i][j].i].vb;
                } else {
                    punteggio=0;
                    ok=0;
                }
            } else {
                if (tiles.list[board.mesh[i][j].i].ca==color){
                    punteggio+=tiles.list[board.mesh[i][j].i].va;
                } else {
                    punteggio=0;
                    ok=0;
                }
            }
        }
        tot+=punteggio;
    }
    return tot;
}

void printBoard(board_t board){
    for (int i=0; i<board.nr; i++) {
        for (int j=0; j<board.nc; j++) {
            printf("%d/%d ", board.mesh[i][j].i, board.mesh[i][j].r);
        }
        puts("");
    }
    puts("");
}
