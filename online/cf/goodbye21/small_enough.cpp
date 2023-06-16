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

struct BIT {
    int n;
    vector<ll> bit;

    BIT(int n) : n(n), bit(n) {}

    void upd(int x, ll q) {
        x++;
        while (x <= n) {
            bit[x - 1] += q;
            x += x & -x;
        }
    }

    ll qry(int x) {
        ll res = 0;
        while (x > 0) {
            res += bit[x - 1];
            x -= x & -x;
        }
        return res;
    }
};

void solve() {
    int n; cin >> n;
    string s, t; cin >> s >> t;

    if (s < t) {
        cout << "0\n";
        return;
    }

    BIT dist(n);
    vector<bool> used(n);

    array<queue<int>, 26> loc;
    for (int i = 0; i < n; i++) {
        loc[s[i] - 'a'].push(i);
    }

    ll ans = INFLL;
    ll cur = 0;
    int si = 0;

    auto get = [&](int c) {
        while (!loc[c].empty() && (loc[c].front() <= si || used[loc[c].front()])) {
            loc[c].pop();
        }

        return loc[c].empty() ? -1 : loc[c].front();
    };

    for (int ti = 0; ti < n; ti++) {
        if (s[si] < t[ti]) {
            ans = min(ans, cur);
            break;
        } else {
            // smaller, immediately end
            for (int c = 0; c < t[ti] - 'a'; c++) {
                int idx = get(c);
                if (idx == -1) continue;
                int d = idx - si + dist.qry(idx);
                ans = min(ans, cur + d);
            }

            // equal
            if (s[si] == t[ti]) {
                si++;
                while (used[si]) {
                    dist.upd(si, 1);
                    si++;
                }
                continue;
            }

            int c = t[ti] - 'a';
            int idx = get(c);
            if (idx == -1) break;

            int d = idx - si + dist.qry(idx);
            dist.upd(idx, -1);
            used[idx] = true;

            cur += d;
        }
    }

    if (ans == INFLL) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
