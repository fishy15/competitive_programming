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

template<class F, class G, class T>
void rec(ll from, ll to, F& f, G& g, ll& i, T& p, T q) {
    if (p == q) return;
    if (from == to) {
        g(i, to, p);
        i = to; p = q;
    } else {
        int mid = (from + to) >> 1;
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
    ll x, y, z, k;
    cin >> x >> y >> z >> k;

    // number of extra attacks needed on top of the increases
    auto comp_attacks = [&](ll incs) -> ll {
        ll num_groups = incs / k;
        auto from_incs_big = (__int128) k * num_groups * (num_groups + 1) / 2;
        if (from_incs_big >= z) {
            return 0;
        }


        auto leftover = z - (ll) from_incs_big;
        auto final_damage = incs;
        return (leftover + final_damage - 1) / final_damage;
    };

    ll ans = INFLL;
    auto min_cost = [&](ll from, ll to, ll attacks) {
        // always use the same number of extra attacks, so minimize the first number
        ll num_groups = from / k;
        auto cost = x * from + (num_groups + attacks) * y;
        ans = min(ans, cost);
    };

    constantIntervals(1, z+1, comp_attacks, min_cost);
    cout << ans << '\n';

    /*
    int groups = 0;
    ll group_damage = 0;
    ll ans = INFLL;
    while (group_damage <= z) {
        // search for optimal within each group
        ll leftover = z - group_damage;
        ll base_damage = groups * k;

        groups++;
        group_damage += (ll) k * groups;
    }
    */
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
