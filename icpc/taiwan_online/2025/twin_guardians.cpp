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
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

constexpr int MAXN = 1'000'000;

bool p[MAXN+1];

void precomp() {
    fill(all(p), true);
    p[0] = p[1] = false;
    rep(i, 2, MAXN+1) {
        if (p[i]) {
            for (ll j = (ll) i * i; j <= MAXN; j += i) {
                p[j] = false;
            }
        }
    }
}

void solve() {
    int x, y;
    cin >> x >> y;
    if (x + 2 == y && p[x] && p[y]) {
        cout << "Y\n";
    } else {
        cout << "N\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
