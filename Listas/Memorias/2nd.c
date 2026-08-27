#include <stdio.h>
#include <stdlib.h>

#define M 7


typedef struct No {
    int dado;
    struct No* proximo;
} No;

void inserirInicio(No** cabeca, int novoDado) {
    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->dado = novoDado;
    novoNo->proximo = *cabeca;
    *cabeca = novoNo;
}

int tamanhoLista(No* cabeca) {
    int contador = 0;
    No* atual = cabeca;
    while (atual != NULL) {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}

void removerPorIndice(No** cabeca, int indice) {
    if (*cabeca == NULL || indice < 0) return;

    No* atual = *cabeca;

    if (indice == 0) {
        *cabeca = atual->proximo;
        free(atual);
        return;
    }

    No* anterior = NULL;
    for (int i = 0; atual != NULL && i < indice; i++) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return;

    anterior->proximo = atual->proximo;
    free(atual);
}

void exibirLista(No* cabeca) {
    No* atual = cabeca;
    printf("Lista: ");
    while (atual != NULL) {
        printf("%d -> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

void liberarLista(No* cabeca) {
    No* atual = cabeca;
    No* temp;
    while (atual != NULL) {
        temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}

int main() {

    int vetor[36] = {30, 14, 15, 75, 32, 6, 5, 81, 48, 41, 87, 18, 56, 20, 26, 4, 21, 65, 22, 49, 11, 16, 8, 12, 44, 9, 7, 81, 23, 19, 1, 78, 13, 16, 51, 8};

    No* particoes[32 % M];



    return 0;
}
