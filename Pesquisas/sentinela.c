#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int pesquisaSentinela(int chave, int v[], int n){
    int contador = 1;
    int i = 0;
    v[n] = chave;
    while(v[i] != chave){
        contador++;
        i++;
    }
    contador++;
    
    if(contador < n) return contador;
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
    
    int v[n+1];
    geraVetor(n, v);
    printf("Melhor caso: %d\n", pesquisaSentinela(v[0], v, n));
    printf("Pior caso: %d\n", n+2);
    printf("Caso médio: %d\n", pesquisaSentinela(v[rand() % n], v, n));



}