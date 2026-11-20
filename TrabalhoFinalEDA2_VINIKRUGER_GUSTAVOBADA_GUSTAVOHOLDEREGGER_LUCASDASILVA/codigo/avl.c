#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int max(int a, int b) {
    return a > b ? a : b;
}

int altura(NoAVL* no) {
    return no != NULL ? no->altura : 0;
}

int fb(NoAVL* no) {
    return altura(no->esquerda) - altura(no->direita);
}

NoAVL* rse(ArvoreAVL* arvore, NoAVL* no) {
    contador++;

    NoAVL* pai = no->pai;
    NoAVL* direita = no->direita;

    if (direita->esquerda != NULL) {
        direita->esquerda->pai = no;
    }

    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    if (pai == NULL) {
        arvore->raiz = direita;
    } else if (pai->esquerda == no) {
        pai->esquerda = direita;
    } else {
        pai->direita = direita;
    }

    no->altura = max(altura(no->esquerda), altura(no->direita)) + 1;
    direita->altura = max(altura(direita->esquerda), altura(direita->direita)) + 1;

    return direita;
}

NoAVL* rsd(ArvoreAVL* arvore, NoAVL* no) {
    contador++;

    NoAVL* pai = no->pai;
    NoAVL* esquerda = no->esquerda;

    if (esquerda->direita != NULL) {
        esquerda->direita->pai = no;
    }

    no->esquerda = esquerda->direita;
    no->pai = esquerda;

    esquerda->direita = no;
    esquerda->pai = pai;

    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else if (pai->esquerda == no) {
        pai->esquerda = esquerda;
    } else {
        pai->direita = esquerda;
    }

    no->altura = max(altura(no->esquerda), altura(no->direita)) + 1;
    esquerda->altura = max(altura(esquerda->esquerda), altura(esquerda->direita)) + 1;

    return esquerda;
}

NoAVL* rde(ArvoreAVL* arvore, NoAVL* no) {
    no->direita = rsd(arvore, no->direita);
    return rse(arvore, no);
}

NoAVL* rdd(ArvoreAVL* arvore, NoAVL* no) {
    no->esquerda = rse(arvore, no->esquerda);
    return rsd(arvore, no);
}

void balanceamento(ArvoreAVL* arvore, NoAVL* no) {
    while (no != NULL) {
        contador++;

        int anterior = no->altura;
        no->altura = max(altura(no->esquerda), altura(no->direita)) + 1;

        int fator = fb(no);

        if (fator > 1) {
            if (fb(no->esquerda) >= 0) {
                no = rsd(arvore, no);
            } else {
                no = rdd(arvore, no);
            }
        } else if (fator < -1) {
            if (fb(no->direita) <= 0) {
                no = rse(arvore, no);
            } else {
                no = rde(arvore, no);
            }
        }

        if (no->altura == anterior) {
            break;
        }

        no = no->pai;
    }
}

ArvoreAVL* criarAVL() {
    ArvoreAVL* arvore = malloc(sizeof(ArvoreAVL));
    arvore->raiz = NULL;

    return arvore;
}

void adicionarAVL(ArvoreAVL* arvore, int valor) {
    NoAVL* no = arvore->raiz;

    while (no != NULL) {
        contador++;

        if (valor > no->valor) {
            if (no->direita != NULL) {
                no = no->direita;
            } else {
                break;
            }
        } else {
            if (no->esquerda != NULL) {
                no = no->esquerda;
            } else {
                break;
            }
        }
    }

    NoAVL* novo = malloc(sizeof(NoAVL));
    novo->valor = valor;
    novo->pai = no;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->altura = 1;

    if (no == NULL) {
        arvore->raiz = novo;
    } else {
        if (valor > no->valor) {
            no->direita = novo;
        } else {
            no->esquerda = novo;
        }

        balanceamento(arvore, no);
    }
}

NoAVL* localizarAVL(NoAVL* no, int valor) {
    while (no != NULL) {
        contador++;

        if (no->valor == valor) {
            return no;
        }

        no = valor < no->valor ? no->esquerda : no->direita;
    }

    return NULL;
}

void removerAVL(ArvoreAVL* arvore, int valor) {
    NoAVL* no = localizarAVL(arvore->raiz, valor);

    if (no == NULL) {
        return;
    }

    if (no->esquerda != NULL && no->direita != NULL) {
        NoAVL* sucessor = no->direita;
        contador++;

        while (sucessor->esquerda != NULL) {
            contador++;
            sucessor = sucessor->esquerda;
        }

        no->valor = sucessor->valor;
        no = sucessor;
    }

    NoAVL* filho = no->esquerda != NULL ? no->esquerda : no->direita;
    NoAVL* pai = no->pai;

    if (filho != NULL) {
        filho->pai = pai;
    }

    if (pai == NULL) {
        arvore->raiz = filho;
    } else if (pai->esquerda == no) {
        pai->esquerda = filho;
    } else {
        pai->direita = filho;
    }

    free(no);
    balanceamento(arvore, pai);
}

int alturaAVL(ArvoreAVL* arvore) {
    return altura(arvore->raiz);
}

void liberarNoAVL(NoAVL* no) {
    if (no != NULL) {
        liberarNoAVL(no->esquerda);
        liberarNoAVL(no->direita);
        free(no);
    }
}

void liberarAVL(ArvoreAVL* arvore) {
    liberarNoAVL(arvore->raiz);
    free(arvore);
}
