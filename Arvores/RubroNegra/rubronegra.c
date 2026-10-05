#include <stdio.h>
#include <stdlib.h>

/*
    ============================================================
    ESTRUTURA DO NÓ DA ÁRVORE AVL
    ============================================================

    Diferentemente da rubro-negra, aqui não precisamos guardar cor.

    Precisamos guardar a ALTURA do nó, porque o balanceamento
    da AVL depende da diferença de altura entre:

    subárvore esquerda
    subárvore direita
*/

typedef struct no {

    int valor;

    int altura;

    struct no *esquerda;
    struct no *direita;

} No;


/*
    ============================================================
    FUNÇÃO MAIOR
    ============================================================

    Retorna o maior entre dois valores.

    Vamos usar isso para calcular a altura de cada nó.
*/

int maior(int a, int b) {

    if (a > b)
        return a;

    return b;
}


/*
    ============================================================
    ALTURA DE UM NÓ
    ============================================================

    Se o nó for NULL:

        altura = 0

    Se for uma folha:

        altura = 1
*/

int alturaNo(No *no) {

    if (no == NULL)
        return 0;

    return no->altura;
}


/*
    ============================================================
    FATOR DE BALANCEAMENTO
    ============================================================

    FB = altura esquerda - altura direita

    Em uma AVL válida:

        -1 <= FB <= 1

    Ou seja:

        FB = -1
        FB = 0
        FB = 1

    são situações normais.

    Se:

        FB = 2

    temos peso excessivo à esquerda.

    Se:

        FB = -2

    temos peso excessivo à direita.
*/

int fatorBalanceamento(No *no) {

    if (no == NULL)
        return 0;

    return alturaNo(no->esquerda)
         - alturaNo(no->direita);
}


/*
    ============================================================
    ATUALIZAR ALTURA
    ============================================================

    A altura de um nó é:

    1 + maior altura entre os filhos

    Exemplo:

          5
         /
        3

    altura do 3 = 1

    altura do 5 = 2
*/

void atualizarAltura(No *no) {

    if (no == NULL)
        return;

    no->altura =
        1 + maior(
            alturaNo(no->esquerda),
            alturaNo(no->direita)
        );
}


/*
    ============================================================
    CRIAR NÓ
    ============================================================
*/

No *criaNo(int valor) {

    No *novo = malloc(sizeof(No));


    if (novo == NULL)
        return NULL;


    novo->valor = valor;


    /*
        Todo nó recém-criado é inicialmente uma folha.

        Portanto sua altura é 1.
    */
    novo->altura = 1;


    novo->esquerda = NULL;

    novo->direita = NULL;


    return novo;
}


/*
    ============================================================
    ROTAÇÃO À DIREITA
    ============================================================

    Temos:

            Y
           /
          X

    Depois:

          X
           \
            Y

    Exemplo clássico:

            30
           /
         20
        /
       10

    Após rotação:

         20
        /  \
       10  30
*/

No *rotacionarDireita(No *y) {

    No *x = y->esquerda;


    /*
        Guardamos o filho direito de x,
        porque ele precisará mudar de posição.
    */
    No *T2 = x->direita;


    /*
        x sobe.
    */
    x->direita = y;


    /*
        T2 passa para a esquerda de y.
    */
    y->esquerda = T2;


    /*
        IMPORTANTE:

        primeiro atualizamos y,
        porque ele ficou abaixo.

        depois atualizamos x.
    */
    atualizarAltura(y);

    atualizarAltura(x);


    /*
        x virou a nova raiz dessa subárvore.
    */
    return x;
}


/*
    ============================================================
    ROTAÇÃO À ESQUERDA
    ============================================================

    É o espelho da rotação anterior.

        X
         \
          Y

    vira:

          Y
         /
        X
*/

No *rotacionarEsquerda(No *x) {

    No *y = x->direita;


    /*
        Guardamos o filho esquerdo de y.
    */
    No *T2 = y->esquerda;


    /*
        y sobe.
    */
    y->esquerda = x;


    /*
        T2 passa para a direita de x.
    */
    x->direita = T2;


    /*
        Atualizamos alturas.
    */
    atualizarAltura(x);

    atualizarAltura(y);


    /*
        y virou a nova raiz dessa subárvore.
    */
    return y;
}


