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
    ll n; cin >> n;
    vector<ll> a, b;
    ll aa = INF;
    ll bb = INF;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        a.push_back(x);
        aa = min(aa, x);
    }
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        b.push_back(x);
        bb = min(bb, x);
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += max(a[i] - aa, b[i] - bb);
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
