#ifndef RUBRONEGRA_H
#define RUBRONEGRA_H

enum coloracao { Vermelho, Preto };
typedef enum coloracao Cor;

typedef struct noRN {
    struct noRN* pai;
    struct noRN* esquerda;
    struct noRN* direita;
    Cor cor;
    int valor;
} NoRN;

typedef struct arvoreRN {
    NoRN* raiz;
    NoRN* nulo;
} ArvoreRN;

extern long long contador;

ArvoreRN* criarRN(void);
void adicionarRN(ArvoreRN* arvore, int valor);
void removerRN(ArvoreRN* arvore, int valor);
int alturaRN(ArvoreRN* arvore);
void liberarRN(ArvoreRN* arvore);

#endif