/*
    ============================================================
    INSERÇÃO AVL
    ============================================================

    A inserção começa exatamente como em uma árvore
    binária de busca comum.

    Depois da inserção:

    1. atualizamos altura
    2. calculamos fator de balanceamento
    3. fazemos rotação se necessário
*/

No *inserir(No *raiz, int valor) {


    /*
        Caso base:

        encontramos a posição onde o nó deve entrar.
    */
    if (raiz == NULL) {

        return criaNo(valor);
    }


    /*
        Menor -> esquerda
    */
    if (valor < raiz->valor) {

        raiz->esquerda =
            inserir(
                raiz->esquerda,
                valor
            );
    }


    /*
        Maior -> direita
    */
    else if (valor > raiz->valor) {

        raiz->direita =
            inserir(
                raiz->direita,
                valor
            );
    }


    /*
        Não vamos permitir valores repetidos.
    */
    else {

        return raiz;
    }


    /*
        Depois de inserir,
        atualizamos a altura do nó atual.
    */
    atualizarAltura(raiz);


    /*
        Calculamos o fator de balanceamento.
    */
    int fb = fatorBalanceamento(raiz);


    /*
        ========================================================
        CASO 1: ESQUERDA - ESQUERDA
        ========================================================

             raiz
             /
          filho
          /
       novo

        Uma rotação à direita resolve.
    */

    if (
        fb > 1 &&
        valor < raiz->esquerda->valor
    ) {

        return rotacionarDireita(raiz);
    }


    /*
        ========================================================
        CASO 2: DIREITA - DIREITA
        ========================================================

        raiz
           \
           filho
              \
              novo

        Uma rotação à esquerda resolve.
    */

    if (
        fb < -1 &&
        valor > raiz->direita->valor
    ) {

        return rotacionarEsquerda(raiz);
    }


    /*
        ========================================================
        CASO 3: ESQUERDA - DIREITA
        ========================================================

             raiz
             /
          filho
              \
              novo

        Precisamos de duas rotações.

        Primeiro:

        rotação à esquerda no filho.

        Depois:

        rotação à direita na raiz.
    */

    if (
        fb > 1 &&
        valor > raiz->esquerda->valor
    ) {

        raiz->esquerda =
            rotacionarEsquerda(
                raiz->esquerda
            );

        return rotacionarDireita(raiz);
    }


    /*
        ========================================================
        CASO 4: DIREITA - ESQUERDA
        ========================================================

        raiz
           \
           filho
           /
        novo

        Primeiro rotação à direita no filho.

        Depois rotação à esquerda na raiz.
    */

    if (
        fb < -1 &&
        valor < raiz->direita->valor
    ) {

        raiz->direita =
            rotacionarDireita(
                raiz->direita
            );

        return rotacionarEsquerda(raiz);
    }


    /*
        Se não houve desbalanceamento,
        apenas devolvemos a raiz.
    */
    return raiz;
}


/*
    ============================================================
    ENCONTRAR MENOR NÓ
    ============================================================

    Essa função será usada na REMOÇÃO.

    Se um nó possui dois filhos, precisamos escolher alguém
    para substituí-lo.

    Vamos usar o SUCESSOR EM ORDEM.

    O sucessor é:

        menor valor da subárvore direita.

    Para encontrar o menor valor:

        basta continuar indo para a esquerda.
*/

No *menorNo(No *raiz) {

    No *atual = raiz;


    while (
        atual != NULL &&
        atual->esquerda != NULL
    ) {

        atual = atual->esquerda;
    }


    return atual;
}


/*
    ============================================================
    REMOÇÃO AVL
    ============================================================

    Essa é a função principal do exercício.

    Existem três casos de remoção:

    CASO 1:
        nó folha

    CASO 2:
        nó possui apenas um filho

    CASO 3:
        nó possui dois filhos

    Depois da remoção:

        precisamos atualizar as alturas
        e verificar se houve desbalanceamento.
*/

