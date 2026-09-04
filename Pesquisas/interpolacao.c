#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int pesquisaInterpolacao(int chave, int v[], int n){
    int contador = 3;
    int l = 0, r = (n-1);
    while(l <= r && chave >= v[l] && chave <= v[r]){
        contador++;
        if(l == r) return contador;

        int m = l + (((double) (r - l) / (v[r] - v[l])) * (chave - v[l]));

        contador++;
        if(v[m] == chave) return contador;
        else if(v[m] < chave) l = m + 1;
        else r = m - 1;;
        contador += 4;
    }

    return contador;

}

void swap(int i, int j, int vetor[]){
    int aux = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = aux;
}

void quicksort(int inicio, int fim, int vetor[]){
    if(inicio >= fim) return;
    int pivo = vetor[fim];
    int j = inicio - 1;
    for(int i = inicio;i < fim;i++){
        if(vetor[i] <= pivo){
            j++;
            if(i != j) swap(i, j, vetor);
        }
    }

    j++;
    swap(j, fim, vetor);
    quicksort(inicio, j-1, vetor);
    quicksort(j+1, fim, vetor);
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
    quicksort(0, n-1, v);

    printf("Melhor caso: %d\n", pesquisaInterpolacao((((double) (n-1) / (v[n-1] - v[0])) * (0 - v[0])), v, n));
    printf("Pior caso: %d\n", pesquisaInterpolacao(n, v, n));
    printf("Caso médio: %d\n", pesquisaInterpolacao(v[rand() % n], v, n));



}