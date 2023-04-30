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

template<typename F>
struct y_combinator_result {
    F f;
    template<typename T> explicit y_combinator_result(T &&f) : f(forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(forward<F>(f));
}

void solve() {
    int n;
    cin >> n;

    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    int k = n;
    for (int i = 0; i < n; i++) {
        if (b[i] < (i + 1)) {
            k = i;
            break;
        }
    }

    vector<vector<int>> after(n + 1);
    for (int i = 0; i < n; i++) {
        if (b[i] == 0 || b[i] == n + 1) {
            after[0].push_back(i + 1);
        } else {
            after[b[i]].push_back(i + 1);
        }
    }

    for (auto &v : after) {
        sort(v.begin(), v.end(), [&after](int a, int b) {
            return after[a].size() < after[b].size();
        });
    }

    vector<int> res;
    auto add = y_combinator([&](auto self, int x) -> void {
        res.push_back(x);
        for (int a : after[x]) {
            self(a);
        }
    });

    for (int x : after[0]) {
        add(x);
    }

    cout << k << '\n';
    for (int x : res) {
        cout << x << ' ';
    }
    cout << '\n';
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