No *remover(No *raiz, int valor) {


    /*
        Se chegamos em NULL,
        o valor não existe.
    */
    if (raiz == NULL)
        return NULL;


    /*
        ========================================================
        PRIMEIRO: PROCURAMOS O VALOR
        ========================================================
    */


    /*
        Se valor é menor,
        buscamos à esquerda.
    */
    if (valor < raiz->valor) {

        raiz->esquerda =
            remover(
                raiz->esquerda,
                valor
            );
    }


    /*
        Se valor é maior,
        buscamos à direita.
    */
    else if (valor > raiz->valor) {

        raiz->direita =
            remover(
                raiz->direita,
                valor
            );
    }


    /*
        Se chegamos aqui:

        valor == raiz->valor

        Encontramos o nó.
    */
    else {


        /*
            ====================================================
            CASO 1 OU CASO 2

            O nó possui:

            nenhum filho

            OU

            apenas um filho
            ====================================================
        */

        if (
            raiz->esquerda == NULL ||
            raiz->direita == NULL
        ) {


            /*
                Descobrimos qual filho existe.

                Se esquerda existe:
                    filho = esquerda

                Caso contrário:
                    filho = direita

                Se nenhum existe:
                    filho será NULL
            */
            No *filho;


            if (raiz->esquerda != NULL) {

                filho = raiz->esquerda;
            }

            else {

                filho = raiz->direita;
            }


            /*
                ================================================
                CASO 1: NÓ FOLHA
                ================================================

                Não existe nenhum filho.

                Exemplo:

                    5

                Basta liberar o nó.
            */

            if (filho == NULL) {

                free(raiz);

                return NULL;
            }


            /*
                ================================================
                CASO 2: UM FILHO
                ================================================

                    5
                   /
                  3

                Removemos 5.

                O 3 ocupa o lugar dele.
            */

            else {

                /*
                    Guardamos o nó que será removido.
                */
                No *aux = raiz;


                /*
                    O filho assume o lugar da raiz.
                */
                raiz = filho;


                /*
                    Liberamos o antigo nó.
                */
                free(aux);
            }
        }


        /*
            ====================================================
            CASO 3: DOIS FILHOS
            ====================================================

            Exemplo exatamente do exercício:

                   6
                  / \
                 5   7

            Não podemos simplesmente apagar o 6.

            Vamos pegar seu sucessor.

            O sucessor é o menor valor
            da subárvore direita.

            Aqui será:

                7
        */

        else {


            /*
                Encontramos o sucessor.
            */
            No *sucessor =
                menorNo(
                    raiz->direita
                );


            /*
                Copiamos o valor do sucessor.

                O nó 6 passa a armazenar 7.
            */
            raiz->valor =
                sucessor->valor;


            /*
                Agora precisamos remover o 7 original.

                Como ele está na subárvore direita,
                chamamos remover novamente.
            */
            raiz->direita =
                remover(
                    raiz->direita,
                    sucessor->valor
                );
        }
    }


    /*
        ========================================================
        A REMOÇÃO TERMINOU.

        AGORA PRECISAMOS VERIFICAR A AVL.
        ========================================================

        Toda remoção pode alterar a altura da árvore.
    */


    atualizarAltura(raiz);


    /*
        Calculamos novamente o fator de balanceamento.
    */
    int fb =
        fatorBalanceamento(raiz);


    /*
        ========================================================
        CASO 1: PESADO À ESQUERDA
        E FILHO ESQUERDO PESADO À ESQUERDA
        ========================================================
    */

    if (
        fb > 1 &&
        fatorBalanceamento(
            raiz->esquerda
        ) >= 0
    ) {

        return rotacionarDireita(raiz);
    }


    /*
        ========================================================
        CASO 2: PESADO À ESQUERDA
        MAS FILHO ESQUERDO PESADO À DIREITA
        ========================================================

        Rotação dupla.
    */

    if (
        fb > 1 &&
        fatorBalanceamento(
            raiz->esquerda
        ) < 0
    ) {

        raiz->esquerda =
            rotacionarEsquerda(
                raiz->esquerda
            );


        return rotacionarDireita(raiz);
    }


    /*
        ========================================================
        CASO 3: PESADO À DIREITA
        E FILHO DIREITO PESADO À DIREITA
        ========================================================
    */

    if (
        fb < -1 &&
        fatorBalanceamento(
            raiz->direita
        ) <= 0
    ) {

        return rotacionarEsquerda(raiz);
    }


    /*
        ========================================================
        CASO 4: PESADO À DIREITA
        MAS FILHO DIREITO PESADO À ESQUERDA
        ========================================================
    */

    if (
        fb < -1 &&
        fatorBalanceamento(
            raiz->direita
        ) > 0
    ) {

        raiz->direita =
            rotacionarDireita(
                raiz->direita
            );


        return rotacionarEsquerda(raiz);
    }


    /*
        Se não houve desbalanceamento,
        devolvemos normalmente.
    */
    return raiz;
}


