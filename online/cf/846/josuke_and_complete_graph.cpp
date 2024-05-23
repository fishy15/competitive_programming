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

// change if necessary
#define MAXN 1000000

using namespace std;

template<class F, class G, class T>
void rec(ll from, ll to, F& f, G& g, ll& i, T& p, T q) {
    if (p == q) return;
    if (from == to) {
        g(i, to, p);
        i = to; p = q;
    } else {
        ll mid = (from + to) >> 1;
        rec(from, mid, f, g, i, p, f(mid));
        rec(mid+1, to, f, g, i, p, q);
    }
}

template<class F, class G>
void constantIntervals(ll from, ll to, F f, G g) {
    if (to <= from) return;
    ll i = from; auto p = f(i), q = f(to-1);
    rec(from, to-1, f, g, i, p, q);
    g(i, to, q);
}

void solve() {
    ll l, r;
    cin >> l >> r;

    ll ans = 0;
    auto myceil = [l](ll k) { return (l + k - 1) / k; };

    constantIntervals(1, r, myceil, [&](ll lo, ll hi, ll ceilres) {
        // want first k where floor(r / k) <= ceilres
        // => r / k < ceilres + 1
        auto k = r / (ceilres + 1) + 1;
        ans += min(hi, k) - min(lo, k);
    });

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
