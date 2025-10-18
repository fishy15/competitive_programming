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
#include <future>

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

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : mi((int)(_v % MOD)) {}
    mi operator+(const mi &m2) const { return mi(v + m2.v); }
    mi operator-(const mi &m2) const { return mi(v - m2.v); }
    mi operator*(const mi &m2) const { return mi((ll) v * m2.v); }
    mi operator/(const mi &m2) const { return mi((ll) v * m2.inv().v); }
    mi &operator+=(const mi &m2) { return *this = *this + m2; }
    mi &operator-=(const mi &m2) { return *this = *this - m2; }
    mi &operator*=(const mi &m2) { return *this = *this * m2; }
    mi &operator/=(const mi &m2) { return *this = *this / m2; }
    mi pow(ll e) const {
        mi res = 1;
        mi n = *this;
        while (e > 0) {
            if (e & 1) res *= n;
            n *= n;
            e >>= 1;
        }
        return res;
    }
    mi inv() const {
        return pow(MOD - 2);
    }
};

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
    auto f = [&](ull x) { return modmul(x, x, n) + i; };
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

struct testcase {
    ll n;
    ull a, b;
    mi ans;

    static testcase read() {
        ll n;
        cin >> n;

        ull a, b;
        cin >> a >> b;

        return testcase{n, a, b};
    }

    void solve() {
        auto factors = factor(b);
        map<ull, int> ps_map;
        for (auto p : factors) {
            ps_map[p]++;
        }

        vector<pair<ull, int>> ps;
        for (auto [x, y] : ps_map) {
            ps.push_back({x, y});
        }

        auto solve = [&](auto &&self, int idx, ull cur_prod, mi combos) -> void {
            if (idx == sz(ps)) {
                if (cur_prod <= a) {
                    ans += combos;
                }
            } else {
                auto [p, cnt] = ps[idx];
                vector<mi> choose_n(cnt+1);
                choose_n[0] = 1;
                rep(i, 1, cnt+1) {
                    choose_n[i] = choose_n[i-1] * ((ll) (n + i - 1)) / i;
                }
                ull prod = cur_prod;
                rep(i, 0, cnt+1) {
                    if (prod <= a) {
                        auto choose_before = choose_n[i];
                        auto choose_after = choose_n[cnt-i];
                        self(self, idx+1, prod, combos * choose_before * choose_after);
                    }
                    prod *= p;
                }
            }
        };
        solve(solve, 0, 1, 1);
    }
};

vector<testcase> tests;

const int PARALLEL=8;
void paralleltests(int l=0, int r=PARALLEL-1) {
    if (l==r) {
        for(int i=l;i<(int)tests.size();i+=PARALLEL) {
            tests[i].solve();
        }
        return;
    }
    ll mid = (l+r)/2;
    auto handle = std::async(launch::async,paralleltests, l,mid);
    paralleltests(mid+1,r);
    handle.wait();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    rep(i, 0, t) {
        tests.push_back(testcase::read());
    }

    paralleltests();

    rep(i, 0, t) {
        cout << "Case #" << i + 1 << ": " << tests[i].ans.v << '\n';
    }

    return 0;
}