/*
    ============================================================
    MOSTRAR A ÁRVORE
    ============================================================

    Essa função imprime a árvore "deitada".

    A direita aparece em cima.

    A esquerda aparece embaixo.

    Exemplo:

            8
        4
            2

    significa:

        4
       / \
      2   8

    Também mostramos:

        h = altura

        fb = fator de balanceamento
*/

void imprimirArvore(
    No *raiz,
    int nivel
) {


    if (raiz == NULL)
        return;


    /*
        Primeiro imprime a direita.
    */
    imprimirArvore(
        raiz->direita,
        nivel + 1
    );


    /*
        Espaçamento proporcional ao nível.
    */
    for (
        int i = 0;
        i < nivel;
        i++
    ) {

        printf("    ");
    }


    printf(
        "%d [h=%d, fb=%d]\n",
        raiz->valor,
        raiz->altura,
        fatorBalanceamento(raiz)
    );


    /*
        Depois imprime a esquerda.
    */
    imprimirArvore(
        raiz->esquerda,
        nivel + 1
    );
}


/*
    ============================================================
    PERCURSO EM ORDEM
    ============================================================

    Em uma árvore de busca binária:

    esquerda
    raiz
    direita

    imprime os números em ordem crescente.

    Isso também ajuda a conferir se a árvore continua correta.
*/

void emOrdem(No *raiz) {

    if (raiz == NULL)
        return;


    emOrdem(
        raiz->esquerda
    );


    printf(
        "%d ",
        raiz->valor
    );


    emOrdem(
        raiz->direita
    );
}


/*
    ============================================================
    LIBERAR A MEMÓRIA
    ============================================================
*/

void liberarArvore(No *raiz) {

    if (raiz == NULL)
        return;


    liberarArvore(
        raiz->esquerda
    );


    liberarArvore(
        raiz->direita
    );


    free(raiz);
}


/*
    ============================================================
    MAIN
    ============================================================
*/

int main() {


    No *raiz = NULL;


    /*
        Vamos montar exatamente a árvore do exercício:

                4
              /   \
             2     8
            / \   / \
           1   3 6   9
                / \
               5   7

        Essa ordem de inserção mantém essa topologia.
    */

    int valores[] = {

        4,
        2,
        8,
        1,
        3,
        6,
        9,
        5,
        7
    };


    int quantidade =
        sizeof(valores)
        /
        sizeof(valores[0]);


    /*
        Inserimos todos os valores.
    */

    for (
        int i = 0;
        i < quantidade;
        i++
    ) {

        raiz =
            inserir(
                raiz,
                valores[i]
            );
    }


    /*
        ========================================================
        ÁRVORE ANTES DA REMOÇÃO
        ========================================================
    */

    printf(
        "ARVORE ANTES DA REMOCAO:\n\n"
    );


    imprimirArvore(
        raiz,
        0
    );


    printf(
        "\nEm ordem: "
    );


    emOrdem(raiz);


    printf("\n");


    /*
        ========================================================
        EXERCÍCIO:

        REMOVER O NÓ 6
        ========================================================
    */

    raiz =
        remover(
            raiz,
            6
        );


    /*
        ========================================================
        ÁRVORE DEPOIS DA REMOÇÃO
        ========================================================
    */

    printf(
        "\nARVORE DEPOIS DE REMOVER O NO 6:\n\n"
    );


    imprimirArvore(
        raiz,
        0
    );


    printf(
        "\nEm ordem: "
    );


    emOrdem(raiz);


    printf("\n");


    /*
        Liberamos toda a memória.
    */

    liberarArvore(raiz);


    return 0;
}