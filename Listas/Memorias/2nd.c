#include <stdio.h>
#include <stdlib.h>

#define M 7

typedef struct {
    int *dados;
    int tamanho;
    int capacidade;
} Particao;

typedef struct {
    int valor;
    int flag;
} Verificador;

void push_back (Particao *p, int valor) {
    if (p->tamanho == p->capacidade) {
        if (p->capacidade == 0) p->capacidade = 10; // numero qualquer, nem muito grande e nem muito pequeno
        else p->capacidade = p->capacidade * 2;

        p->dados = (int *) realloc(p->dados, p->capacidade * sizeof(int));
    }

    p->dados[p->tamanho] = valor;

    p->tamanho++;
} 

int main () {
    int arquivo[36] = {
        30, 14, 15, 75, 32, 6, 5, 81, 48, 41, 87, 18,
        56, 20, 26, 4,  21, 65, 22, 49, 11, 16, 8,  12,
        44, 9,  7,  81, 23, 19, 1,  78, 13, 16, 51, 8
    };

    int indice = 0;
    Verificador memoria[M];

    for (int i = 0; i < M; i++) {
        memoria[i].valor = arquivo[indice++];
        memoria[i].flag = 0;
    }

    int particoestotal = 0;
    int fim = 0;

    while (!fim) {
        Particao p_atual = {NULL, 0, 0};
        particoestotal++;

        int ultimogravado = -1;

        while (1) {
            int menor = -1;
            for (int i = 0; i < M; i++) {
                if (memoria[i].flag == 0) {
                    if (menor == -1 || memoria[i].valor < memoria[menor].valor) {
                        menor = i;
                    }
                }
            }

            if (menor == -1) break;

            ultimogravado  = memoria[menor].valor;
            push_back(&p_atual, ultimogravado);

            if (indice < 36) {
                int novo_valor = arquivo[indice++];
                memoria[menor].valor = novo_valor;

                if (novo_valor < ultimogravado) {
                    memoria[menor].flag = 1;
                }
            }
            else {
                memoria[menor].flag = 2;
            }
        }

        printf("Particao %d: ", particoestotal);
        for (int i = 0; i < p_atual.tamanho; i++) {
            printf("%d ", p_atual.dados[i]);
        }

        printf("\n");
        free(p_atual.dados);

        fim = 1;

        for (int i = 0; i < M; i++) {
            if (memoria[i].flag == 1) {
                memoria[i].flag = 0;
                fim = 0;
            }
        }
    }

    return 0;
}