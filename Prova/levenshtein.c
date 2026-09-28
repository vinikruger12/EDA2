#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b){
    return a < b ? a : b;
}


int f(const char *A, const char *B){
    int m = strlen(A);
    int n = strlen(B);
    int mat[m][n];
    for(int i = 0;i < m;i++){
        mat[i][0] = i;
    }

    for(int j = 0;j < n;j++){
        mat[0][j] = j;
    }

    for(int i = 1;i < m;i++){
        for(int j = 1;j < n;j++){
            int custo = 1;
            if(A[i] == B[j]) custo = 0;
            mat[i][j] = min(min(mat[i-1][j] + 1, mat[i][j-1] + 1), mat[i-1][j-1] + custo);
        }
    }

    return mat[m-1][n-1];

}

int main(){
    char *s = "exercício";
    char *c = "exército";
    printf("%d\n", f(s, c));
}

