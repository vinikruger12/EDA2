#include <stdio.h>
#include <stdlib.h>

int max(int a, int b){
    return a > b ? a : b;
}

int main(){
    int n, k; scanf("%d %d", &n, &k);
    int v[n];
    
    for(int i = 0;i < n;i++){
        scanf("%d", &v[i]);
    }
    int maior = v[0];
    for(int i = 0;i <= (n-k);i++){
        int o = k;
        for(int j = i;o--;j++){
            maior = max(maior, v[j]);
        }
        printf("%d ", maior);
        maior = 0;
    }
    printf("\n");


}