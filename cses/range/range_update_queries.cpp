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
#define MAXN 200010

using namespace std;

int n, q;
ll bit[MAXN];

void upd(int x, int v) {
    while (x < MAXN) {
        bit[x] += v;
        x += x & -x;
    }
}

ll qry(int x) {
    ll ans = 0;
    while (x) {
        ans += bit[x];
        x -= x & -x;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        ll x; cin >> x;
        upd(i, x);
        upd(i + 1, -x);
    }

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int a, b; ll u;
            cin >> a >> b >> u;
            upd(a, u);
            upd(b + 1, -u);
        } else {
            int x; cin >> x;
            cout << qry(x) << '\n';
        }
    }

    return 0;
}
