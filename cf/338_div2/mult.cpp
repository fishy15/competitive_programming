// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

ll modPow(ll num, ll exp, ll mod) {
    if (exp == 0) {
        return 1;
    }

    if (exp == 1) {
        return num;
    }

    ll val = 0;
    if (exp % 2 == 0) {
        val = modPow(num, exp / 2, mod);
        val *= val;
    } else {
        val = modPow(num, exp - 1, mod) * num;
    }

    val %= mod;
    return val;
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    ll n; cin >> n;
    map<ll, ll> factor;

    for (ll i = 0; i < n; i++) {
        ll x; cin >> x;
        if (factor.count(x)) {
            factor[x]++;
        } else {
            factor[x] = 1;
        }
    }

    ll num = 1;
    ll cnt = 1;
    ll sqrts = 1;
    bool issq = true;
    for (auto p : factor) {
        num *= modPow(p.first, p.second, MOD);
        sqrts *= modPow(p.first, p.second / 2, MOD);

        if (issq && p.second % 2 == 1) {
            issq = false;
            p.second /= 2;
        }

        cnt *= p.second + 1;
        num %= MOD;
        cnt %= MOD - 1;
        sqrts %= MOD;
    }

    //cout << cnt << num << sqrts << '\n';

    if (issq) {
        cout << modPow(sqrts, cnt, MOD);
    } else {
        cout << modPow(num, cnt, MOD);
    }

    return 0;
}
