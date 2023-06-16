#include "stdio.h"

void solve() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    if (a == b + c || b == a + c || c == a + b) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}
