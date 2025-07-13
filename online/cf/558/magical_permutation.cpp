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

void add_to_basis(vector<pair<int, int>> &basis, int x, int idx) {
    rep(i, 0, sz(basis)) {
        if (x & (1 << i)) {
            if (basis[i].first == -1) {
                basis[i].first = x;
                basis[i].second = idx;
                return;
            } else {
                x ^= basis[i].first;
            }
        }
    }
}

vector<int> gray(int p) {
    if (p == 0) {
        return {0};
    } else {
        auto first = gray(p - 1);

        auto second = first;
        reverse(all(second));
        for (auto x : second) {
            first.push_back(x ^ (1 << (p - 1)));
        }
        return first;
    }
}

vector<int> solve(const vector<int> &s, int p) {
    vector<pair<int, int>> basis(p, pair{-1, -1});

    auto max_allowed = (1 << p) - 1;
    rep(i, 0, sz(s)) {
        auto x = s[i];
        if (x <= max_allowed) {
            add_to_basis(basis, x, i);
        }
    }

    if (any_of(all(basis), [](auto p) { return p.first == -1; })) {
        return {};
    }


    vector<int> res;
    auto base = gray(p);
    for (auto x : base) {
        int to_add = 0;
        rep(i, 0, p) {
            if (x & (1 << i)) {
                to_add ^= s[basis[i].second];
            }
        }
        res.push_back(to_add);
    }

    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> s(n);
    rep(i, 0, n) {
        cin >> s[i];
    }

    for (int i = 18; i > 0; i--) {
        auto res = solve(s, i);
        if (!res.empty()) {
            cout << i << '\n';
            for (auto x : res) {
                cout << x << ' ';
            }
            cout << '\n';
            return 0;
        }
    }

    cout << "0\n";
    cout << "0\n";

    return 0;
}
