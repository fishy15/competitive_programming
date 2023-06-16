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
    template<typename T> explicit y_combinator_result(T &&f) : f(std::forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), std::forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(std::forward<F>(f));
}

enum st {
    UNKNOWN = 0,
    REAL = 1,
    SKIPPED = 2
};

void set_real(int idx, vector<int> &state, const vector<int> &ord, const map<int, vector<int>> &idx_of);
void set_skipped(int idx, vector<int> &state, const vector<int> &ord, const map<int, vector<int>> &idx_of);

void set_real(int idx, vector<int> &state, const vector<int> &ord, const map<int, vector<int>> &idx_of) {
    if (state[idx] == SKIPPED) {
        cout << "No\n";
        exit(0);
    }

    if (state[idx] == UNKNOWN) {
        state[idx] = REAL;

        for (auto x : idx_of.at(ord[idx])) {
            if (x != idx) {
                set_skipped(x, state, ord, idx_of);
            }
        }
    }
}

void set_skipped(int idx, vector<int> &state, const vector<int> &ord, const map<int, vector<int>> &idx_of) {
    if (state[idx] == REAL) {
        cout << "No\n";
        exit(0);
    }

    if (state[idx] == UNKNOWN) {
        state[idx] = SKIPPED;
        set_real(idx - 1, state, ord, idx_of);
        set_real(idx + 1, state, ord, idx_of);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> ord;
    auto dfs = y_combinator([&](auto self, int v, int p) -> void {
        ord.push_back(v);
        for (auto e : adj[v]) {
            if (e != p) {
                self(e, v);
                ord.push_back(v);
            }
        }
    });

    dfs(0, 0);

    map<int, vector<int>> idx_of;
    for (int i = 0; i < (int) ord.size(); i++) {
        idx_of[ord[i]].push_back(i);
    }

    vector<int> state(ord.size());

    // special case since non-unique
    state[0] = REAL;
    state.back() = REAL;

    for (auto &[_, v] : idx_of) {
        for (int i = 1; i < (int) v.size() - 1; i++) {
            set_skipped(v[i], state, ord, idx_of);
        }
    }

    for (auto &[_, v] : idx_of) {
        if (v.size() == 1) {
            set_real(v[0], state, ord, idx_of);
        }
    }

    for (int i = (int) ord.size() - 1; i >= 0; i--) {
        if (state[i] == UNKNOWN) {
            set_real(i, state, ord, idx_of);
        }
    }

    cout << "Yes\n";
    for (int i = 0; i < (int) ord.size() - 1; i++) {
        if (state[i] == REAL) {
            cout << ord[i] + 1 << ' ';
        }
    }
    cout << '\n';

    return 0;
}
