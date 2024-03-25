#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

#define sz(x) (int) x.size()
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define vi vector<int>
#define all(x) x.begin(), x.end()

template<class T> T edmondsKarp(vector<unordered_map<int, T>> &graph, int source, int sink) {
	T flow = 0;
	vi par(sz(graph)), q = par;

	for (;;) {
		fill(all(par), -1);
		par[source] = 0;
		int ptr = 1;
		q[0] = source;

		rep(i, 0, ptr) {
			int x = q[i];
			for (auto e : graph[x]) {
				if (par[e.first] == -1 && e.second > 0) {
					par[e.first] = x;
					q[ptr++] = e.first;
					if (e.first == sink) goto out;
				}
			}
		}
		return flow;
out:
		T inc = numeric_limits<T>::max();
		for (int y = sink; y != source; y = par[y])
			inc = min(inc, graph[par[y]][y]);

		flow += inc;
		for (int y = sink; y != source; y = par[y]) {
			int p = par[y];
			if ((graph[p][y] -= inc) <= 0) graph[p].erase(y);
			graph[y][p] += inc;
		}
	}
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	auto get_color = [](int x) {
		return x;
	};

	auto get_country = [m](int x) {
		return x + m;
	};

	int source = n + m;
	int sink = n + m + 1;

	vector<unordered_map<int, int>> graph(n + m + 2);

	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;

		graph[get_country(i)][sink] = 1;

		for (int j = 0; j < k; j++) {
			int c;
			cin >> c;
			c--;
			graph[get_color(c)][get_country(i)] = INF;
		}
	}

	for (int i = 0; i < m; i++) {
		graph[source][get_color(i)] = 1;
	}

	cout << edmondsKarp(graph, source, sink) << '\n';

    return 0;
}
