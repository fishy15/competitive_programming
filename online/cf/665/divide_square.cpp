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
#define MAXN 100010
#define MAXB 10 * MAXN

using namespace std;

int n, m;
array<int, 3> h[MAXN];
array<int, 3> v[MAXN];
ll ans = 1;

// add horz - x 0 y 0
// end horz - x 1 y 0
// vert qry - x 2 y1 y2
vector<array<int, 4>> events;

int bit[MAXB];

void upd(int x, int v) {
    x += 5; 
    while (x < MAXB) {
        bit[x] += v;
        x += x & -x;
    }
}

int qry(int x) {
    x += 5;
    int res = 0;
    while (x) {
        res += bit[x];
        x -= x & -x;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> h[i][0] >> h[i][1] >> h[i][2];
        events.push_back({h[i][1], 0, h[i][0], 0});
        events.push_back({h[i][2] + 1, 1, h[i][0], 0});
        if (h[i][1] == 0 && h[i][2] == 1000000) ans++;
    }

    for (int i = 0; i < m; i++) {
        cin >> v[i][0] >> v[i][1] >> v[i][2];
        events.push_back({v[i][0], 2, v[i][1], v[i][2]});
        if (v[i][1] == 0 && v[i][2] == 1000000) ans++;
    }

    sort(events.begin(), events.end());

    for (auto [x, t, y1, y2] : events) {
        if (t == 0) {
            upd(y1, 1);
        } else if (t == 1) {
            upd(y1, -1);
        } else {
            ans += qry(y2) - qry(y1 - 1);
        }
    }

    cout << ans << '\n';

    return 0;
}
