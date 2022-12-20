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

// change if necessary
#define MAXN 1000000

using namespace std;

struct DSU {
    vector<int> dsu;
    vector<int> sz;

    DSU(int n) : dsu(n), sz(n) {
        iota(dsu.begin(), dsu.end(), 0);
        fill(sz.begin(), sz.end(), 1); 
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    bool join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            dsu[y] = x;
            sz[x] += sz[y];
            return true;
        }
        return false;
    }
};

// computes x^e mod m
ll modpow(ll x, ll e, ll m) {
    ll res = 1;
    ll n = x;

    while (e) {
        if (e & 1) {
            res *= n;
            res %= m;
        }

        n *= n;
        n %= m;
        e >>= 1;
    }

    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector nums(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vector<array<ll, 3>> conn;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ll w = modpow(nums[i], nums[j], m) + modpow(nums[j], nums[i], m);
            if (w >= m) w -= m;

            conn.push_back({w, i, j});
        }
    }

    sort(conn.begin(), conn.end(), greater());

    DSU dsu(n);
    ll ans = 0;
    for (auto [w, i, j] : conn) {
        if (dsu.join(i, j)) {
            ans += w;
        }
    }

    cout << ans << '\n';

    return 0;
}
