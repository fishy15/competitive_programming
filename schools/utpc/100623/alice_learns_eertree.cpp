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

bool ok(int h) {
    return h == 0 || (h & (h - 1)) == 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    string s;
    cin >> s;

    vector<int> rep(n);
    for (int i = 0; i < n; i++) {
        rep[i] = 1 << (s[i] - 'A');
    }

    vector adj(n, vector<int>());
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> hash(n);
    vector<int> pp(n);
    int cur_ans = 0;
    auto dfs = y_combinator([&](auto self, int v, int p) -> void {
        hash[v] = rep[v];
        pp[v] = p;
        for (auto e : adj[v]) {
            if (e != p) {
                self(e, v);
                hash[v] ^= hash[e];
            }
        }

        if (ok(hash[v])) cur_ans++;
    });

    dfs(0, 0);

    int tot_hash = 0;
    for (auto x : rep) {
        tot_hash ^= x;
    }

    vector<int> ans(n);
    ans[0] = cur_ans;

    // assume u is the current root
    auto move = [&](int u, int v) {
        if (u == pp[v]) {
            if (ok(hash[v])) {
                cur_ans--;
            }
            if (ok(hash[v] ^ tot_hash)) {
                cur_ans++;
            }
        } else {
            if (ok(hash[u])) {
                cur_ans++;
            }
            if (ok(hash[u] ^ tot_hash)) {
                cur_ans--;
            }
        }
    };

    auto reroot = y_combinator([&](auto self, int v, int p) -> void {
        ans[v] = cur_ans;
        for (auto e : adj[v]) {
            if (e != p) {
                move(v, e);
                self(e, v);
                move(e, v);
            }
        }
    });

    reroot(0, 0);

    for (auto x : ans) {
        cout << x << '\n';
    }

    return 0;
}
