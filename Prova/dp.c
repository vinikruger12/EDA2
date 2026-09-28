#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b){
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

    int soma1 = v[0];
    int soma2 = max(v[0], v[1]);

    for(int i = 2;i < n;i++){
        int maior = max(soma2, soma1 + v[i]);
        soma1 = soma2;
        soma2 = maior;
    }

    printf("%d\n", soma2);

}