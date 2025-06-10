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

typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
    ll ret = a * b - M * ull(1.L / M * a * b);
    return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
    ull ans = 1;
    for (; e; b = modmul(b, b, mod), e /= 2)
        if (e & 1) ans = modmul(ans, b, mod);
    return ans;
}

bool isPrime(ull n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
        s = __builtin_ctzll(n-1), d = n >> s;
    for (ull a : A) {   // ^ count trailing zeroes
        ull p = modpow(a%n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--)
            p = modmul(p, p, n);
        if (p != n-1 && i != s) return 0;
    }
    return 1;
}

ull pollard(ull n) {
    ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    auto f = [&](ull a) { return modmul(a, a, n) + i; };
    while (t++ % 40 || __gcd(prd, n) == 1) {
        if (x == y) x = ++i, y = f(x);
        if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
        x = f(x), y = f(f(y));
    }
    return __gcd(prd, n);
}
vector<ull> factor(ull n) {
    if (n == 1) return {};
    if (isPrime(n)) return {n};
    ull x = pollard(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), all(r));
    return l;
}

void solve() {
    int n;
    cin >> n;

    map<ll, int> cnt;
    ll mx = 0;
    rep(i, 0, n) {
        ll x;
        cin >> x;
        cnt[x]++;
        mx = max(mx, x);
    }

    vector<pair<ll, int>> cnt_v(all(cnt));

    ll ans = 0;
    for (auto [_, c] : cnt_v) {
        if (c > 2) {
            ans += (ll) c * (c - 1) * (c - 2);
        }
    }

    vector<ll> poss = {1};
    for (auto [v, c] : cnt_v) {
        map<ll, int> ps;
        for (auto p : factor(v)) {
            ps[p]++;
        }

        poss.clear();
        poss.push_back(1);
        for (auto [p, c] : ps) {
            auto cur_sz = sz(poss);
            rep(i, 0, cur_sz) {
                auto x = poss[i] * p;
                rep(i, 1, c+1) {
                    poss.push_back(x);
                    x *= p;
                }
            }
        }

        for (auto x : poss) {
            if (x != v) {
                auto wanted = (ll) v * v / x;
                if (wanted <= mx) {
                    auto x_it = lower_bound(all(cnt_v), pair{x, 0});
                    if (x_it != end(cnt_v) && x_it->first == x) {
                        auto wanted_it = lower_bound(all(cnt_v), pair{wanted, 0});
                        if (wanted_it != end(cnt_v) && wanted_it->first == wanted) {
                            ans += (ll) c * x_it->second * wanted_it->second;
                        }
                    }
                }
            }
        }
    }

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
