#include <stdio.h>
#include <stdlib.h>

int min(int a, int b){
    return a < b ? a : b;
}

int max(int a, int b){
    return a > b ? a : b;
}

int main(){
    int n; scanf("%d", &n);
    char c[n];
    char s[n];
    scanf("%s", c);
    scanf("%s", s);

    int ans = 0;

    for(int i = 0;i < n;i++){
        if(c[i] == s[0]){
            int idC = i + 1;
            if(idC == n) idC = 0;
            int idS = 1;
            int falso = 1;

            if(s[idS] != c[idC]){
                falso = 0;
                break;
            }

            while(idC != i){
                
                idC = (idC % n) + 1;
                if(idC == n) idC = 0;
                idS++;
                
                if(idC == i) break;



                if(s[idS] != c[idC]){
                    falso = 0;
                    break;
                }
                
                
            }
            if(falso == 1){
                ans = 1;
                break;
            }
        }
    }

    if(ans == 1) printf("True\n");
    else printf("False\n");

}