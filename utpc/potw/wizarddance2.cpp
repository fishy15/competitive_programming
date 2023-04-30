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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> p(n);
    vector<pair<int, int>> lr(n);
    vector<set<int>> can_move(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];

        int l = i + p[i];
        if (l >= n) l -= n;

        int r = i - p[i];
        if (r < 0) r += n;

        lr[i] = {l, r};
        can_move[l].insert(i);
        can_move[r].insert(i);
    }

    queue<int> one;
    for (int i = 0; i < n; i++) {
        if (can_move[i].size() == 1) {
            one.push(i);
        }
    }

    vector<bool> is_right(n);
    vector<bool> vis(n);

    while (!one.empty()) {
        auto end_pos = one.front();
        one.pop();

        auto person = *can_move[end_pos].begin();
        vis[person] = true;

        int other;
        if (end_pos == lr[person].first) {
            other = lr[person].second; 
        } else {
            is_right[person] = true;
            other = lr[person].first;
        }

        can_move[other].erase(person);
        can_move[end_pos].erase(person);
        if (can_move[other].size() == 1) {
            one.push(other);
        }
    }

    // all ones removed
    for (int i = 0; i < n; i++) {
        if (!can_move[i].empty()) {
            if (can_move[i].size() != 2) {
                cout << "no dance\n";
                return 0;
            }
        }
    }

    auto dfs = y_combinator([&](auto self, int x, int goes) -> void {
        if (!vis[goes]) {
            vis[goes] = true;
            if (lr[goes].second == x) {
                is_right[goes] = true;
            }

            auto p1 = *can_move[x].begin();
            auto p2 = *next(can_move[x].begin());

            int other;
            if (p1 == goes) {
                other = p2;
            } else {
                other = p1;
            }

            if (lr[other].first == x) {
                self(lr[other].second, other);
            } else {
                self(lr[other].first, other);
            }
        }
    });

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(lr[i].first, i);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << "LR"[is_right[i]];
    }
    cout << '\n';

    return 0;
}
