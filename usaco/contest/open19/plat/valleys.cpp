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
#define MAXN 750

using namespace std;

int n;
int dsu[577600]; // 760^2
int sz[577600];
int curve[577600];
int grid[760][760];

int pos(int i, int j) {
    return 752 * i + j;
}

int find(int a) {
    if (a == dsu[a]) return a;
    return dsu[a] = find(dsu[a]);
}

void join(int a, int b) {
    if ((a = find(a)) != (b = find(b))) {
        if (sz[b] > sz[a]) swap(a, b);
        dsu[b] = dsu[a];
        sz[a] += sz[b];
        curve[a] += curve[b];
    }
}

int corner(bool left, bool diag, bool down) {
    if (!diag) {
        if (!left && !down) {
            return 1;
        } else if (!left || !down) {
            return -1;
        } 
        return -3;
    }

    if (!left && !down) {
        return 1;
    } else if (!left || !down) {
        return -1;
    }

    return 1;
}

bool same(int i, int j, int x, int y) {
    return find(pos(i, j)) == find(pos(i + x, j + y));
}

int main() {
    ifstream fin("valleys.in");
    ofstream fout("valleys.out");

    fin >> n;

    vector<array<int, 3>> q;

    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= n + 1; j++) {
            int v = pos(i, j);
            dsu[v] = v;
            sz[v] = 1;
            grid[i][j] = INF;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x; fin >> x;
            grid[i][j] = x;
            q.push_back({x, i, j});
        }
    }

    sort(q.begin(), q.end());

    ll ans = 0;

    for (const auto &v : q) {
        int i = v[1];
        int j = v[2];

        if (grid[i - 1][j] < v[0]) {
            join(pos(i - 1, j), pos(i, j));
        }

        if (grid[i + 1][j] < v[0]) {
            join(pos(i + 1, j), pos(i, j));
        }

        if (grid[i][j - 1] < v[0]) {
            join(pos(i, j - 1), pos(i, j));
        }

        if (grid[i][j + 1] < v[0]) {
            join(pos(i, j + 1), pos(i, j));
        }

        int loc = find(pos(i, j));
        curve[loc] += corner(same(i, j, -1, 0), same(i, j, -1, 1), same(i, j, 0, 1));
        curve[loc] += corner(same(i, j, 0, 1), same(i, j, 1, 1), same(i, j, 1, 0));
        curve[loc] += corner(same(i, j, 1, 0), same(i, j, 1, -1), same(i, j, 0, -1));
        curve[loc] += corner(same(i, j, 0, -1), same(i, j, -1, -1), same(i, j, -1, 0));

        if (curve[loc] == 4) {
            ans += sz[loc];
        }
    }

    fout << ans << '\n';

    return 0;
}
