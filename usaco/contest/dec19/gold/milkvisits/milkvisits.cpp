// :pray: :steph:
// :pray: :bakekaga:

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
#define MAXN 100000
#define MAXBIT (2 * MAXN + 10)

using namespace std;

int n, m;
vector<int> adj[MAXN + 1];
vector<pair<int, int>> types;
vector<array<int, 4>> q;
int in[MAXN + 1];
int out[MAXN + 1];
int up[MAXN + 1][18];
int ans[MAXN + 1];
int t = 1;

int bit[MAXBIT];

void dfs(int v, int p) {
    in[v] = t++;

    up[v][0] = p;
    for (int i = 1; i < 18; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }

    for (int i : adj[v]) {
        if (i != p) {
            dfs(i, v);
        }
    }

    out[v] = t++;
}

bool is_ancestor(int a, int b) {
    return in[a] <= in[b] && out[b] <= out[a];
}

int lca(int a, int b) {
    if (is_ancestor(a, b)) {
        return a;
    }

    if (is_ancestor(b, a)) {
        return b;
    }

    for (int i = 17; i >= 0; i--) {
        if (!is_ancestor(up[a][i], b)) {
            a = up[a][i];
        }
    }
    
    return up[a][0];
}

void update(int x, int v) {
    while (x < MAXBIT) {
        bit[x] += v;
        x += x & -x;
    }
}

int query(int x) {
    int ans = 0;
    while (x) {
        ans += bit[x];
        x -= x & -x;
    }

    return ans;
}

int main() {
    ifstream fin("milkvisits.in");
    ofstream fout("milkvisits.out");

    fin >> n >> m;

    for (int i = 1; i <= n; i++) {
        int x; fin >> x;
        types.push_back({x, i});
    }

    sort(types.begin(), types.end());

    for (int i = 0; i < n - 1; i++) {
        int a, b; fin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 1);

    for (int i = 0; i < m; i++) {
        int a, b, c; fin >> a >> b >> c;
        q.push_back({c, a, b, i});
    }

    sort(q.begin(), q.end());

    int pos = 0;
    int pos2 = 0;
    for (int i = 1; i <= n; i++) {
        /* cout << i << '\n'; */
        vector<int> todo;
        while (pos < n && types[pos].first == i) {
            /* cout << '\t' << pos << '\n'; */
            update(in[types[pos].second], 1); 
            update(out[types[pos].second], -1);
            todo.push_back(types[pos].second);
            pos++;
        }

        while (pos2 < m && q[pos2][0] == i) {
            /* cout << "\t\t" << pos2 << ' '; */
            int a = q[pos2][1];
            int b = q[pos2][2];
            int l = lca(a, b);
            /* cout << a << ' ' << b << ' ' << l << '\n'; */
            int cnt1 = query(in[a]) - query(in[l] - 1);
            int cnt2 = query(in[b]) - query(in[l] - 1);
            /* cout << cnt1 << ' ' << cnt2 << '\n'; */
            ans[q[pos2][3]] = (cnt1 > 0) || (cnt2 > 0);
            pos2++;
        }

        for (int i : todo) {
            /* cout << "\t\t\t" << i << '\n'; */
            update(in[i], -1);
            update(out[i], 1);
        }
    }

    for (int i = 0; i < m; i++) {
        fout << ans[i];
    } fout << '\n';

    return 0;
}
