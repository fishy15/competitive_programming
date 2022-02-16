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

int n;
set<int> missing;

bool repr(int x) {
    return !missing.count(x % 10) && !missing.count(x / 10);
}

void pr(int h, int m, int s) {
    printf("%02d:%02d:%02d\n", h, m, s);
}

int closest(int x) {
    pair<int, int> c = {INF, INF};
    for (int i = 0; i < 60; i++) {
        if (repr(i)) {
            c = min(c, {abs(x - i), i});
        }
    }
    return c.second;
}

int closest_l(int x) {
    pair<int, int> c = {INF, INF};
    for (int i = 0; i < x; i++) {
        if (repr(i)) {
            c = min(c, {abs(x - i), i});
        }
    }
    return c.second;
}

int closest_r(int x) {
    pair<int, int> c = {INF, INF};
    for (int i = x + 1; i < 60; i++) {
        if (repr(i)) {
            c = min(c, {abs(x - i), i});
        }
    }
    return c.second;
}

ll get_d(array<int, 3> a, array<int, 3> b) {
    ll v1 = a[0] * 60 * 60 + a[1] * 60 + a[2];
    ll v2 = b[0] * 60 * 60 + b[1] * 60 + b[2];
    return abs(v1 - v2);
}

void solve() {
    int i; string ss; 
    cin >> i >> ss;
    int h = stoi(ss.substr(0, 2));
    int m = stoi(ss.substr(3, 2));
    int s = stoi(ss.substr(6, 2));

    cout << i << ' ';

    int zero = closest_r(-1);
    int sixty = closest_l(60);

    int m1 = closest_l(m);
    int m2 = closest_r(m);

    int h1 = closest_l(h);
    int h2 = closest_r(h);

    vector<array<int, 3>> test = {
        {h, m, s},
        {h, m, closest_l(s)},
        {h, m, closest_r(s)},
        {h, m1, sixty},
        {h, m2, zero},
        {h1, sixty, sixty},
        {h2, zero, zero}
    };

    sort(test.begin(), test.end(), [&](auto a, auto b) {
        int d1 = get_d(a, {h, m, s});
        int d2 = get_d(b, {h, m, s});
        if (d1 == d2) {
            return a == min(a, b);
        }
        return d1 < d2;
    });

    for (auto a : test) {
        if (repr(a[0]) && repr(a[1]) && repr(a[2])) {
            pr(a[0], a[1], a[2]);
            return;
        }
    }
}

int main() {
    /* cin.tie(0)->sync_with_stdio(0); */

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        missing.insert(x);
    }

    int q; cin >> q;
    while (q--) solve();

    return 0;
}
