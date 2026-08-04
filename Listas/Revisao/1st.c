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
        hash[metade + v[i]]++;
        if(target - v[i] != v[i]) hash[metade + target - v[i]]++;
        if(hash[metade + v[i]] >= 2){
            ans = 1;
            break;
        }
        
    }

    if(ans) printf("True\n");
    else printf("False\n");

}