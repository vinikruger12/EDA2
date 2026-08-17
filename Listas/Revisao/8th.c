#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char c;
} info;

struct Node{
    info dados;
    struct Node *under;
};

struct stack{
    struct Node *top;
    int stackSize;
};

int vazia(struct stack *stk);
struct stack *cria();
int insert(info *reg, struct stack *stk);
int pop(struct stack *stk);
info first(struct stack *stk);
void reset(struct stack *stk);
struct stack *destroy(struct stack *stk);

int vazia(struct stack *stk){
    return (stk->stackSize == 0 || stk == NULL);
}

struct stack *cria(){
    struct stack *stk = NULL;
    stk = malloc(sizeof(struct stack));
    
    if(stk){
        stk->top = NULL;
        stk->stackSize = 0;
    }
    else return NULL;

    return stk;
}

int insert(info *reg, struct stack *stk){
    if(stk == NULL) return 0;

    struct Node *aux = NULL;
    aux = malloc(sizeof(struct Node));

    if(aux != NULL){
        memcpy(&(aux->dados), reg, sizeof(info));
        aux->under = stk->top;
        stk->top = aux;
        (stk->stackSize)++;
        return 1;
    }
    return 0;
    
}

int pop(struct stack *stk){
    struct Node *aux = NULL;
    if(!vazia(stk)){
        aux = stk->top->under;
        free(stk->top);
        stk->top = aux;
        (stk->stackSize)--;
        return 1;
    }
    return 0;
}

info first(struct stack *stk){
    if(stk == NULL || vazia(stk)){
        info k;
        return k;
    }
    return stk->top->dados;
}

void reset(struct stack *stk){
    while(pop(stk));
}

struct stack *destroy(struct stack *stk){
    if(stk == NULL) return NULL;
    reset(stk);
    free(stk);
    return NULL;
}

int main(){
    printf("Digite a quantidade de caracteres da string\n");
    int n; 
    scanf("%d", &n);
    struct stack *stk = cria();
    char s[n];
    scanf("%s", s);

    int ans = 1;

    for(int i = 0;i < n;i++){
        if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
            info *reg;
            reg->c = s[i];
            insert(reg, stk);
        }
        else{
            if(s[i] == ')'){
                if(first(stk).c != '('){
                    ans = 0;
                    break;
                }
                pop(stk);
            }
            else if(s[i] == ']'){
                if(first(stk).c != '['){
                    ans = 0;
                    break;
                }
                pop(stk);
            }
            else if(s[i] == '}'){
                if(first(stk).c != '{'){
                    ans = 0;
                    break;
                }
                pop(stk);
            }
        }

    }

    if(ans && vazia(stk)) printf("True\n");
    else printf("False\n");
}