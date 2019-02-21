/* great
 * *xxxxxxxxx
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define true 1
#define false 0

int N, T;
int cows[MAX_N];

int works(int x) {
    int maxT = 0;
    int i; 

    //printf("testing %d:\n", x);

    for (i = 0; i < x; i++) {
        int sum = 0;
        int j;

        for (j = i; j < N; j += x) {
            sum += cows[j];
        }
        
        maxT = maxT > sum ? maxT : sum;
        //printf("%d\n", sum);
    }

    return maxT <= T;
}

int main() {
    FILE* fin = fopen("cowdance.in", "r");
    FILE* fout = fopen("cowdance.out", "w");
    int i;
    int min, max;

    fscanf(fin, "%d %d", &N, &T);

    for (i = 0; i < N; i++) {
        fscanf(fin, "%d", &cows[i]);
    }

    for (int i = 1; i <= N; i++) {
        printf("%d\n", works(i));
    }

    min = 1;
    max = N;
    while (min < max) {
        //printf("%d %d\n", min, max);
        int mid = (min + max) / 2;

        if (works(mid)) {
            max = mid;
        } else {
            min = mid + 1;
        }
    }

    //printf("%d\n", min);
    fprintf(fout, "%d\n", min);
    return 0;
}
