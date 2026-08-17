#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maior(int a, int b){
    if(a > b) return a;
    return b;
}

int main(){
    int n;
    scanf("%d", &n);

    int k;
    scanf("%d", &k);

    int v[n];   
    

    for(int i = 0;i < n;i++){
        scanf("%d", &v[i]);
    }

    int vetor[n - k + 1];

    int u = 0;
    int o = k;
    int maxx = v[0];
    for(int i = 0;i < (n - k + 1);i++){
        maxx = v[i];
        o = k;
        for(int j = i;o--;j++){
            maxx = maior(maxx, v[j]);
        }
        vetor[u] = maxx;
        u++;
    }

    for(int i = 0;i < n - k + 1;i++){
        printf("%d\n", vetor[i]);
    }

}