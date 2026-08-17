#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    int v[n];
    int produto = 1;
    for(int i = 0;i < n;i++){
        scanf("%d", &v[i]);
        produto *= v[i];
    }
    
    int ans[n];
    int aux = produto;
    for(int i = 0;i < n;i++){
        aux = produto;
        ans[i] = (produto / v[i]);
    }

    for(int i = 0;i < n;i++){
        printf("v[%d] = %d \n", i, ans[i]);
    }


}