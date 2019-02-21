#include <stdio.>
#include <stdlib.h>

#define MAX_BARN 40000
#define true 1
#define false 0

int B, E, P, N, M;
int barns[MAX_BARN + 1][MAX_BARN + 1];
int cows1[MAX_BARN + 1];
int cows2[MAX_BARN + 1];
int together[MAX_BARN + 1];
int cur[MAX_BARN + 1];
int curNum;

void distCows(int dist[]) {
    int i, j;
    int curNum2 = 0;
    for (i = 0; i < curNum; i++) {
        int curPoint = cur[i];
        for (j = 2; j <= M; j++) {
            if (barns[curPoint][j] && (dist[j] == 0 || dist[j] > dist[curPoint] + 1)) {
                dist[j] = dist[curPoint] + 1;
                cur[curNum2++] = j;
            }
        }
    }

    curNum = curNum2;
    if (curNum > 0) {
        distCows(dist);
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", dist[i]);
    }

    printf("\n");
}

int main() {
    FILE* fin = fopen("piggyback.in", "r");
    FILE* fout = fopen("piggyback.out", "w");
    int i = 0;

    fscanf(fin, "%d %d %d %d %d", &B, &E, &P, &N, &M);
    for (i = 0; i < M; i++) {
        int x, y;
        fscanf(fin, "%d %d", &x, &y);
        barns[x][y] = true;
        barns[y][x] = true;
    }

    cur[0] = 1;
    curNum = 1;
    distCows(cows1);

    cur[0] = 2;
    curNum = 1;
    distCows(cows2); 

    cur[0] = N;
    curNum = 1;
    distCows(together);

    int minimum = 1000000007;
    for (int i = 1; i <= N; i++) {
        int res = cows1[i] * B + cows2[i] * E + together[i] * P;
        minimum = res < minimum ? res : minimum;
    }

    printf("%d\n", minimum);

    exit(0);
}
