#include <stdlib.h> 
#include <stdio.h>  

typedef struct no {     
    struct no* pai;      
    struct no* esquerda;     
    struct no* direita;      
    float v; 
} No;  

typedef struct arvore {     
    struct no* raiz; 
} Arvore;  

typedef struct info {     
    No* dado; // CORRIGIDO: de int para No* para poder guardar o nó da árvore 
} Info;  

typedef struct noFSE {     
    Info dados;     
    struct noFSE *atras; 
} NoFse;  

typedef struct fse {     
    NoFse *frente;     
    NoFse *cauda;     
    int quantidade; 
} FSE;  

FSE* criaFila() { // CORRIGIDO: mudado o nome para não dar conflito com o cria() da árvore
    FSE *f = (FSE *) malloc(sizeof(FSE));     
    if (f != NULL) {         
        f->frente = NULL;         
        f->cauda = NULL;         
        f->quantidade = 0;      
    }      
    return f; 
}  

int vaziaFila(FSE *f) { // CORRIGIDO: mudado o nome para não dar conflito com o vazia() da árvore
    return (f->frente == NULL); 
}  

int insere (FSE *f, Info valor) {     
    NoFse *novo = (NoFse *) malloc(sizeof(NoFse)); // CORRIGIDO: alocava sizeof(No) em vez de sizeof(NoFse)      
    if (novo == NULL) return 0;      
    novo->dados = valor;     
    novo->atras = NULL;      
    if (vaziaFila(f)) {         
        f->frente = novo;     
    }     
    else {         
        f->cauda->atras = novo;     
    }      
    f->cauda = novo;     
    f->quantidade++;      
    return 1; 
}  

int remove_ (FSE *f, Info *saida) {     
    if (vaziaFila(f)) return 0;      
    NoFse *aux = f->frente; // segura o nó da frente      
    *saida = aux->dados;      
    f->frente = aux->atras; // a frente vai ser o cara que ta atras do primeiro      
    // se a fila ficou vazia, a cauda também deve ser limpa     
    if (f->frente == NULL) f->cauda = NULL;      
    free(aux);     
    f->quantidade--;      
    return 1; 
}  

int buscaNaFrente (FSE *f, Info *saida) {     
    if (vaziaFila(f)) return 0;      
    *saida = f->frente->dados;      
    return 1; 
}    

Arvore* cria() {     
    Arvore *arvore;     
    arvore = malloc(sizeof(Arvore));     
    arvore->raiz = NULL;     
    return arvore; 
}  

int vazia(Arvore* arvore) {     
    return (arvore->raiz == NULL); 
}  

void adiciona(Arvore* arvore, float valor) {     
    No *no = malloc(sizeof(No));      
    if(vazia(arvore)){         
        no->esquerda = NULL;         
        no->direita = NULL;         
        no->pai = no;         
        arvore->raiz = no;         
        no->v = valor;         
        return;     
    }          
    No *antes = malloc(sizeof(No));     
    No *atual = malloc(sizeof(No));     
    atual = arvore->raiz;     
    int id = 0;          
    while(atual != NULL){         
        if(atual->v > valor){             
            antes = atual;             
            atual = atual->esquerda;             
            id = 0;         
        }         
        else{             
            antes = atual;             
            atual = atual->direita;             
            id = 1;         
        }     
    }          
    if(id == 0){         
        antes->esquerda = no;         
        no->pai = antes;     
    }     
    else{         
        antes->direita = no;         
        no->pai = antes;     
    }      
    no->v = valor;     
    no->esquerda = NULL;     
    no->direita = NULL;     
    return; 
}  

void remover(Arvore* arvore, No* no) {          
    if(no->esquerda != NULL)         
        remover(arvore, no->esquerda);     
    if(no->direita != NULL)         
        remover(arvore, no->direita);          
    if(no->pai == NULL){         
        arvore->raiz = NULL;     
    }     
    else{         
        if(no->pai->esquerda == no)             
            no->pai->esquerda = NULL;         
        else             
            no->pai->direita = NULL;     
    }     
    free(no); 
}  

void preOrdem(No* no){     
    printf("%f ", no->v);     
    if(no->esquerda != NULL) preOrdem(no->esquerda);     
    if(no->direita != NULL) preOrdem(no->direita); 
}  

void inOrder(No* no){     
    if(no->esquerda != NULL) inOrder(no->esquerda);     
    printf("%f ", no->v);     
    if(no->direita != NULL) inOrder(no->direita); 
}  

void posOrder(No* no){     
    if(no->esquerda != NULL) posOrder(no->esquerda);     
    if(no->direita != NULL) posOrder(no->direita);     
    printf("%f ", no->v); 
}  

void largura(No* no){     
    if (no == NULL) return; // Garante que não vai quebrar se a árvore estiver vazia
         
    FSE *fila = criaFila();     
    Info dadoInicial;     
    dadoInicial.dado = no;     
    insere(fila, dadoInicial); // Insere o nó raiz na fila
         
    while(!vaziaFila(fila)){         
        Info dadoAtual;         
        remove_(fila, &dadoAtual); // Remove o nó da frente da fila
        No *aux = dadoAtual.dado;                  
        
        printf("%f ", aux->v); // CORRIGIDO: printf do valor correto usando a máscara %f
                 
        // CORRIGIDO: para busca em largura padrão, empilhamos primeiro o esquerdo depois o direito
        if(aux->esquerda != NULL) {             
            Info dadoEsq;             
            dadoEsq.dado = aux->esquerda;             
            insere(fila, dadoEsq);         
        }         
        if(aux->direita != NULL) {             
            Info dadoDir;             
            dadoDir.dado = aux->direita;             
            insere(fila, dadoDir);         
        }     
    }     
    free(fila); // Libera o ponteiro da fila da memória
}  

int main(){     
    // Questao 4     
    Arvore *a = cria();     
    adiciona(a, 4);     
    adiciona(a, 2);     
    adiciona(a, 1);     
    adiciona(a, 3);     
    adiciona(a, 8);     
    adiciona(a, 9);     
    adiciona(a, 6);     
    adiciona(a, 5);     
    adiciona(a, 7);          
    
    preOrdem(a->raiz);     
    printf("\n");      
    
    inOrder(a->raiz);     
    printf("\n");      
    
    posOrder(a->raiz);     
    printf("\n");      
    
    largura(a->raiz);     
    printf("\n"); 
}
