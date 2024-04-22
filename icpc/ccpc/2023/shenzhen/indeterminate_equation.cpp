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
#include <optional>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

using ull = unsigned long long;

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

ull pollard(ull n) {
    auto f = [n](ull x) { return modmul(x, x, n) + 1; };
    ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    while (t++ % 40 || __gcd(prd, n) == 1) {
        if (x == y) x = ++i, y = f(x);
        if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
        x = f(x), y = f(f(y));
    }
    return __gcd(prd, n);
}

bool isPrime(ull n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
        s = __builtin_ctzll(n-1), d = n >> s;
    for (ull a : A) {
        ull p = modpow(a%n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--)
            p = modmul(p, p, n);
        if (p != n-1 && i != s) return 0;
    }
    return 1;
}

#define all(x) x.begin(), x.end()
vector<ull> factor(ull n) {
    if (n == 1) return {};
    if (isPrime(n)) return {n};
    ull x = pollard(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), all(r));
    return l;
}

vector<ll> divs(const vector<ull> &pf) {
    map<ull, int> cnt;
    for (auto x : pf) {
        cnt[x]++;
    }

    vector<ll> poss = {1};
    for (auto [p, c] : cnt) {
        vector<ll> new_poss;
        ll mul = p;
        for (int i = 1; i <= c; i++) {
            for (auto x : poss) {
                new_poss.push_back(x * mul);
            }
            mul *= p;
        }
        poss.insert(poss.end(), all(new_poss));
    }

    return poss;
}

void solve() {
    ll n;
    int k;
    cin >> n >> k;
            
    auto comp_other = [n, k](ll a, ll b) -> optional<ll> {
        ll term = 1;
        for (int i = 0; i < k - 1; i++) {
            if (n / term < a) return {};
            term *= a; 
        }

        ll sum = term;
        for (int i = 1; i < k; i++) {
            term /= a;
            term *= b;
            if (n - sum < term) return {};
            sum += term;
        }

        return sum;
    };

    ll tot = 0;
    for (auto d : divs(factor(n))) {
        auto other = n / d;
        // d = a - b
        // other = a^(k - 1) + a^(k - 2) b + ... + b^(k - 1)

        ll l = d + 1;
        ll r = n;
        ll ans = -1;

        while (l <= r) {
            ll m = l + (r - l) / 2;
            if (comp_other(m, m - d)) {
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }

        if (ans == -1) continue;
        l = d + 1;
        r = ans;

        while (l <= r) {
            ll m = l + (r - l) / 2;
            auto res = *comp_other(m, m - d);
            if (res < other) {
                l = m + 1;
            } else if (res > other) {
                r = m - 1;
            } else {
                tot++;
                break;
            }
        }
    }

    cout << tot << '\n';
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
