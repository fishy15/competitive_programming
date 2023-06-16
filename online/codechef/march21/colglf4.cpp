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
#define MAXN 1000000

using namespace std;

void solve() {
    ll n, e, h, a, b, c;
    cin >> n >> e >> h >> a >> b >> c;
    ll ans = INFLL;
    for (int i = 0; i <= n; i++) {
        ll ne = e;
        ll nh = h - 3 * i;
        if (nh < 0) break;
        ll cur_cost = i * b;
        if (a < c) {
            ne -= 2 * (n - i);
            cur_cost += (n - i) * a;
            if (ne < 0) {
                ll fix = min(-ne, n - i);
                ne += fix;
                nh -= fix;
                cur_cost += fix * (c - a);
            }
            if (nh < 0 || ne < 0) cur_cost = INFLL;
        } else {
            nh -= n - i;
            ne -= n - i;
            cur_cost += (n - i) * c;
            if (nh < 0) {
                ll fix = min(-nh, n - i);
                ne -= fix;
                nh += fix;
                cur_cost += fix * (a - c);
            }
            if (nh < 0 || ne < 0) cur_cost = INFLL;
        }
        ans = min(ans, cur_cost);
    }

    if (ans == INFLL) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
