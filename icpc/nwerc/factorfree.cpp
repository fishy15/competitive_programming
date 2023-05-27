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
#define MAXN 10000010

using namespace std;

int p[MAXN];

void precalc() {
    for (ll i = 2; i < MAXN; i++) {
        if (p[i] == 0) {
            p[i] = i;
            for (ll j = i * i; j < MAXN; j += i) {
                p[j] = i;
            }
        }
    }
}

vector<int> factor(int x) {
    vector<int> res;
    while (x > 1) {
        res.push_back(p[x]);
        x /= p[x];
    }
    
    sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vector<vector<int>> pf;
    map<int, vector<int>> has_p;
    for (int i = 0; i < n; i++) {
        pf.push_back(factor(nums[i]));

        auto &v = pf.back();
        for (auto p : v) {
            has_p[p].push_back(i);
        }
    }

    vector<int> ans(n);
    bool ok = true;

    auto check = [&](int l, int r, int idx) {
        for (auto p : pf[idx]) {
            auto it = lower_bound(has_p[p].begin(), has_p[p].end(), idx);

            if (it != has_p[p].begin()) {
                if (*prev(it) >= l) {
                    return false;
                }
            }

            if (next(it) != has_p[p].end()) {
                if (*next(it) < r) {
                    return false;
                }
            }
        }

        return true;
    };

    auto solve = [&](auto self, int l, int r, int proot) {
        if (l + 1 > r) return;

        for (int a = l, b = r - 1; a <= b; a++, b--) {
            if (check(l, r, a)) {
                ans[a] = proot;
                self(self, l, a, a);
                self(self, a + 1, r, a);
                return;
            } else if (a != b && check(l, r, b)) {
                ans[b] = proot;
                self(self, l, b, b);
                self(self, b + 1, r, b);
                return;
            }
        }

        ok = false;
    };

    solve(solve, 0, n, -1);

    if (ok) {
        for (int i = 0; i < n; i++) {
            cout << ans[i] + 1 << ' ';
        }
        cout << '\n';
    } else {
        cout << "impossible\n";
    }

    return 0;
}
