#include "stdio.h"
#include "stdlib.h"

int gcd(int a, int b) {
    return a == 0 ? b : gcd(b % a, a);
}

int max(int a, int b) {
    return a > b ? a : b;
}

void solve() {
    int n;
    scanf("%d", &n);

    int max_match[1001];
    for (int i = 0; i < 1001; i++) {
        max_match[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        max_match[x] = i + 1;
    }

    int ans = -1;
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            if (gcd(i, j) == 1 && max_match[i] != -1 && max_match[j] != -1) {
                ans = max(ans, max_match[i] + max_match[j]);
            }
        }
    }

    printf("%d\n", ans);
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}
