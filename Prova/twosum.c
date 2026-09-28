#include <stdio.h>
#include <stdlib.h>

int comp(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y)
        return -1;
    if (x > y)
        return 1;
    return 0;
}

int main(){
    int n, k; scanf("%d %d", &n, &k);
    int v[n];
    for(int i = 0;i < n;i++){
        scanf("%d", &v[i]);
    }

    qsort(v, n, sizeof(v[0]), comp);

    int l = 0, r = n-1;
    int soma = 0;
    int ans = 0;
    while(l < r){
        soma = v[l] + v[r];
        if(soma > k){
            r--;
        }
        else if(soma < k){
            l++;
        }
        else{
            ans = 1;
            break;
        }
    }   

    if(ans) printf("True\n");
    else printf("False");

}