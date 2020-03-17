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

int dsu[MAXN + 1];
int sz[MAXN + 1];
int l[MAXN + 1];
int r[MAXN + 1];

int find(int x) {
    if (dsu[x] == x) return x;
    return find(dsu[x]);
}

void join(int x, int y) {
    if ((x = find(x)) != (y = find(y))) {
        if (sz[x] < sz[y]) {
            dsu[x] = y;
            sz[y] += sz[x];
        } else {
            dsu[y] = x;
            sz[x] += sz[y];
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        dsu[i] = i;
        sz[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        join(a, b);
    }

    for (int i = 1; i <= n; i++) {
        l[i] = -1;
        r[i] = -1;
    }

    for (int i = 1; i <= n; i++) {
        int f = find(i);
        if (l[f] == -1) l[f] = i;
        r[f] = i;
    }

    vector<pair<int, int>> p;

    for (int i = 1; i <= n; i++) {
        if (l[i] != -1) {
            p.push_back({l[i], -1});
            p.push_back({r[i], 1});
        }
    }

    sort(p.begin(), p.end());

    int cur = 0;
    int ans = 0;
    for (auto i : p) {
        if (i.second < 0) {
            cur++;
            if (cur > 1) ans++;
        } else {
            cur--;
        }
    }

    cout << ans << '\n';

    return 0;
}
