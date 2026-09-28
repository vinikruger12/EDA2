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


int max(int a, int b){
    return a > b ? a : b;
}

// AVLs

int altura(No* no){
    int esquerda = 0,direita = 0;

    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }
    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }
        
    return max(direita, esquerda);
}

int fb(No* no) {
    
    int esquerda = 0,direita = 0;
    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }
        
    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }

    return esquerda - direita;
}

No* rse(Arvore* arvore, No* no) {
    No* pai = no->pai;
    No* direita = no->direita;
    No* meio = direita->esquerda;

    direita->esquerda = no;
    no->direita = meio;

    direita->pai = pai;
    no->pai = direita;

    if(meio != NULL)
        meio->pai = no;

    if(pai == NULL) {
        arvore->raiz = direita;
    }
    else if(pai->esquerda == no) {
        pai->esquerda = direita;
    }
    else {
        pai->direita = direita;
    }

    return direita;
}

No* rsd(Arvore* arvore, No* no) {
    No* pai = no->pai;
    No* esquerda = no->esquerda;
    No* meio = esquerda->direita;

    esquerda->direita = no;
    no->esquerda = meio;

    esquerda->pai = pai;
    no->pai = esquerda;

    if(meio != NULL)
        meio->pai = no;

    if(pai == NULL) {
        arvore->raiz = esquerda;
    }
    else if(pai->esquerda == no) {
        pai->esquerda = esquerda;
    }
    else {
        pai->direita = esquerda;
    }

    return esquerda;
}

No* rde(Arvore* arvore, No* no) {
    rsd(arvore, no->direita);
    return rse(arvore, no);
}

No* rdd(Arvore* arvore, No* no) {
    rse(arvore, no->esquerda);
    return rsd(arvore, no);
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
        no->pai = NULL;         
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
    
    No *auxiliar = no;
    while(auxiliar != NULL) {

        int fator = fb(auxiliar);

        if(fator > 1) {

            if(fb(auxiliar->esquerda) >= 0) {
                auxiliar = rsd(arvore, auxiliar);
            }
            else {
                auxiliar = rdd(arvore, auxiliar);
            }

        }
        else if(fator < -1) {

            if(fb(auxiliar->direita) <= 0) {
                auxiliar = rse(arvore, auxiliar);
            }
            else {
                auxiliar = rde(arvore, auxiliar);
            }

        }

        auxiliar = auxiliar->pai;
    }


    return; 
}  

void verificarBalanceamento(Arvore* arvore, No* no){

    while(no->pai != NULL) {

        int fator = fb(no);

        if(fator > 1) {

            if(fb(no->esquerda) >= 0) {
                no = rsd(arvore, no);
            }
            else {
                no = rdd(arvore, no);
            }

        }
        else if(fator < -1) {

            if(fb(no->direita) <= 0) {
                no = rse(arvore, no);
            }
            else {
                no = rde(arvore, no);
            }

        }

        no = no->pai;
    }

    return;

}

void remover(Arvore* arvore, float valor){

    No *no = arvore->raiz;

    while(no != NULL && no->v != valor){

        if(valor < no->v) no = no->esquerda;        
        else no = no->direita;
    }

    if(no == NULL) return;

    if(no->esquerda != NULL && no->direita != NULL){

        No *auxiliar = no->direita;
        while(auxiliar->esquerda != NULL){
            auxiliar = auxiliar->esquerda;
        }

        no->v = auxiliar->v;
        no = auxiliar;
    }

    No *filho;

    if(no->esquerda != NULL) filho = no->esquerda;
    else filho = no->direita;
    
    No *pai = no->pai;

    if(filho != NULL){
        filho->pai = pai;
    }

    if(pai == NULL) arvore->raiz = filho;
    else if(pai->esquerda == no) pai->esquerda = filho;
    else pai->direita = filho;
    
    free(no);

    if(pai != NULL){
        verificarBalanceamento(arvore, pai);
    }
    else if(filho != NULL){
        verificarBalanceamento(arvore, filho);
    }
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

    if (no == NULL) return; 
         
    FSE *fila = criaFila();     
    Info dadoInicial;     
    dadoInicial.dado = no;     
    insere(fila, dadoInicial); 
         
    while(!vaziaFila(fila)){         
        Info dadoAtual;         
        remove_(fila, &dadoAtual); 
        No *aux = dadoAtual.dado;                  
        
        printf("%f ", aux->v); 
                 
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

    free(fila); 
}  

int main(){     
    Arvore *a = cria();     
    
    adiciona(a, 4); 
    adiciona(a, 2);     
    adiciona(a, 8);     
    adiciona(a, 1);     
    adiciona(a, 3); 
    adiciona(a, 6);     
    adiciona(a, 9);     
    adiciona(a, 5);     
    adiciona(a, 7); 
    
    remover(a, 6);

    largura(a->raiz);     
    printf("\n"); 
}
