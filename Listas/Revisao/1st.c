#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    printf("Digite o valor do target\n");
    int target; scanf("%d", &target);

    printf("Digite o tamanho do vetor\n");
    int tam; scanf("%d", &tam);
    int v[tam];

    printf("Digite os valores do vetor\n");
    for(int i = 0;i < tam;i++){ 
        printf("v[%d]:\n", i); 
        scanf("%d", &v[i]);
    }

    int ans = 0;
    int TAM = 1000000;
    int metade = TAM/2;
    int hash[TAM];
    memset(hash, 0, sizeof(hash));

    for(int i = 0;i < tam;i++){
        int c = target - v[i];
        if(c >= -metade && c <= metade && hash[metade + c] >= 1){
            ans = 1; 
            break; 
        }
        hash[metade + v[i]]++;
        
    }

    if(ans) printf("True\n");
    else printf("False\n");

}