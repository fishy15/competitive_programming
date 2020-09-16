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
#define MAXN 1010

using namespace std;

int n, m;
string grid[MAXN];
int dsu[MAXN][MAXN];
int sz[MAXN][MAXN];
set<int> in[MAXN][MAXN];
bool vis[MAXN][MAXN];

int get(int y, int x) {
    if (dsu[y][x] == x) return x;
    return dsu[y][x] = get(y, dsu[y][x]);
}

void join(int y, int i, int j) {
    if ((i = get(y, i)) != (j = get(y, j))) { 
        if (sz[y][i] < sz[y][j]) swap(i, j);
        dsu[y][j] = i;
        sz[y][i] += sz[y][j];
        for (int k : in[y][j]) in[y][i].insert(k);
    }
}

ll solve(int i, int pos) {
    ll ans = 1;
    vis[i][pos] = true;
    for (int j : in[i][pos]) {
        if (grid[i + 1][j] == '.' && !vis[i + 1][get(i + 1, j)]) {
            ll res = solve(i + 1, get(i + 1, j));
            ans = ans * res % MOD;
        }
    }
    ans++;
    return ans % MOD;
}

int main() {
    ifstream fin("cave.in");
    ofstream fout("cave.out");

    fin >> n >> m;
    for (int i = 0; i < n; i++) {
        fin >> grid[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dsu[i][j] = j;
            sz[i][j] = 1;
            in[i][j] = {j};
        }
    }

    for (int i = n - 2; i > 0; i--) {
        for (int j = 0; j < m - 1; j++) {
            // connected below already
            if (grid[i][j] == '.' && grid[i + 1][j] == '.' && !vis[i + 1][get(i + 1, j)]) {
                int pos = get(i + 1, j);
                vis[i + 1][pos] = true;
                for (int k : in[i + 1][pos]) {
                    if (grid[i][k] == '.') join(i, j, k);
                }
            }
            
            // connected adjacent level
            if (grid[i][j] == '.' && grid[i][j + 1] == '.') {
                join(i, j, j + 1);
            }
        }
    }

    memset(vis, 0, sizeof vis);

    ll ans = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.') {
                int pos = get(i, j);
                if (!vis[i][pos]) {
                    ll val = solve(i, pos);
                    ans = val * ans % MOD;
                }
            }
        }
    }

    fout << ans << '\n';

    return 0;
}
