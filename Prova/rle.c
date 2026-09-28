#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Digite o tamanho da string\n");
    int c; scanf("%d", &c);
    char s[c];
    scanf("%s", s);

    int out = 0;
    for(int i = 1;s[i] != 0;i++){
        out++;
        if(s[i] != s[i-1]){
            printf("%d%c",out, s[i-1]);
            out = 0;
        }
    }
    out++;
    printf("%d%c\n",out,s[c-1]);

}