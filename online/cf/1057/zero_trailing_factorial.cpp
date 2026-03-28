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

constexpr int MAXN = 1e7;
constexpr int MAXP = 700'000;

int divi[MAXN + 1];
int pidx[MAXN + 1];
vector<int> primes;

void precomp() {
    rep(i, 2, MAXN + 1) {
        if (divi[i] == 0) {
            divi[i] = i;
            pidx[i] = sz(primes);
            primes.push_back(i);
            for (ll j = (ll) i * i; j <= MAXN; j += i) {
                divi[j] = i;
            }
        }
    }
}

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

template<typename T>
T &ckmax(T &a, T b) {
    return a = max(a, b);
}

int cnt_full[MAXP];
int cnt_cur[MAXP];

void solve() {
    int n, m;
    cin >> n >> m;

    if (n == 2) {
        cout << "0\n";
        return;
    }

    auto max_p = *prev(upper_bound(all(primes), n));

    // get the set of relevant primes
    set<int> in_range;
    rep(i, max_p, n+1) {
        int cur = i;
        while (cur > 1) {
            auto p = divi[cur];
            in_range.insert(p);
            cur /= p;
        }
    }

    // fill in relevant primes
    auto init = [&](int *cnt, ll lim) {
        for (auto p : in_range) {
            ll x = p;
            while (x <= lim) {
                cnt[pidx[p]] += lim / x;
                x *= p;
            }
        }
    };

    init(cnt_full, n);
    init(cnt_cur, max_p-1);

    ll ans = 0;
    rep(i, max_p, n) {
        int cur = i;
        while (cur > 1) {
            auto p = divi[cur];
            cnt_cur[pidx[p]]++;
            cur /= p;
        }

        int best = INF;
        for (auto p : in_range) {
            ll x = p;
            int e = 1;
            while (x <= m) {
                auto small = cnt_cur[pidx[p]] / e;
                auto big = cnt_full[pidx[p]] / e;
                if (small != big) {
                    ckmin(best, small);
                }
                x *= p;
                e++;
            }
        }

        ans += best;
    }

    // clear out relevant primes
    for (auto p : in_range) {
        cnt_full[pidx[p]] = 0;
        cnt_cur[pidx[p]] = 0;
    }

    cout << ans << '\n';
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
