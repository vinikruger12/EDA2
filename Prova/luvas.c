#include <stdio.h>
#include <stdlib.h>

int main(){
    int n; scanf("%d", &n);
    int v[n], vis[n];
    for(int i = 0;i < n;i++){
        scanf("%d", &v[i]);
        vis[i] = 0;
    } 
    
    int ans = 0;
    for(int i = 0;i < (n-1);i++){
        if(vis[i] == 1) continue;
        int conta = 1;
        vis[i] = 1;
        for(int j =i+1;j < n;j++){
            if(v[i] == v[j]){
                conta++;
                vis[j] = 1;
            } 
        }
        ans += (conta/2);
    }

    printf("%d pares\n", ans);


}