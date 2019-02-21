#include <iostream>
#include <vector>

#define vi vector<int>
#define vvi vector<vector<int>>

using namespace std;

vector<node> graph;
int N, M;

typedef struct node node;

struct node {
	int num;
	vector<int> next;
	vector<int> prev;
	bool visited;

	node(int i) {
		num = i;
		visited = false;
	}
};


int main() {
	cin >> N >> M;
	for (int i = 0; i <= N; i++) {
		graph.push_back(node(i));
	}

	for (int i = 0; i < M; i++) {
		int x, y; cin >> x >> y;
		graph[x].next.push_back(y);
		graph[y].prev.push_back(x);
	}

	for (int i = 0; i < 
