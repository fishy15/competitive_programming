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
#include <bitset>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 10000010

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

int sz;
int val[30];
vector<int> pr;
bitset<MAXN> pf;

ll calc(int p, int x) {
    ll pp = p;
    int cnt = 0;
    while (pp <= x) {
        cnt += x / pp;
        pp *= p;
    }
    return cnt;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    while (true) {
        int x; cin >> x;
        if (x == 0) break;
        val[sz] = x;
        sz++;
    }

    for (ll i = 2; i < MAXN; i++) {
        if (pf[i] == 0) {
            pf[i] = 1;
            for (ll j = i * i; j < MAXN; j += i) {
                pf[j] = 1;
            }
            pr.push_back(i);
        }

        if (i % 1000 == 0) cout << i << endl;
    }

    for (int i = 0; i < sz; i++) {
        int x = val[i];
        mi prod = 1;

        for (int p : pr) {
            ll cnt = calc(p, x);
            if (cnt & 1) cnt ^= 1;
            prod *= mi(p).pow(cnt); 
        }

        cout << prod.v << '\n';
    }

    return 0;
}
