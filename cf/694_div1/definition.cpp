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

int p[MAXN + 10];

ll get_class(int x) {
    ll ans = 1;
    while (p[x] != 0) {
        int cnt = 0;
        int cur_p = p[x];
        while (p[x] == cur_p) {
            x /= p[x];
            cnt++;
        }
        if (cnt % 2 == 1) ans *= cur_p;
    }
    return ans;
}

void solve() {
    int n; cin >> n;
    map<ll, int> cnt;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        ll c = get_class(x);
        cnt[c]++;
    }

    int ans_beg = 0;
    int zero_later = 0;

    for (auto p : cnt) {
        ans_beg = max(ans_beg, p.second);
        if (p.second % 2 == 0 || p.first == 1) {
            zero_later += p.second; 
        }
    }

    int q; cin >> q;
    while (q--) {
        ll x; cin >> x;
        if (x == 0) {
            cout << ans_beg << '\n';
        } else {
            cout << max(ans_beg, zero_later) << '\n';
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (ll i = 2; i <= MAXN + 9; i++) {
        if (!p[i]) {
            p[i] = i;
            for (ll j = i * i; j <= MAXN + 9; j += i) {
                if (!p[j]) p[j] = i;
            }
        }
    }

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
