#ifndef AVL_H
#define AVL_H

typedef struct noAVL {
    struct noAVL* pai;
    struct noAVL* esquerda;
    struct noAVL* direita;
    int valor;
    int altura;
} NoAVL;

typedef struct arvoreAVL {
    NoAVL* raiz;
} ArvoreAVL;

extern long long contador;

ArvoreAVL* criarAVL(void);
void adicionarAVL(ArvoreAVL* arvore, int valor);
void removerAVL(ArvoreAVL* arvore, int valor);
int alturaAVL(ArvoreAVL* arvore);
void liberarAVL(ArvoreAVL* arvore);

#endif
