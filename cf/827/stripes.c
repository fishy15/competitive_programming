#include "stdio.h"

void solve() {
    char grid[8][9];

    for (int i = 0; i < 8; i++) {
        scanf("%s", grid[i]);
    }

    // check row
    for (int i = 0; i < 8; i++) {
        int all_ok = 1;
        for (int j = 0; j < 8; j++) {
            if (grid[i][j] != 'R') {
                all_ok = 0;
                break;
            }
        }

        if (all_ok) {
            printf("R\n");
            return;
        }
    }

    printf("B\n");
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}
