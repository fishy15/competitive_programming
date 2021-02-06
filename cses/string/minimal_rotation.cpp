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
#include <random>
#include <chrono>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 2000010

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll modpow(ll n, ll e, ll mod) {
    ll res = 1;
    while (e) {
        if (e & 1) res = res * n % mod;
        n = n * n % mod;
        e >>= 1;
    }
    return res;
}

int randval() {
    return uniform_int_distribution<int>(2, 1000000005)(rng);
}
 
template<int N>
struct string_hash {
    struct hash {
        int n;
        array<int, 2> h;
        static inline array<array<int, N>, 2> base, inv;
        static constexpr int p[2] = {1000000007, 1000000009};
        hash() { 
            n = 0;
            if (!base[0][0]) calc_base();
            h = {0, 0};
        }
        hash(char c) : hash() {
            *this += c;
        }
        hash(const hash &h2) : hash() {
            n = h2.n;
            h = h2.h;
        }
        void calc_base() {
            for (int i = 0; i < 2; i++) {
                base[i][0] = 1;
                base[i][1] = randval();
                inv[i][0] = 1;
                inv[i][1] = modpow(base[i][1], p[i] - 2, p[i]);
            }
            for (int j = 2; j < N; j++) {
                for (int i = 0; i < 2; i++) {
                    base[i][j] = (ll) base[i][j - 1] * base[i][1] % p[i];
                    inv[i][j] = (ll) inv[i][j - 1] * inv[i][1] % p[i];
                }
            }
        }
        bool operator==(const hash &h2) const {
            return n == h2.n && h == h2.h;
        }
        bool operator<(const hash &h2) const {
            if (n == h2.n) return h < h2.h;
            return n < h2.n;
        }
        hash &operator+=(const char c) {
            for (int i = 0; i < 2; i++) {
                h[i] += (ll) base[i][n] * c % p[i];
                if (h[i] >= p[i]) h[i] -= p[i];
            }
            n++;
            return *this;
        }
        hash &operator-=(const hash &h2) {
            for (int i = 0; i < 2; i++) {
                h[i] -= h2.h[i];
                if (h[i] < 0) h[i] += p[i];
                h[i] = (ll) h[i] * inv[i][h2.n] % p[i];
            }
            n -= h2.n;
            return *this;
        }
    };
    vector<hash> h;
    string_hash() : string_hash("") {}
    string_hash(const string &s) {
        h.resize(s.size());
        hash cur;
        for (int i = 0; i < (int)(s.size()); i++) {
            cur += s[i];
            h[i] = cur;
        }
    }
    hash substr(int n, int sz) const {
        hash res = h[n + sz - 1];
        if (n) res -= h[n - 1];
        return res;
    }
    hash val() const {
        return h.back();
    }
    static hash calc(const string &s) {
        hash cur;
        for (char c : s) {
            cur += c;
        }
        return cur;
    }
};
 
using shash = string_hash<MAXN>;

int n;
string s;
shash sh;

int check(int a, int b) {
    int l = 0;
    int r = n - 1;
    int ans = 0;
    while (l <= r) {
        int m = (l + r) / 2;
        auto h1 = sh.substr(a, m);
        auto h2 = sh.substr(b, m);
        if (h1 == h2) {
            l = m + 1;
            ans = m;
        } else {
            r = m - 1;
        }
    }

    if (s[a + ans] <= s[b + ans]) return a;
    return b;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> s;
    n = s.size();
    s += s;

    sh = shash(s);

    int cur = 0;
    for (int i = 1; i < n; i++) {
        cur = check(cur, i);
    }

    cout << s.substr(cur, n) << '\n';

    return 0;
}
