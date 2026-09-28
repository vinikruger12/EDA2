#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maior(int a, int b){
    if(a > b) return a;
    return b;
}


int main(){
    int n;
    scanf("%d", &n);
    int v[n];   
    

    for(int i = 0;i < n;i++){
        scanf("%d", &v[i]);
        if(v[i] < 0) v[i] = 0;
    }

    int soma1 = v[0], soma2 = v[1];

    for(int i = 2;i < n;i++){
        int atual = maior(soma2, soma1 + v[i]);
        soma1 = soma2;
        soma2 = atual;
    }

    printf("%d\n", soma2);
}