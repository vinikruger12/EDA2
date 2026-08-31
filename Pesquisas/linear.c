#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int pesquisaSequencial(int chave, int v[], int n){
    int contador = 1;
    for(int i = 0;i < n;i++){
        contador++;
        if(v[i] == chave){
            return contador;
        }
        contador++;
    }

    return contador;
}

void geraVetor(int n, int v[]){
    for(int i = 0;i < n;i++) v[i] = (rand() % n);
}

void printaVetor(int n, int v[]){
    for(int i = 0;i < n;i++){
        printf("[%d]: %d\n",i, v[i]);
    }
}

int main(int argc, char* argv[]){

    srand(time(NULL));

    int n = atoi(argv[1]); 
    
    int v[n];
    geraVetor(n, v);

    printf("Melhor caso: %d\n", pesquisaSequencial(v[0], v, n));
    printf("Pior caso: %d\n", pesquisaSequencial(n, v, n));
    printf("Caso médio: %d\n", pesquisaSequencial(v[rand() % n], v, n));



}