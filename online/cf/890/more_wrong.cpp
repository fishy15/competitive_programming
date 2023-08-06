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

int qry(int l, int r, map<pair<int, int>, int> &cache) {
    if (l == r) {
        return 0;
    } else {
        if (cache.count({l, r})) {
            return cache[{l, r}];
        }

        cout << "? " << l + 1 << ' ' << r + 1 << endl;
        int x;
        cin >> x;
        if (x == -1) {
            exit(0);
        }

        return cache[{l, r}] = x;
    }
}

void ans(int x) {
    cout << "! " << x + 1 << endl;
}

void solve() {
    int n;
    cin >> n;

    map<pair<int, int>, int> cache;

    // sz, left, right
    set<array<int, 3>> q;
    set<int> relevant;

    for (int i = 0; i < n; i++) {
        relevant.insert(i);
        if (i < n - 1) {
            q.insert({1, i, i + 1});
        }
    }

    while (!q.empty()) {
        auto [_, l, r] = *q.begin();
        q.erase({r - l, l, r});

        int inv1 = qry(l, r - 1, cache);
        int inv2 = qry(l, r, cache);
        if (inv1 == inv2) {
            // r is bigger
            auto it = relevant.find(l);
            if (it != relevant.begin()) {
                auto bef = *prev(it);
                q.erase({l - bef, bef, l});
                q.insert({r - bef, bef, r});
            }

            relevant.erase(it);
        } else {
            // l is bigger
            auto it = relevant.find(r);
            auto nxt_it = next(it);
            if (nxt_it != relevant.end()) {
                auto nxt = *nxt_it;
                q.erase({nxt - r, r, nxt});
                q.insert({nxt - l, l, nxt});
            }

            relevant.erase(it);
        }
    }

    ans(*relevant.begin());
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
