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

struct line {
    ll m, b;
    line operator+(const line &other) const {
        return {m + other.m, b + other.b};
    }
    line operator-(const line &other) const {
        return {m - other.m, b - other.b};
    }
    ll operator()(ll x) const {
        return m * x + b;
    }
};

ll fdiv(ll a, ll b) {
    return a / b - ((a ^ b) < 0 && a % b);
}

ll cdiv(ll a, ll b) {
    if (b < 0) {
        a *= -1;
        b *= -1;
    }

    auto ans = fdiv(a + b - 1, b);
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<line> a(n + 1), b(n + 1);
    rep(i, 1, n+1) {
        int x;
        cin >> x;
        a[i] = line{0, x};
    }
    rep(i, 1, n+1) {
        int x;
        cin >> x;
        if (i == 1) {
            b[i] = line{1, 0};
        } else {
            b[i] = line{0, x};
        }
    }

    vector<line> lines;
    vector<array<ll, 4>> events; // stores x, 0, left m, left b
                                 // or     q, 1, idx, _
    line cur{0, 0};
    rep(i, 1, n+1) {
        auto diff = b[i] - a[i];
        if (diff.m == 0) {
            cur.b += abs(diff.b);
        } else if (diff.m < 0) {
            auto change = cdiv(-diff.b, diff.m);
            events.push_back({change, 0, diff.m, diff.b});
            cur = cur + diff;
        } else if (diff.m > 0) {
            auto change = cdiv(-diff.b, diff.m);
            events.push_back({change, 0, -diff.m, -diff.b});
            cur = cur - diff;
        }
        for (int j = i; j <= n; j += i) {
            a[j] = a[j] + diff;
        }
    }

    int q;
    cin >> q;

    vector<ll> ans(q);
    rep(i, 0, q) {
        int x;
        cin >> x;
        events.push_back({x, 1,i});
    }

    sort(all(events));
    for (const auto &e : events) {
        if (e[1] == 0) {
            line change{e[2], e[3]};
            cur = cur - change - change;
        } else {
            auto x = e[0];
            auto idx = e[2];
            ans[idx] = cur(x);
        }
    }

    for (auto x : ans) {
        cout << x << '\n';
    }

    return 0;
}
