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
#include <random>
#include <chrono>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

constexpr int NUM_ITERS = 10;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand_idx(int n) {
    return uniform_int_distribution(0, n - 1)(rng);
}


#define all(x) x.begin(), x.end()

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
    auto f = [n](ull x) { return modmul(x, x, n) + 1; };
    ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
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

map<ull, int> compress(const vector<ull> &ps) {
    map<ull, int> res;
    for (auto p : ps) res[p]++;
    return res;
}

vector<ull> divisor(const map<ull, int> f) {
    vector<ull> res = {1};
    for (auto [p, c] : f) {
        int sz = res.size();
        ull prod = p;
        for (int j = 1; j <= c; j++, prod *= p) {
            for (int i = 0; i < sz; i++) {
                res.push_back(prod * res[i]);
            }
        }
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<ll> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    ull ans = 0;
    for (int i = 0; i < NUM_ITERS; i++) {
        int idx = rand_idx(n);
        auto divs = divisor(compress(factor(nums[idx])));
        sort(divs.begin(), divs.end());
        vector<int> cnt(divs.size());

        for (auto j : nums) {
            ull div = gcd(nums[idx], j);
            auto idx = lower_bound(divs.begin(), divs.end(), div) - divs.begin();
            cnt[idx]++;
        }

        for (int i = 0; i < (int) divs.size(); i++) {
            for (int j = i + 1; j < (int) divs.size(); j++) {
                if (divs[j] % divs[i] == 0) {
                    cnt[i] += cnt[j];
                }
            }
        }

        for (int i = 0; i < (int) divs.size(); i++) {
            if (2 * cnt[i] >= n) {
                ans = max(ans, divs[i]);
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
