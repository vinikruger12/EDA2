#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    printf("Digite a quantidade de caracteres da string\n");
    int n; 
    scanf("%d", &n);
    char s[n];
    scanf("%s", s);

    char atual = s[0];
    int k = 0;
    char new[n];
    int u = 0;
    int total = 0;
    for(int i = 0;i < n;i++){
        if(s[i] != atual){
            new[u] = (k + 48);
            u++;
            new[u] = atual;
            u++;
            atual = s[i];
            k = 1;
            total += 2;
        }
        else k++;
    }

    new[u] = (k + 48);
    u++;
    new[u] = atual;
    u++;
    total += 2;

    for(int i = 0;i < total;i++){
        printf("%c", new[i]);
    }
    printf("\n");
    

}