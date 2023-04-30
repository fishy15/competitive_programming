#include "stdio.h"
#include "stdlib.h"

int max(int a, int b) {
    return a > b ? a : b;
}

void solve() {
    int n, q;
    scanf("%d %d", &n, &q);

    int *h = malloc(n * sizeof *h);
    for (int i = 0; i < n; i++) {
        scanf("%d", h + i);
    }

    long long *psum = malloc((n + 1) * sizeof *psum);
    psum[0] = 0;
    for (int i = 0; i < n; i++) {
        psum[i + 1] = psum[i] + h[i];
        if (i > 0) {
            h[i] = max(h[i], h[i - 1]);
        }
    }

    for (int i = 0; i < q; i++) {
        int k;
        scanf("%d", k);

        int l = 0;
        int r = n - 1;
        int ans = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (h[m] <= k) {
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }

        printf("%lld ", psum[ans + 1]);
    }

    printf("\n");
    free(h);
    free(psum);
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}
