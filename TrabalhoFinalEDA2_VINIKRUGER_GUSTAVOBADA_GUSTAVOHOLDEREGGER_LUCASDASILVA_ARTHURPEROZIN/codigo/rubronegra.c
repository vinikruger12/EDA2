#include <stdio.h>
#include <stdlib.h>
#include "rubronegra.h"

static NoRN* criarNo(ArvoreRN* arvore, NoRN* pai, int valor) {
    NoRN* no = malloc(sizeof(NoRN));

    no->pai = pai;
    no->valor = valor;
    no->direita = arvore->nulo;
    no->esquerda = arvore->nulo;

    return no;
}

ArvoreRN* criarRN(void) {
    ArvoreRN* arvore = malloc(sizeof(ArvoreRN));
    arvore->nulo = NULL;

    arvore->nulo = criarNo(arvore, NULL, 0);
    arvore->nulo->cor = Preto;

    arvore->raiz = arvore->nulo;

    return arvore;
}

static void rotacionarEsquerda(ArvoreRN* arvore, NoRN* no) {
    contador++;

    NoRN* direita = no->direita;
    no->direita = direita->esquerda;

    if (direita->esquerda != arvore->nulo) {
        direita->esquerda->pai = no;
    }

    direita->pai = no->pai;

    if (no->pai == arvore->nulo) {
        arvore->raiz = direita;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = direita;
    } else {
        no->pai->direita = direita;
    }

    direita->esquerda = no;
    no->pai = direita;
}

static void rotacionarDireita(ArvoreRN* arvore, NoRN* no) {
    contador++;

    NoRN* esquerda = no->esquerda;
    no->esquerda = esquerda->direita;

    if (esquerda->direita != arvore->nulo) {
        esquerda->direita->pai = no;
    }

    esquerda->pai = no->pai;

    if (no->pai == arvore->nulo) {
        arvore->raiz = esquerda;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = esquerda;
    } else {
        no->pai->direita = esquerda;
    }

    esquerda->direita = no;
    no->pai = esquerda;
}

static void balancear(ArvoreRN* arvore, NoRN* no) {
    while (no->pai->cor == Vermelho) {
        contador++;

        if (no->pai == no->pai->pai->esquerda) {
            NoRN* tio = no->pai->pai->direita;

            if (tio->cor == Vermelho) {
                tio->cor = Preto;
                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho;
                no = no->pai->pai;
            } else {
                if (no == no->pai->direita) {
                    no = no->pai;
                    rotacionarEsquerda(arvore, no);
                }

                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho;
                rotacionarDireita(arvore, no->pai->pai);
            }
        } else {
            NoRN* tio = no->pai->pai->esquerda;

            if (tio->cor == Vermelho) {
                tio->cor = Preto;
                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho;
                no = no->pai->pai;
            } else {
                if (no == no->pai->esquerda) {
                    no = no->pai;
                    rotacionarDireita(arvore, no);
                }

                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho;
                rotacionarEsquerda(arvore, no->pai->pai);
            }
        }
    }

    arvore->raiz->cor = Preto;
}

static NoRN* adicionarNo(ArvoreRN* arvore, NoRN* no, int valor) {
    contador++;

    if (valor > no->valor) {
        if (no->direita == arvore->nulo) {
            no->direita = criarNo(arvore, no, valor);
            no->direita->cor = Vermelho;

            return no->direita;
        } else {
            return adicionarNo(arvore, no->direita, valor);
        }
    } else {
        if (no->esquerda == arvore->nulo) {
            no->esquerda = criarNo(arvore, no, valor);
            no->esquerda->cor = Vermelho;

            return no->esquerda;
        } else {
            return adicionarNo(arvore, no->esquerda, valor);
        }
    }
}

void adicionarRN(ArvoreRN* arvore, int valor) {
    if (arvore->raiz == arvore->nulo) {
        arvore->raiz = criarNo(arvore, arvore->nulo, valor);
        arvore->raiz->cor = Preto;
    } else {
        NoRN* no = adicionarNo(arvore, arvore->raiz, valor);
        balancear(arvore, no);
    }
}

static NoRN* localizarRN(ArvoreRN* arvore, int valor) {
    NoRN* no = arvore->raiz;

    while (no != arvore->nulo) {
        contador++;

        if (no->valor == valor) {
            return no;
        }

        no = valor < no->valor ? no->esquerda : no->direita;
    }

    return NULL;
}

