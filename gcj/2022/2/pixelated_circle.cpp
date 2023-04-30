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

int hyp(int x, int y) {
    return (int) round(hypot(x, y));
}

void solve() {
    int r; cin >> r;

    set<array<int, 2>> a, b;

    for (int c = 0; c <= r; c++) {
        for (int x = -c; x <= c; x++) {
            int y = round(sqrt(c * c - x * x));
            a.insert({x, y});
            a.insert({x, -y});
            a.insert({y, x});
            a.insert({-y, x});
        }
    }

    for (int x = -r; x <= r; x++) {
        for (int y = -r; y <= r; y++) {
            if (hyp(x, y) <= r) {
                b.insert({x, y});
            }
        }
    }

    cout << b.size() - a.size() << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
