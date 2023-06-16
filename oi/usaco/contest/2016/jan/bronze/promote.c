#include <stdio.h>
#include <stdlib.h>

int before[4];
int after[4];
int ans[3];

int main() {
    FILE* fin = fopen("promote.in", "r");
    FILE* fout = fopen("promote.out", "w");
    int i = 0;

    for (i = 0; i < 4; i++) {
        fscanf(fin, " %d", &before[i]);
        fscanf(fin, " %d", &after[i]);
        //printf("%d %d\n", before[i], after[i]);
    }

    for (i = 2; i >= 0; i--) {
        //puts("hi");
        ans[i] = after[i + 1] - before[i + 1];
        after[i] += ans[i];
    }

    fprintf(fout, "%d\n%d\n%d\n", ans[0], ans[1], ans[2]);
    return 0;
}
