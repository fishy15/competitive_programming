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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200000

using namespace std;

int n, m;
vector<int> adj[MAXN];
vector<int> radj[MAXN];

int vis[MAXN];
vector<int> ord;

int vis2[MAXN];
int ans[MAXN];
int assign[MAXN];

void dfs(int v) {
    vis[v] = true;
    for (int e : adj[v]) {
        if (!vis[e]) dfs(e);
    }
    ord.push_back(v);
}

void dfs2(int v, int pos) {
    ans[v] = pos;
    vis2[v] = true;
    for (int e : radj[v]) {
        if (!vis2[e]) dfs2(e, pos);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        char sgn1, sgn2;
        int p1[2], p2[2];
        cin >> sgn1 >> p1[0] >> sgn2 >> p2[0];
        p1[0]--; p2[0]--;
        p1[1] = p1[0] + n;
        p2[1] = p2[0] + n;
        if (sgn1 == '-') swap(p1[0], p1[1]);
        if (sgn2 == '-') swap(p2[0], p2[1]);
        adj[p1[1]].push_back(p2[0]);
        adj[p2[1]].push_back(p1[0]);
        radj[p1[0]].push_back(p2[1]);
        radj[p2[0]].push_back(p1[1]);
    }

    for (int i = 0; i < 2 * n; i++) {
        if (!vis[i]) dfs(i);
    }

    int cnt = 1;
    reverse(ord.begin(), ord.end());

    for (int i : ord) {
        if (!vis2[i]) dfs2(i, cnt++);
    }

    for (int i = 0; i < n; i++) {
        if (ans[i] == ans[i + n]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        } else {
            assign[i] = ans[i] > ans[i + n];
        }
    }

    for (int i = 0; i < n; i++) {
        cout << (assign[i] ? "+ " : "- ");
    }
    cout << '\n';

    return 0;
}
