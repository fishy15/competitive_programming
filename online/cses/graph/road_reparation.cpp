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
#define MAXN 1000000

using namespace std;

int n, m;
vector<array<ll, 3>> edge;
ll ans;
int dsu[MAXN];
int sz[MAXN];

int get(int x) {
    if (x == dsu[x]) return x;
    return dsu[x] = get(dsu[x]);
}

void join(int x, int y) {
    if ((x = get(x)) != (y = get(y))) {
        if (sz[x] < sz[y]) swap(x, y);
        dsu[y] = dsu[x];
        sz[x] += sz[y];
    }
}

int main() {
   cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        edge.push_back({c, a, b});
    }

    for (int i = 0; i < n; i++) {
        dsu[i] = i;
        sz[i] = 1;
    }

    sort(edge.begin(), edge.end());

    int cnt = 0;
    for (auto &e : edge) {
        if (cnt == n - 1) break;
        if (get(e[1]) != get(e[2])) {
            join(e[1], e[2]);
            ans += e[0];
            cnt++;
        }
    }

    if (cnt < n - 1) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}
