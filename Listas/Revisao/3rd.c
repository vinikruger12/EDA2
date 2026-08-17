#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int n;
    scanf("%d", &n);
    int v[n];
    int aux[n+1];
    memset(aux, 0, sizeof(aux));

    for(int i = 0;i < n;i++){
        scanf("%d", &v[i]);
        if(v[i] >= 0 && v[i] <= n){
            aux[v[i]] = 1;
        }
    }

    int ans = 0;
    for(int i = 0;i < n+1;i++){
        if(aux[i] == 0){
            ans = i;
            break;
        }
    }

    printf("%d\n", ans);

}