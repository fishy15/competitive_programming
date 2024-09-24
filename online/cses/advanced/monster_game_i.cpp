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

ll floordiv(ll x, ll y) {
    return x / y - ((x ^ y) < 0 && x % y);
}

struct line {
    ll m, b;
    ll isect(const line &l2) {
        return floordiv(b - l2.b, m - l2.m);
    }
    ll eval(ll x) {
        return m * x + b;
    }
};

struct CHT {
    deque<line> lines;

    line at(int x) { return end(lines)[x]; }

    void add(line l) {
        while (sz(lines) > 0 && lines[0].m == l.m) {
            if (lines[0].b < l.b) return;
            else lines.pop_front();
        }
        while (sz(lines) >= 2 && l.isect(lines[0]) >= lines[0].isect(lines[1])) {
            lines.pop_front();
        }
        lines.push_front(l);
    }

    ll qry(ll x) {
        while (sz(lines) >= 2 && at(-2).eval(x) <= at(-1).eval(x)) {
            lines.pop_back();
        }
        return at(-1).eval(x);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, x;
    cin >> n >> x;

    vector<int> s(n);
    rep(i, 0, n) {
        cin >> s[i];
    }

    vector<int> f(n);
    rep(i, 0, n) {
        cin >> f[i];
    }

    CHT cht;
    cht.add({x, 0});

    ll ans;
    rep(i, 0, n) {
        auto cost = cht.qry(s[i]);
        if (i == n - 1) {
            ans = cost;
        } else {
            cht.add({f[i], cost});
        }
    }

    cout << ans << '\n';

    return 0;
}
