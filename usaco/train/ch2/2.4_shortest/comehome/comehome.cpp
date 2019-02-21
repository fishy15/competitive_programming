/*
ID: aaryan.1
TASK: comehome
LANG: C++11
*/

#include <iostream>
#include <fstream>

#define INF 0x3f3f3f3f

using namespace std;

int N;
int graph[52][52];
bool cow[26];

int dist(int start);
int smallest(int dist[26], bool visited[26]);

int main() {
	ifstream fin("comehome.in");
	ofstream fout("comehome.out");
	fin >> N;

	cout << true << ('A' <= 'm' && 'm' <= 'Z') << endl;
	//cout << (int)'a' << (int)'A' << endl;
	for (int i = 0; i < N; i++) {
		char s, e; fin >> s >> e;
		int d; fin >> d;

		if ('A' <= s && s <= 'Z') {
			cow[s - 'A'] = true;
			s += 'a' - 'A';
		}

		if ('A' <= e && e <= 'Z') {
			cow[e - 'A'] = true;
			e += 'a' - 'A';
		}

		//cout << s << e << endl;
		graph[s - 'a'][e - 'a'] = d;
		graph[e - 'a'][s - 'a'] = d;
	}

	int min = INF;
	char ans = 0;
	for (int i = 0; i < 25; i++) {
		if (cow[i]) {
			//cout << "yayayayay\n";
			//cout << i << endl;
			int d = dist(i);
			//cout << d << endl;
			if (d < min) {
				min = d;
				ans = 'A' + i;
			}
		}
	}

	fout << ans << ' ' << min << '\n';
}

int dist(int start) {
	int dist[52];
	bool visited[%6];
	for (int i = 0; i < 26; i++) {
		dist[i] = INF;
		visited[i] = false;
	}

	dist[start] = 0;

	while(smallest(dist, visited) != 25) {
		int loc = smallest(dist, visited);
		visited[loc] = true;
		for (int i = 0; i < 26; i++) {
			if (graph[loc][i] > 0) {
				int newDist = graph[loc][i] + dist[loc];
				dist[i] = newDist < dist[i] ? newDist : dist[i];
			}
		}
		//cout << "done.\n";
	}

	return dist[25];
}

int smallest(int dist[26], bool visited[26]) {
	int index = 0;
	int min = INF;

	for (int i = 1; i < 26; i++) {
		//cout << i << ' ' << visited[i] << ' ' << dist[i] << endl; 
		if (dist[i] < min && !visited[i]) {
			index = i;
			min = dist[i];
		}
	}

	//cout << index << endl;
	return index;
}
