#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000
int nums[MAXN];

int int_cmp(void const *a, void const *b) {
    return *(int *) a - *(int *) b;
}

void solve() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    qsort(nums, n, sizeof(*nums), int_cmp);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] > ans) {
            ans++;
        }
    }

    printf("%d\n", ans);
}

int main() {
    int t;
    scanf("%d", &t);

    for (int i = 1; i <= t; i++) {
        printf("Case #%d: ", i);
        solve();
    }
}
