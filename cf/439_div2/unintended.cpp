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
#include <random>
#include <chrono>
#include <climits>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 2510

using namespace std;

int n, m, q;
ll bit[MAXN][MAXN];
ll val[MAXN][MAXN];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void update(int x, int y, ll v) {
    while (x <= MAXN) {
        int yy = y;
        while (yy <= MAXN) {
            bit[x][yy] ^= v;
            yy += yy & -yy;
        }
        x += x & -x;
    }
}

ll query(int x, int y) {
    ll res = 0;
    while (x) {
        int yy = y;
        while (yy) {
            res ^= bit[x][yy];
            yy -= yy & -yy;
        }
        x -= x & -x;
    }
    return res;
}

ll randval() {
    return uniform_int_distribution<ll>(LLONG_MIN, LLONG_MAX)(rng);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> q;

    for (int i = 0; i < q; i++) {
        int t, x1, y1, x2, y2; cin >> t >> x1 >> y1 >> x2 >> y2;
        if (t == 1) {
            val[x1][y1] = randval(); 
            update(x1, y1, val[x1][y1]);
            update(x2 + 1, y1, val[x1][y1]);
            update(x1, y2 + 1, val[x1][y1]);
            update(x2 + 1, y2 + 1, val[x1][y1]);
        } else if (t == 2) {
            update(x1, y1, val[x1][y1]);
            update(x2 + 1, y1, val[x1][y1]);
            update(x1, y2 + 1, val[x1][y1]);
            update(x2 + 1, y2 + 1, val[x1][y1]);
        } else {
            if (query(x1, y1) == query(x2, y2)) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }

    return 0;
}
