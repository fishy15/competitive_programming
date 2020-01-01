#include <stdio.h>

int time[1001];

int main() {
	FILE* fin = fopen("blist.in", "r");
	FILE* fout = fopen("blist.out", "w");
	int num, i;
	int max = 0;
	fscanf(fin, "%d", &num);
	
	for (i = 0; i < num; i++) {
		int s, t, b;
		int j;
		fscanf(fin, "%d %d %d", &s, &t, &b);
		
		for (j = s; j <= t; j++) {
			time[j] += b;
		}
	}
	
	for (i = 0; i < 1001; i++) {
		max = time[i] > max ? time[i] : max;
	}
	
	fprintf(fout, "%d\n", max);
	return 0;
}

