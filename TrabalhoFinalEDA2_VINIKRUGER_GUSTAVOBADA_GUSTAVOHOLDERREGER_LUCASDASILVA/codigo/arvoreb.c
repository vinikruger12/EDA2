#include <stdio.h>
#include <stdlib.h>
#include "arvoreb.h"

NoB* criaNo(ArvoreB* arvore) {
    int max = arvore->ordem * 2;
    NoB* no = malloc(sizeof(NoB));

    no->pai = NULL;
    no->chaves = malloc(sizeof(int) * (max + 1));
    no->filhos = malloc(sizeof(NoB*) * (max + 2));
    no->total = 0;

    for (int i = 0; i < max + 2; i++) {
        no->filhos[i] = NULL;
    }

    return no;
}

ArvoreB* criaArvore(int ordem) {
    ArvoreB* arvore = malloc(sizeof(ArvoreB));
    arvore->ordem = ordem;
    arvore->raiz = criaNo(arvore);

    return arvore;
}

int pesquisaBinaria(NoB* no, int chave) {
    int inicio = 0, fim = no->total - 1, meio;

    while (inicio <= fim) {
        contador++;
        meio = (inicio + fim) / 2;

        if (no->chaves[meio] == chave) {
            return meio;
        } else if (no->chaves[meio] > chave) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    return inicio;
}

NoB* localizaNo(ArvoreB* arvore, int chave) {
    NoB* no = arvore->raiz;

    while (no->filhos[0] != NULL) {
        int i = pesquisaBinaria(no, chave);
        no = no->filhos[i];
    }

    return no;
}

void adicionaChaveNo(NoB* no, NoB* novo, int chave) {
    int i = pesquisaBinaria(no, chave);

    for (int j = no->total - 1; j >= i; j--) {
        contador++;
        no->chaves[j + 1] = no->chaves[j];
        no->filhos[j + 2] = no->filhos[j + 1];
    }

    no->chaves[i] = chave;
    no->filhos[i + 1] = novo;
    no->total++;
}

int transbordo(ArvoreB* arvore, NoB* no) {
    return no->total > arvore->ordem * 2;
}

NoB* divideNo(ArvoreB* arvore, NoB* no) {
    contador++;

    int meio = no->total / 2;
    NoB* novo = criaNo(arvore);
    novo->pai = no->pai;

    for (int i = meio + 1; i < no->total; i++) {
        contador++;
        novo->filhos[novo->total] = no->filhos[i];
        novo->chaves[novo->total] = no->chaves[i];

        if (novo->filhos[novo->total] != NULL) {
            novo->filhos[novo->total]->pai = novo;
        }

        novo->total++;
    }

    novo->filhos[novo->total] = no->filhos[no->total];

    if (novo->filhos[novo->total] != NULL) {
        novo->filhos[novo->total]->pai = novo;
    }

    no->total = meio;

    return novo;
}

void adicionaChaveRecursivo(ArvoreB* arvore, NoB* no, NoB* novo, int chave) {
    adicionaChaveNo(no, novo, chave);

    if (transbordo(arvore, no)) {
        int promovido = no->chaves[arvore->ordem];
        NoB* irmao = divideNo(arvore, no);

        if (no->pai == NULL) {
            NoB* pai = criaNo(arvore);
            pai->filhos[0] = no;
            adicionaChaveNo(pai, irmao, promovido);

            no->pai = pai;
            irmao->pai = pai;
            arvore->raiz = pai;
        } else {
            adicionaChaveRecursivo(arvore, no->pai, irmao, promovido);
        }
    }
}

void adicionaChave(ArvoreB* arvore, int chave) {
    NoB* no = localizaNo(arvore, chave);
    adicionaChaveRecursivo(arvore, no, NULL, chave);
}

void liberaNo(NoB* no) {
    free(no->chaves);
    free(no->filhos);
    free(no);
}

void removeChaveNo(NoB* no, int i) {
    for (int j = i; j < no->total - 1; j++) {
        contador++;
        no->chaves[j] = no->chaves[j + 1];
        no->filhos[j + 1] = no->filhos[j + 2];
    }

    no->total--;
    no->filhos[no->total + 1] = NULL;
}

int subfluxo(ArvoreB* arvore, NoB* no) {
    return no->total < arvore->ordem;
}

int indiceFilho(NoB* pai, NoB* filho) {
    int i = 0;

    while (pai->filhos[i] != filho) {
        contador++;
        i++;
    }

    return i;
}

void emprestaEsquerda(NoB* pai, int i) {
    contador++;

    NoB* no = pai->filhos[i];
    NoB* esquerdo = pai->filhos[i - 1];

    for (int j = no->total; j > 0; j--) {
        contador++;
        no->chaves[j] = no->chaves[j - 1];
        no->filhos[j + 1] = no->filhos[j];
    }

    no->filhos[1] = no->filhos[0];
    no->chaves[0] = pai->chaves[i - 1];
    no->filhos[0] = esquerdo->filhos[esquerdo->total];

    if (no->filhos[0] != NULL) {
        no->filhos[0]->pai = no;
    }

    no->total++;

    pai->chaves[i - 1] = esquerdo->chaves[esquerdo->total - 1];
    esquerdo->filhos[esquerdo->total] = NULL;
    esquerdo->total--;
}

void emprestaDireita(NoB* pai, int i) {
    contador++;

    NoB* no = pai->filhos[i];
    NoB* direito = pai->filhos[i + 1];

    no->chaves[no->total] = pai->chaves[i];
    no->filhos[no->total + 1] = direito->filhos[0];

    if (no->filhos[no->total + 1] != NULL) {
        no->filhos[no->total + 1]->pai = no;
    }

    no->total++;

    pai->chaves[i] = direito->chaves[0];
    direito->filhos[0] = direito->filhos[1];
    removeChaveNo(direito, 0);
}

void juntaNos(NoB* pai, int i) {
    contador++;

    NoB* esquerdo = pai->filhos[i];
    NoB* direito = pai->filhos[i + 1];

    esquerdo->chaves[esquerdo->total] = pai->chaves[i];
    esquerdo->total++;

    for (int j = 0; j < direito->total; j++) {
        contador++;
        esquerdo->chaves[esquerdo->total] = direito->chaves[j];
        esquerdo->filhos[esquerdo->total] = direito->filhos[j];

        if (esquerdo->filhos[esquerdo->total] != NULL) {
            esquerdo->filhos[esquerdo->total]->pai = esquerdo;
        }

        esquerdo->total++;
    }

    esquerdo->filhos[esquerdo->total] = direito->filhos[direito->total];

    if (esquerdo->filhos[esquerdo->total] != NULL) {
        esquerdo->filhos[esquerdo->total]->pai = esquerdo;
    }

    removeChaveNo(pai, i);
    liberaNo(direito);
}

void corrigeSubfluxo(ArvoreB* arvore, NoB* no) {
    if (no->pai == NULL) {
        if (no->total == 0 && no->filhos[0] != NULL) {
            arvore->raiz = no->filhos[0];
            arvore->raiz->pai = NULL;
            liberaNo(no);
        }

        return;
    }

    if (!subfluxo(arvore, no)) {
        return;
    }

    NoB* pai = no->pai;
    int i = indiceFilho(pai, no);

    if (i > 0 && pai->filhos[i - 1]->total > arvore->ordem) {
        emprestaEsquerda(pai, i);
    } else if (i < pai->total && pai->filhos[i + 1]->total > arvore->ordem) {
        emprestaDireita(pai, i);
    } else {
        if (i > 0) {
            juntaNos(pai, i - 1);
        } else {
            juntaNos(pai, i);
        }

        corrigeSubfluxo(arvore, pai);
    }
}

void removeChave(ArvoreB* arvore, int chave) {
    NoB* no = arvore->raiz;
    int i = 0;

    while (no != NULL) {
        i = pesquisaBinaria(no, chave);

        if (i < no->total && no->chaves[i] == chave) {
            break;
        }

        no = no->filhos[i];
    }

    if (no == NULL) {
        return;
    }

    if (no->filhos[0] != NULL) {
        NoB* folha = no->filhos[i + 1];
        contador++;

        while (folha->filhos[0] != NULL) {
            contador++;
            folha = folha->filhos[0];
        }

        no->chaves[i] = folha->chaves[0];
        no = folha;
        i = 0;
    }

    removeChaveNo(no, i);
    corrigeSubfluxo(arvore, no);
}

int alturaB(ArvoreB* arvore) {
    NoB* no = arvore->raiz;
    int niveis = 1;

    while (no->filhos[0] != NULL) {
        no = no->filhos[0];
        niveis++;
    }

    return niveis;
}

void liberaNos(NoB* no) {
    if (no->filhos[0] != NULL) {
        for (int i = 0; i <= no->total; i++) {
            liberaNos(no->filhos[i]);
        }
    }

    liberaNo(no);
}

void liberaArvore(ArvoreB* arvore) {
    liberaNos(arvore->raiz);
    free(arvore);
}
