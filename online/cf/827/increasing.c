#include "stdio.h"
#include "stdlib.h"

int cmp(const void *a, const void *b) {
    return * (int *) a - * (int *) b; 
}

void solve() {
    int n;
    scanf("%d", &n);

    int *arr = malloc(n * sizeof *arr);
    for (int i = 0; i < n; i++) {
        scanf("%d", arr + i);
    }

    qsort(arr, n, sizeof *arr, cmp);
    
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] == arr[i + 1]) {
            free(arr);
            printf("NO\n");
            return;
        }
    }

    free(arr);
    printf("YES\n");
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}
