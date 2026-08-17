#include <stdio.h>

void powerSet(int v[], int n) {
    int totalSubsets = 1 << n; 

    for(int mask = 0; mask < totalSubsets; mask++){
        printf("{ ");
        for (int i = 0; i < n; i++) {

            if (mask & (1 << i)) {
                printf("%d ", v[i]);
            }
        }
        printf("}\n");
    }
}

int main() {
    int v[] = {1, 2, 3};
    int n = sizeof(v) / sizeof(v[0]);

    powerSet(v, n);

    return 0;
}