static void transplantar(ArvoreRN* arvore, NoRN* u, NoRN* v) {
    if (u->pai == arvore->nulo) {
        arvore->raiz = v;
    } else if (u == u->pai->esquerda) {
        u->pai->esquerda = v;
    } else {
        u->pai->direita = v;
    }

    v->pai = u->pai;
}

static NoRN* minimo(ArvoreRN* arvore, NoRN* no) {
    contador++;

    while (no->esquerda != arvore->nulo) {
        contador++;
        no = no->esquerda;
    }

    return no;
}

static void balancearRemocao(ArvoreRN* arvore, NoRN* x) {
    while (x != arvore->raiz && x->cor == Preto) {
        contador++;

        if (x == x->pai->esquerda) {
            NoRN* irmao = x->pai->direita;

            if (irmao->cor == Vermelho) {
                irmao->cor = Preto;
                x->pai->cor = Vermelho;
                rotacionarEsquerda(arvore, x->pai);
                irmao = x->pai->direita;
            }

            if (irmao->esquerda->cor == Preto && irmao->direita->cor == Preto) {
                irmao->cor = Vermelho;
                x = x->pai;
            } else {
                if (irmao->direita->cor == Preto) {
                    irmao->esquerda->cor = Preto;
                    irmao->cor = Vermelho;
                    rotacionarDireita(arvore, irmao);
                    irmao = x->pai->direita;
                }

                irmao->cor = x->pai->cor;
                x->pai->cor = Preto;
                irmao->direita->cor = Preto;
                rotacionarEsquerda(arvore, x->pai);
                x = arvore->raiz;
            }
        } else {
            NoRN* irmao = x->pai->esquerda;

            if (irmao->cor == Vermelho) {
                irmao->cor = Preto;
                x->pai->cor = Vermelho;
                rotacionarDireita(arvore, x->pai);
                irmao = x->pai->esquerda;
            }

            if (irmao->direita->cor == Preto && irmao->esquerda->cor == Preto) {
                irmao->cor = Vermelho;
                x = x->pai;
            } else {
                if (irmao->esquerda->cor == Preto) {
                    irmao->direita->cor = Preto;
                    irmao->cor = Vermelho;
                    rotacionarEsquerda(arvore, irmao);
                    irmao = x->pai->esquerda;
                }

                irmao->cor = x->pai->cor;
                x->pai->cor = Preto;
                irmao->esquerda->cor = Preto;
                rotacionarDireita(arvore, x->pai);
                x = arvore->raiz;
            }
        }
    }

    x->cor = Preto;
}

void removerRN(ArvoreRN* arvore, int valor) {
    NoRN* no = localizarRN(arvore, valor);

    if (no == NULL) {
        return;
    }

    NoRN* y = no;
    NoRN* x;
    Cor corOriginal = y->cor;

    if (no->esquerda == arvore->nulo) {
        x = no->direita;
        transplantar(arvore, no, no->direita);
    } else if (no->direita == arvore->nulo) {
        x = no->esquerda;
        transplantar(arvore, no, no->esquerda);
    } else {
        y = minimo(arvore, no->direita);
        corOriginal = y->cor;
        x = y->direita;

        if (y->pai == no) {
            x->pai = y;
        } else {
            transplantar(arvore, y, y->direita);
            y->direita = no->direita;
            y->direita->pai = y;
        }

        transplantar(arvore, no, y);
        y->esquerda = no->esquerda;
        y->esquerda->pai = y;
        y->cor = no->cor;
    }

    free(no);

    if (corOriginal == Preto) {
        balancearRemocao(arvore, x);
    }
}

static int alturaNoRN(ArvoreRN* arvore, NoRN* no) {
    if (no == arvore->nulo) {
        return 0;
    }

    int esquerda = alturaNoRN(arvore, no->esquerda);
    int direita = alturaNoRN(arvore, no->direita);

    return (esquerda > direita ? esquerda : direita) + 1;
}

int alturaRN(ArvoreRN* arvore) {
    return alturaNoRN(arvore, arvore->raiz);
}

static void liberarNoRN(ArvoreRN* arvore, NoRN* no) {
    if (no != arvore->nulo) {
        liberarNoRN(arvore, no->esquerda);
        liberarNoRN(arvore, no->direita);
        free(no);
    }
}

void liberarRN(ArvoreRN* arvore) {
    liberarNoRN(arvore, arvore->raiz);
    free(arvore->nulo);
    free(arvore);
}
