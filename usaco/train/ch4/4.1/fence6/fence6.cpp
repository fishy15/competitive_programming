/*
ID: aaryan.1
TASK: fence6
LANG: C++14
*/
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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct Graph {
    int n = 0;
    vector<vector<pair<int, int>>> adj;
    vector<int> dist;

    void add_edge(int u, int v, int w) {
        n = max(n, max(u, v) + 1);
        adj.resize(n);
        dist.resize(n);

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int solve() {
        int ans = INF;
        for (int i = 0; i < n; i++) {
            for (auto e : adj[i]) {
                ans = min(ans, dijk(i, e.first, e.second));
            }
        }
        
        return ans;
    }

    int dijk(int u, int v, int w) {
        priority_queue<array<int, 2>, vector<array<int, 2>>, greater<>> pq;
        fill(dist.begin(), dist.end(), INF);
        dist[u] = 0;
        pq.push({0, u});

        while (!pq.empty()) {
            int a = pq.top()[1], d = pq.top()[0];
            pq.pop();
            if (dist[a] < d) continue;

            for (auto e : adj[a]) {
                if (a == u && e.first == v && e.second == w) continue;

                int b = e.first;
                int nd = e.second + d;

                if (nd < dist[b]) {
                    dist[b] = nd;
                    pq.push({nd, b});
                }
            }
        }

        return dist[v] + w;
    }
};

struct Edge {
    int w;
    vector<int> n1, n2;
};

int n;
vector<Edge> edges;
vector<vector<int>> nodes;

int main() {
    ifstream fin("fence6.in");
    ofstream fout("fence6.out");

    fin >> n;

    for (int i = 0; i < n; i++) {
        int s, l, n1, n2; 
        fin >> s >> l >> n1 >> n2;

        vector<int> e1, e2;
        for (int j = 0; j < n1; j++) {
            int x; fin >> x;
            e1.push_back(x);
        }
        e1.push_back(s);
        sort(e1.begin(), e1.end());

        for (int j = 0; j < n2; j++) {
            int x; fin >> x;
            e2.push_back(x);
        }
        e2.push_back(s);
        sort(e2.begin(), e2.end());

        edges.push_back({l, e1, e2});
        nodes.push_back(e1);
        nodes.push_back(e2);
    }

    sort(nodes.begin(), nodes.end());
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

    Graph g;
    for (const auto &e : edges) {
        int u = find(nodes.begin(), nodes.end(), e.n1) - nodes.begin();
        int v = find(nodes.begin(), nodes.end(), e.n2) - nodes.begin();
        g.add_edge(u, v, e.w);
    }

    fout << g.solve() << '\n';

    return 0;
}
