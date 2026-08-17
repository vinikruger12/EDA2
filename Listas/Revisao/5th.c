#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int v[n+1];
    v[0] = 1;
    v[1] = 1;

    for(int i = 2;i <= n;i++){
        v[i] = v[i-1] + v[i-2];
    }

    printf("%d\n", v[n]);

}