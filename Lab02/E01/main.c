#include <stdio.h>

int gcd(int a, int b);

int main() {
    printf("%d", gcd(60,200));
    return 0;
}

int gcd(int a, int b){
    int c;
    if (a<b){
        c=a;
        a=b;
        b=c;
    }

    if (a==b) return a;

    if (a%2==0 && b%2==0) return 2*gcd(a/2, b/2);
    else if (a%2!=0 && b%2==0) return gcd(a, b/2);
    else if (a%2==0 && b%2!=0) return gcd(a/2, b);
    else if (a%2!=0 && b%2!=0) return gcd((a-b)/2, b);
    else return 0;

}
