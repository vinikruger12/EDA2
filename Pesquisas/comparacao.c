#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int pesquisaInterpolacao(int chave, int v[], int n){
    int contador = 3;
    int l = 0, r = (n-1);
    while(l <= r && chave >= v[l] && chave <= v[r]){
        contador++;
        if(l == r || v[r] == v[l]) return contador;

        int m = l + (((double) (r - l) / (v[r] - v[l])) * (chave - v[l]));

        contador++;
        if(v[m] == chave) return contador;
        else if(v[m] < chave) l = m + 1;
        else r = m - 1;;
        contador += 4;
    }

    return contador;

}

int pesquisaBinaria(int chave, int v[], int n){
    int contador = 1;
    int l = 0, r = (n-1);
    while(l <= r){
        int m = (l+r)/2;
        contador++;
        if(v[m] == chave) return contador;
        else if(v[m] < chave) l = m + 1;
        else r = m - 1;;
        contador += 2;
    }

    return contador;
}

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



int* geraVetor(int n) {
    int* v = malloc(sizeof(int) * (n + 1));

    for (int i = 0; i < n; i++) {
        v[i] = rand() % n;
    }

    return v;
}

void printaVetor(int n, int v[]){
    for(int i = 0;i < n;i++){
        printf("[%d]: %d\n",i, v[i]);
    }
}

int main(int argc, char* argv[]){

    srand(time(NULL));

    int n = atoi(argv[1]);
    char* comparacoes = "resultados_buscas.csv";
    FILE* fp = fopen(comparacoes, "w"); 

    printf("%-8s | %-14s | %-10s | %-10s | %-10s\n", "TAM (N)", "INTERPOLACAO", "BINARIO", "SENTINELA", "SEQUENCIAL");
    printf("---------+----------------+------------+------------+------------\n");
    fprintf(fp, "N,Interpolacao,Binario,Sentinela,Sequencial\n");

    for(int i = 1;i <= n;i++){
        int *v = geraVetor(i);
        int media = rand() % i;
        quicksort(0, i-1, v);

        int inter = 0, bin = 0, sent = 0, seq = 0;
        int k = 100;
        for(int j = 0;j < k;j++){
            inter += pesquisaInterpolacao(v[media], v, i);
            bin += pesquisaBinaria(v[media], v, i);
            sent += pesquisaSentinela(v[media], v, i);
            seq += pesquisaSequencial(v[media], v, i);
        }
        inter /= k;
        bin /= k;
        sent /= k;
        seq /= k;

        printf("%-8d | %-14d | %-10d | %-10d | %-10d\n", i, inter, bin, sent, seq);
        fprintf(fp, "%d,%d,%d,%d,%d\n", i, inter, bin, sent, seq);
        free(v);
    }
}