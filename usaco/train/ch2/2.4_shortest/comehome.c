/*
ID: aaryan.1
TASK: comehome
LANG: C
*/

#include <stdio.h>
#include <stdlib.h>

#define INF 0x3f3f3f3f

typedef int bool;
#define true 1
#define false 0

int N;
int graph[52][52];
bool cow[26];

int dist(int start);
int smallest(int dist[52], bool visited[52]);

int main() {
	FILE *fin = fopen("comehome.in", "r");
	FILE *fout = fopen("comehome.out", "w");
	int min = INF;
	char ans = 0;
	int i;

	fscanf(fin, "%d", &N);

	for (i = 0; i < N; i++) {
		char s, e;
		int d, convS, convE;
		fscanf(fin, " %c %c %d", &s, &e, &d);
		//printf("%c %c\n", s, e);
		if ('A' <= s && s <= 'Z') {
			cow[s - 'A'] = true;
			convS = s - 'A';
		} else {
			convS = s - 'a' + 26;
		}

		if ('A' <= e && e <= 'Z') {
			//printf("%d %d\n", e, 'Z');
			cow[e - 'A'] = true;
			convE = e - 'A';
		} else {
			//printf("hi\n");
			convE = e - 'a' + 26;
		}

		//printf("%d %d\n", s, e);
		if (graph[convS][convE] == 0) {
			graph[convS][convE] = d;
			graph[convE][convS] = d;
		} else if (d < graph[convS][convE]) {
			graph[convS][convE] = d;
			graph[convE][convS] = d;
		}
	}

	/*
	for (int i = 0; i < 52; i++) {
		for (int j = 0; j < 52; j++) {
			printf("%4d ", graph[i][j]);
		}
		printf("\n");
	}
	*/

	for (i = 0; i < 25; i++) {
		//printf("%d\n", i);
		if (cow[i]) {
			int d = dist(i);

			if (d < min) {
				min = d;
				ans = 'A' + i;
			}
		}
	}

	fprintf(fout, "%c %d\n", ans, min);
	return 0;
}

int dist(int start) {
	int dist[52];
	bool visited[52];
	int loc = start;

	for (int i = 0; i < 52; i++) {
		dist[i] = INF;
		visited[i] = false;
	}

	dist[start] = 0;
		
	while(loc != 25) {
		//printf("%d\n", loc);
		visited[loc] = true;
		for (int i = 0; i < 52; i++) {
			if (graph[loc][i] > 0 && !visited[i]) {
				int newDist = graph[loc][i] + dist[loc];
				dist[i] = newDist < dist[i] ? newDist : dist[i];
			}
		}

		loc = smallest(dist, visited);
	}

	return dist[25];
}

int smallest(int dist[52], bool visited[52]) {
	int index = -1;
	int min = INF;


	for (int i = 0; i < 52; i++) {
		//printf("%d ", visited[i]);
		if (dist[i] < min && !visited[i]) {
			index = i;
			min = dist[i];
		}
	}

	return index;
}
