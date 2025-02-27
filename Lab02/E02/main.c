#include <stdio.h>
#include <stdlib.h>

int **malloc2dR(int nr, int nc, FILE *fp);

void separa(int **mat, int nr, int nc, int *nere, int *bianche);

void stdeall(int *ptr, int nc);

int main() {
    char dir[20]="../mat.txt";
    int nr, nc, ncb, ncn;
    FILE *fp=fopen(dir, "r");
    fscanf(fp, "%d %d", &nr, &nc);
    ncn=(nr*nc)%2==0?(nr*nc/2):(nr*nc/2.0+0.5);
    ncb=(nr*nc)%2==0?(nr*nc/2):(nr*nc/2.0-0.5);
    int **mat=malloc2dR(nr, nc, fp), *nere=(int *) malloc(ncn*(sizeof(int))), *bianche=(int *) malloc(ncb*(sizeof(int)));
    fclose(fp);

    separa(mat, nr, nc, nere, bianche);

    printf("Celle nere:\n");
    stdeall(nere, ncn);
    printf("Celle bianche:\n");
    stdeall(bianche, ncb);

    return 0;
}

int **malloc2dR(int nr, int nc, FILE *fp){
    int **mat;
    mat = (int **) malloc(nr*(sizeof (int *)));
    if (mat==NULL) exit(1);
    for (int ir=0; ir<nr; ir++){
        mat[ir]= (int *) malloc(nc*(sizeof (int)));
        if (mat[ir]==NULL) exit(1);
        for (int ic=0; ic<nc; ic++){
            fscanf(fp, "%d", &mat[ir][ic]);
        }
    }

    return mat;
}

void separa(int **mat, int nr, int nc, int *nere, int *bianche){
    int cn=0, cb=0;
    for (int ir=0; ir<nr; ir++) {
        for (int ic = 0; ic < nc; ic++) {
            if ((ir + ic) % 2 == 0) { //caselle nere
                nere[cn] = mat[ir][ic];
                cn++;
            } else { //caselle bianche
                bianche[cb] = mat[ir][ic];
                cb++;
            }
        }
    }
}

void stdeall(int *ptr, int nc){
    for (int i=0; i<nc; i++){
        printf("%d ", ptr[i]);
    }
    free(ptr);
    puts("");
}