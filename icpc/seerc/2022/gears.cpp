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

bool is_perm(vector<ll> a, vector<ll> b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<ll> pos(n);
    vector<ll> r(n);
    for (int i = 0; i < n; i++) {
        cin >> pos[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }

    vector<ll> diff(n - 1);
    for (int i = 0; i < n - 1; i++) {
        diff[i] = pos[i + 1] - pos[i];
    }

    // implicit x -x x ... coefficients
    vector<ll> exprs(n);
    exprs[0] = 0;
    for (int i = 1; i < n; i++) {
        exprs[i] = diff[i - 1] - exprs[i - 1];
    }

    auto min_p = *min_element(r.begin(), r.end());
    ll min_even = 0;
    ll min_odd = INFLL;

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            min_even = min(min_even, exprs[i]);
        } else {
            min_odd = min(min_odd, exprs[i]);
        }
    }

    vector<int> to_check;
    to_check.push_back(min_p - min_even);
    if (min_odd != INFLL) {
        to_check.push_back(min_odd - min_p);
    }

    for (auto init : to_check) {
        vector<ll> res(n);
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                res[i] = exprs[i] + init;
            } else {
                res[i] = exprs[i] - init;
            }
        }

        if (is_perm(r, res)) {
            for (auto x : res) cout << x << ' ';
            cout << '\n';
            return 0;
        }
    }

    return 0;
}
