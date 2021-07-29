/*
 * For the nodes at height g, their value will be the lowest value in their subtree. For the higher nodes,
 * their value will be the lowest value in the subtree that is higher than the children. The other nodes
 * can be removed in any order to give this tree, so we can mark which ones need to be removed and then 
 * print out the result from highest to lowest index.
 */
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
#include <list>
#include <functional>

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

int L(int v) {
    return 2 * v + 1;
}

int R(int v) {
    return 2 * v + 2;
}

int nums[1 << 20];
vector<pair<int, int>> vals[1 << 20];
bool is_used[1 << 20];
int remain[1 << 20];

void solve() {
    int h, g; cin >> h >> g;

    fill(is_used, is_used + (1 << h), false);
    for (int i = 0; i < (1 << h) - 1; i++) {
        cin >> nums[i];
    }

    auto solve = y_combinator([&](auto self, int v, int d) -> void {
        vals[v].push_back({nums[v], v});

        if (d < h - 1) {
            self(L(v), d + 1);
            self(R(v), d + 1);
            vals[v].resize(vals[L(v)].size() + vals[R(v)].size() + 1);
            merge(vals[L(v)].begin(), vals[L(v)].end(), vals[R(v)].begin(), vals[R(v)].end(), 
                  vals[v].begin() + 1, greater<>());
            vals[L(v)].clear();
            vals[R(v)].clear();
        }

        if (d < g) {
            int left = 0;
            int right = 0;
            if (d < g - 1) {
                left = remain[L(v)];
                right = remain[R(v)];
            }

            while (vals[v].back().first < max(left, right)) {
                vals[v].pop_back();
            }

            remain[v] = vals[v].back().first;
            is_used[vals[v].back().second] = true;
            vals[v].pop_back();
        }
    });

    solve(0, 0);
    vals[0].clear(); 

    ll sum = 0;

    for (int i = 0; i < (1 << h) - 1; i++) {
        if (is_used[i]) {
            sum += nums[i];
        }
    }

    cout << sum << '\n';

    for (int i = (1 << h) - 2; i >= 0; i--) {
        if (!is_used[i]) {
            cout << i + 1 << ' ';
        }
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
