#ifndef ARVOREB_H
#define ARVOREB_H

typedef struct noB {
    int total;
    int* chaves;
    struct noB** filhos;
    struct noB* pai;
} NoB;

typedef struct arvoreB {
    NoB* raiz;
    int ordem;
} ArvoreB;

extern long long contador;

ArvoreB* criaArvore(int ordem);
void adicionaChave(ArvoreB* arvore, int chave);
void removeChave(ArvoreB* arvore, int chave);
int alturaB(ArvoreB* arvore);
void liberaArvore(ArvoreB* arvore);

#endif
