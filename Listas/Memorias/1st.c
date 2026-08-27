#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N 100
int vetor[N];

void swap(int i, int j){
    int aux = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = aux;
}

void quicksort(int inicio, int fim){
    if(inicio >= fim) return;
    int pivo = vetor[fim];
    int j = inicio - 1;
    for(int i = inicio;i < fim;i++){
        if(vetor[i] <= pivo){
            j++;
            if(i != j) swap(i, j);
        }
    }

    j++;
    swap(j, fim);
    quicksort(inicio, j-1);
    quicksort(j+1, fim);
}

int main(){
    srand(time(NULL));
    for(int i = 0;i < N;i++){
        vetor[i] = rand() % 100;
    }

    quicksort(0, N-1);

    for(int i = 0;i < N;i++){
        printf("%d ", vetor[i]);
    }

    printf("\n");

}