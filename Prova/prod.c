#include <stdio.h>
#include <stdlib.h>

int main(){
    int n; scanf("%d", &n);
    int v[n];
    int prod = 1;
    for(int i = 0;i < n;i++){
        scanf("%d", &v[i]);
        prod *= v[i];
    }

    for(int i = 0;i < n;i++){
        printf("%d ", prod / v[i]);
    }
    printf("\n");

}