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

pair<vector<int>, vector<int>> move(const vector<int> &a, const vector<int> &b, int x) {
    int n = a.size();
    vector<int> res_a, res_b;

    bool flip_at_end = false;
    if (x >= n) {
        flip_at_end = true;
        x -= n;
    }

    for (int i = x; i < n; i++) {
        res_a.push_back(a[i]);
        res_b.push_back(b[i]);
    }

    for (int i = 0; i < x; i++) {
        res_a.push_back(b[i]);
        res_b.push_back(a[i]);
    }

    if (flip_at_end) {
        swap(res_a, res_b);
    }

    return {res_a, res_b};
}

bool check(const vector<int> &a, const vector<int> &b) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        if (2 * i < n - 1) {
            if (a[i] >= b[i]) {
                return false;
            }
        }

        if (2 * i > n - 1) {
            if (a[i] <= b[i]) {
                return false;
            }
        }

        if (a[i] != b[n - i - 1]) {
            return false;
        }
    }

    return true;
}

bool check(const vector<int> &a, const vector<int> &b, int moves) {
    auto [res_a, res_b] = move(a, b, moves);
    return check(res_a, res_b);
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }

    vector<int> b(n);
    for (auto &x : b) {
        cin >> x;
    }

    int equal_idx = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] == b[i]) {
            if (equal_idx == -1 && n % 2 == 1) {
                equal_idx = i;
            } else {
                cout << "-1\n";
                return;
            }
        }
    }

    if (equal_idx != -1) {
        // has to be in the middle
        auto mid = n / 2;
        if (equal_idx < mid) {
            equal_idx += n;
        }

        auto moves = equal_idx - mid;
        if (check(a, b, moves)) {
            cout << moves << '\n';
        } else if (check(a, b, moves + n)) {
            cout << moves + n << '\n';
        } else {
            cout << "-1\n";
        }
        return;
    }

    // everything is different, so goal is to make all a[i] > b[i]
    int flip_idx = 0;
    for (int i = 0; i < n - 1; i++) {
        if ((a[i] < b[i]) != (a[i + 1] < b[i + 1])) {
            if (flip_idx == 0) {
                flip_idx = i + 1;
            } else {
                cout << "-1\n";
                return;
            }
        }
    }

    auto shift = flip_idx;
    if (a[flip_idx] < b[flip_idx]) {
        shift += n;
    }

    int ans = INF;
    auto cc = [&](int s) {
        if (s < 0) {
            s += 2 * n;
        }

        if (check(a, b, s)) {
            ans = min(ans, s);
        }
    };

    if (n % 2 == 0) {
        shift -= n / 2;
        cc(shift);
    } else {
        shift -= n / 2;
        cc(shift);
        cc(shift + 1);
    }

    if (ans == INF) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
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
