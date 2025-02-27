#include <stdio.h>

int majority( int *a, int N);

int main() {
    int vet[8] = {3, 3, 3, 7, 9, 2, 3, 3}, n;
    n=majority(vet, 8);
    printf("%d", n);
    return 0;
}

int majority(int *a, int N){
    int  r=N-1, m=r/2, s,d, js=0, jd=0;
    if (N==1)
        return a[m];

    s=majority(a,m+1);
    d=majority(a+m+1,N-(m+1));

    for (int k=0; k<N;k++){
        if (s==a[k])
            js++;
        if (d==a[k])
            jd++;
    }
    if (js>N/2)
        return s;
    else if (jd>N/2)
        return d;

    return -1;

}