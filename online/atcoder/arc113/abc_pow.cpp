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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

ll a, b, c;

ll modpow(ll n, ll e, ll mod) {
    ll res = 1;
    while (e) {
        if (e & 1) res = res * n % mod;
        n = n * n % mod;
        e >>= 1;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> a >> b >> c;
    a %= 10;
    if (a == 0) {
        cout << a << '\n';
        return 0;
    }

    b = modpow(b, c, 4);
    cout << modpow(a, b + 4, 10) << '\n';

    return 0;
}
