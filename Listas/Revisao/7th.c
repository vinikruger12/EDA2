#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo{
    int valor;
    struct Nodo *link;
} Nodo;

typedef struct Descritor{
    int tamanho;
    Nodo *inicio;
} descritor;


Nodo *intersecao(descritor *listaA, descritor *listaB){

    Nodo *auxA = listaA->inicio;
    Nodo *auxB = listaB->inicio;

    int tamA = listaA->tamanho;
    int tamB = listaB->tamanho;

    while(tamA > tamB){
        auxA = auxA->link;
        tamA--;
    }

    while(tamB > tamA){
        auxB = auxB->link;
        tamB--;
    }

    
    while(auxA != NULL && auxB != NULL){

        if(auxA == auxB){
            return auxA;
        }

        auxA = auxA->link;
        auxB = auxB->link;
    }

    return NULL;
}


int main(){

    descritor listaA;
    descritor listaB;

    Nodo *n3 = malloc(sizeof(Nodo));
    Nodo *n7 = malloc(sizeof(Nodo));
    Nodo *n8 = malloc(sizeof(Nodo));
    Nodo *n10 = malloc(sizeof(Nodo));

    Nodo *n99 = malloc(sizeof(Nodo));
    Nodo *n1 = malloc(sizeof(Nodo));


    // Valores
    n3->valor = 3;
    n7->valor = 7;
    n8->valor = 8;
    n10->valor = 10;

    n99->valor = 99;
    n1->valor = 1;



    n3->link = n7;
    n7->link = n8;
    n8->link = n10;
    n10->link = NULL;

    listaA.inicio = n3;
    listaA.tamanho = 4;


    n99->link = n1;
    n1->link = n8;

    listaB.inicio = n99;
    listaB.tamanho = 4;


    Nodo *resultado = intersecao(&listaA, &listaB);

    if(resultado != NULL){
        printf("Primeiro nodo de intersecao: %d\n", resultado->valor);
    }
    else{
        printf("As listas nao possuem intersecao.\n");
    }

    free(n3);
    free(n7);
    free(n99);
    free(n1);
    free(n8);
    free(n10);

    return 0;
}