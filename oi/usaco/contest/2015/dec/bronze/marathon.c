#include <stdio.h>
#include <stdlib.h>

#define N_MAX 100000

int N;
int x[N_MAX];
int y[N_MAX];

int dist(int i1, int i2) {
	int diffX = abs(x[i1] - x[i2]);
	int diffY = abs(y[i1] - y[i2]);
	return diffX + diffY;
}

int main() {
	FILE *fin = fopen("marathon.in", "r");
	FILE *fout = fopen("marathon.out", "w");
	int i = 0, maxDiff = 0, total = 0;
	fscanf(fin, "%d", &N);

	for (i = 0; i < N; i++) {
		fscanf(fin, "%d %d", &x[i], &y[i]);
	}

	for (i = 1; i < N - 1; i++) {
		int diff = 0;
		//printf("%d\n", dist(i, i - 1)); 
		total += dist(i, i - 1);
		diff = dist(i, i - 2) - dist(i, i - 1) - dist(i - 1, i - 2);
		//printf("%d\n", diff);	
		if (diff < maxDiff) {
			maxDiff = diff;
		}
	}

	total += dist(N - 1, N - 2);
	//printf("%d\n", total);

	fprintf(fout, "%d\n", total + maxDiff);
	return 0;
}
