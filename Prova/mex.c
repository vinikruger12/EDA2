#include <stdio.h>
#include <stdlib.h>

int main(){
    int n; scanf("%d", &n);
    int v[n];
    int map[n+1];

    for(int i = 0;i <= n;i++) map[i] = 0;

    for(int i = 0;i < n;i++){
        scanf("%d", &v[i]);
    }

    for(int i = 0;i < n;i++){
        if(v[i] >= 0) map[v[i]] = 1;
    }


    int ans = 0;   
    for(int i = 0;i <= n;i++){
        if(map[i] == 0){
            ans = i;
            break;
        }
    }
    printf("O menor número é o %d\n", ans);

}