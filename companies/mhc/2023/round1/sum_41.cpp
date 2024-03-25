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
#define MAXN 41

using namespace std;

map<int, array<vector<int>, MAXN + 1>> ans;
map<int, vector<pair<int, int>>> f;

vector<pair<int, int>> factor_p(int x) {
    if (f.count(x)) {
        return f[x];
    }

    vector<pair<int, int>> res;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            res.push_back({i, x / i});
        }
    }
    return f[x] = res;
}

vector<int> merge(const vector<int> &a, const vector<int> &b) {
    vector<int> res(a.begin(), a.end());
    for (auto x : b) res.push_back(x);
    return res;
}

void solve(int x) {
    if (!ans.count(x)) {
        auto fs = factor_p(x);
        array<vector<int>, MAXN + 1> res;

        if (x <= MAXN) {
            res[x] = {x};
        }

        for (auto [a, b] : fs) {
            solve(a);
            solve(b);
            auto res_a = ans[a];
            auto res_b = ans[b];
            for (int i = 1; i <= MAXN; i++) {
                if (res_a[i].empty()) continue;
                for (int j = 1; i + j <= MAXN; j++) {
                    if (res_b[j].empty()) continue;
                    auto tot = merge(res_a[i], res_b[j]);
                    if (res[i + j].empty()) {
                        res[i + j] = tot;
                    } else if (res[i + j].size() > tot.size()) {
                        res[i + j] = tot;
                    }
                }
            }
        }

        ans[x] = res;
    }
}

void solve() {
    int p;
    cin >> p;
    
    solve(p);
    auto &res = ans[p];

    vector<int> qq;
    for (int i = 1; i <= MAXN; i++) {
        if (!res[i].empty()) {
            auto v = res[i];
            for (int j = i + 1; j <= MAXN; j++) v.push_back(1);

            if (qq.empty()) {
                qq = v;
            } else if (qq.size() > v.size()) {
                qq = v;
            }
        }
    }
    
    if (qq.empty()) {
        cout << "-1\n";
    } else {
        cout << qq.size() << ' ';
        for (auto x : qq) cout << x << ' ';
        cout << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
