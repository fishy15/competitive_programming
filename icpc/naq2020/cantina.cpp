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
#include <sstream>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n;
map<string, int> m;
int cur;

struct person {
    int lang;
    vector<int> understand;
};

vector<person> ppl;

struct graph {
    int n;
    vector<vector<int>> adj;
    vector<vector<int>> radj;
    vector<bool> vis;
    vector<int> ord;
    vector<int> cur;
    int t;
    graph(int n) : n(n) {
        adj.resize(n);
        radj.resize(n);
        vis.resize(n);
    }
    void add_edge(int a, int b) {
        adj[a].push_back(b);
        radj[b].push_back(a);
    }
    void dfs1(int v) {
        vis[v] = true;
        for (int e : adj[v]) {
            if (!vis[e]) {
                dfs1(e);
            }
        }
        ord.push_back(v);
    }
    void dfs2(int v) {
        vis[v] = true;
        cur.push_back(v);
        for (int e : radj[v]) {
            if (!vis[e]) {
                dfs2(e);
            }
        }
    }
    int solve() {
        vis.assign(n, false);
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs1(i);
            }
        }
        vis.assign(n, false);
        int ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            int v = ord[i];
            if (!vis[v]) {
                dfs2(v);
                int cnt = 0;
                for (int j : cur) {
                    if (j < ::n) {
                        cnt++;
                    }
                }
                ans = max(ans, cnt);
                cur = {};
            }
        }
        return ans;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    cur = n;

    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        cin >> s;
        ppl.emplace_back();
        if (!m.count(s)) m[s] = cur++;
        ppl.back().lang = m[s];
        ppl.back().understand.push_back(m[s]);

        getline(cin, s);
        stringstream ss(s);

        while (ss) {
            ss >> s;
            if (!m.count(s)) m[s] = cur++;
            ppl.back().understand.push_back(m[s]);
        }
    }

    graph g(cur);
    for (int i = 0; i < n; i++) {
        g.add_edge(i, ppl[i].lang);
        for (int j : ppl[i].understand) {
            g.add_edge(j, i);
        }
    }

    cout << n - g.solve() << '\n';

    return 0;
}
