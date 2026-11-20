#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "avl.h"
#include "rubronegra.h"
#include "arvoreb.h"

#define TAM 10000
#define AMOSTRAS 10
#define PASSO 10
#define LIMITE 1000000

long long contador = 0;
int chaves[AMOSTRAS][TAM];
char usada[LIMITE];

void geraChaves() {
    srand(time(NULL));

    for (int s = 0; s < AMOSTRAS; s++) {
        for (int i = 0; i < LIMITE; i++) {
            usada[i] = 0;
        }

        for (int i = 0; i < TAM; i++) {
            int chave = rand() % LIMITE;

            while (usada[chave]) {
                chave = rand() % LIMITE;
            }

            usada[chave] = 1;
            chaves[s][i] = chave;
        }
    }

    FILE* fp = fopen("chaves.csv", "w");

    fprintf(fp, "amostra1");

    for (int s = 1; s < AMOSTRAS; s++) {
        fprintf(fp, ",amostra%d", s + 1);
    }

    fprintf(fp, "\n");

    for (int i = 0; i < TAM; i++) {
        fprintf(fp, "%d", chaves[0][i]);

        for (int s = 1; s < AMOSTRAS; s++) {
            fprintf(fp, ",%d", chaves[s][i]);
        }

        fprintf(fp, "\n");
    }

    fclose(fp);
}

int lerChaves() {
    FILE* fp = fopen("chaves.csv", "r");

    if (fp == NULL) {
        return 0;
    }

    char cabecalho[200];

    if (fgets(cabecalho, 200, fp) == NULL) {
        fclose(fp);
        return 0;
    }

    for (int i = 0; i < TAM; i++) {
        for (int s = 0; s < AMOSTRAS; s++) {
            if (fscanf(fp, "%d,", &chaves[s][i]) != 1) {
                fclose(fp);
                return 0;
            }
        }
    }

    fclose(fp);
    return 1;
}

void testaAVL(int v[], int n, long long* adicao, long long* remocao) {
    ArvoreAVL* arvore = criarAVL();

    contador = 0;

    for (int i = 0; i < n; i++) {
        adicionarAVL(arvore, v[i]);
    }

    *adicao += contador;
    contador = 0;

    for (int i = 0; i < n; i++) {
        removerAVL(arvore, v[i]);
    }

    *remocao += contador;
    liberarAVL(arvore);
}

void testaRN(int v[], int n, long long* adicao, long long* remocao) {
    ArvoreRN* arvore = criarRN();

    contador = 0;

    for (int i = 0; i < n; i++) {
        adicionarRN(arvore, v[i]);
    }

    *adicao += contador;
    contador = 0;

    for (int i = 0; i < n; i++) {
        removerRN(arvore, v[i]);
    }

    *remocao += contador;
    liberarRN(arvore);
}

void testaB(int ordem, int v[], int n, long long* adicao, long long* remocao) {
    ArvoreB* arvore = criaArvore(ordem);

    contador = 0;

    for (int i = 0; i < n; i++) {
        adicionaChave(arvore, v[i]);
    }

    *adicao += contador;
    contador = 0;

    for (int i = 0; i < n; i++) {
        removeChave(arvore, v[i]);
    }

    *remocao += contador;
    liberaArvore(arvore);
}

void mostraAlturas() {
    ArvoreAVL* avl = criarAVL();
    ArvoreRN* rn = criarRN();
    ArvoreB* b1 = criaArvore(1);
    ArvoreB* b5 = criaArvore(5);
    ArvoreB* b10 = criaArvore(10);

    for (int i = 0; i < TAM; i++) {
        adicionarAVL(avl, chaves[0][i]);
        adicionarRN(rn, chaves[0][i]);
        adicionaChave(b1, chaves[0][i]);
        adicionaChave(b5, chaves[0][i]);
        adicionaChave(b10, chaves[0][i]);
    }

    printf("Altura das arvores com %d chaves (amostra 1)\n", TAM);
    printf("AVL: %d\n", alturaAVL(avl));
    printf("Rubro-negra: %d\n", alturaRN(rn));
    printf("B ordem 1: %d\n", alturaB(b1));
    printf("B ordem 5: %d\n", alturaB(b5));
    printf("B ordem 10: %d\n\n", alturaB(b10));

    liberarAVL(avl);
    liberarRN(rn);
    liberaArvore(b1);
    liberaArvore(b5);
    liberaArvore(b10);
}

int main() {
    if (!lerChaves()) {
        printf("Gerando chaves.csv\n\n");
        geraChaves();
    }

    FILE* adicao = fopen("../resultados/resultado_adicao.csv", "w");
    FILE* remocao = fopen("../resultados/resultado_remocao.csv", "w");

    if (adicao == NULL || remocao == NULL) {
        printf("Nao foi possivel criar os arquivos em ../resultados\n");
        return 1;
    }

    mostraAlturas();

    fprintf(adicao, "N,AVL,RubroNegra,B1,B5,B10\n");
    fprintf(remocao, "N,AVL,RubroNegra,B1,B5,B10\n");

    printf("Esforco medio por operacao (adicao / remocao)\n\n");
    printf("%-6s | %-15s | %-15s | %-15s | %-15s | %-15s\n", "N", "AVL", "RUBRO-NEGRA", "B ORDEM 1", "B ORDEM 5", "B ORDEM 10");
    printf("-------+-----------------+-----------------+-----------------+-----------------+----------------\n");

    for (int n = 1; n <= TAM; n = (n == 1) ? PASSO : n + PASSO) {
        long long somaAdicao[5] = {0, 0, 0, 0, 0};
        long long somaRemocao[5] = {0, 0, 0, 0, 0};

        for (int s = 0; s < AMOSTRAS; s++) {
            testaAVL(chaves[s], n, &somaAdicao[0], &somaRemocao[0]);
            testaRN(chaves[s], n, &somaAdicao[1], &somaRemocao[1]);
            testaB(1, chaves[s], n, &somaAdicao[2], &somaRemocao[2]);
            testaB(5, chaves[s], n, &somaAdicao[3], &somaRemocao[3]);
            testaB(10, chaves[s], n, &somaAdicao[4], &somaRemocao[4]);
        }

        double operacoes = (double) n * AMOSTRAS;

        fprintf(adicao, "%d", n);
        fprintf(remocao, "%d", n);

        for (int k = 0; k < 5; k++) {
            fprintf(adicao, ",%.2f", somaAdicao[k] / operacoes);
            fprintf(remocao, ",%.2f", somaRemocao[k] / operacoes);
        }

        fprintf(adicao, "\n");
        fprintf(remocao, "\n");

        if (n % 1000 == 0) {
            printf("%-6d", n);

            for (int k = 0; k < 5; k++) {
                printf(" | %6.2f / %-6.2f", somaAdicao[k] / operacoes, somaRemocao[k] / operacoes);
            }

            printf("\n");
        }
    }

    fclose(adicao);
    fclose(remocao);

    return 0;
}
