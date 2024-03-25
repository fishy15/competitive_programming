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

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        adj[i].push_back(p);
        adj[p].push_back(i);
    }

    vector<multiset<int, greater<>>> adj_deg(n);
    vector<int> d_down(n);
    vector<int> pp(n);
    vector<int> uu(n);

    auto dfs = y_combinator([&](auto self, int v, int p) -> void {
        d_down[v] = 0;
        pp[v] = p;
        for (auto e : adj[v]) {
            if (e != p) {
                self(e, v);
                adj_deg[v].insert(d_down[e] + 1);
                d_down[v] = max(d_down[v], d_down[e] + 1);
            }
        }
    });

    dfs(0, 0);

    auto dfs2 = y_combinator([&](auto self, int v, int p, int upd) -> void {
        adj_deg[v].insert(upd);
        uu[v] = upd;
        for (auto e : adj[v]) {
            if (e != p) {
                self(e, v, upd + 1);
            }
        }
    });

    for (auto e : adj[0]) {
        // if this is the path to the lowest leaf
        int upd;
        if (d_down[e] == d_down[0] - 1) {
            if (adj[0].size() == 0) {
                upd = 1;
            } else {
                upd = *next(adj_deg[0].begin()) + 1;
            }
        } else {
            upd = *adj_deg[0].begin() + 1;
        }

        dfs2(e, 0, upd);
    }

    ll ans = 0;
    for (int i = 1; i < n; i++) {
        auto &a = adj_deg[i];
        auto &b = adj_deg[pp[i]];

        a.erase(a.find(d_down[i] + 1));
        if (uu[i] != 1) {
            b.erase(b.find(uu[i] - 1));
        }

        int sz = min(a.size(), b.size());
        auto it1 = a.begin();
        auto it2 = b.begin();
        for (int i = 0; i < sz; i++) {
            ans += min(*it1, *it2);
            it1++;
            it2++;
        }

        a.insert(d_down[i] + 1);
        if (uu[i] != 1) {
            b.insert(uu[i] - 1);
        }
    }

    cout << ans << '\n';
}

int main_() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}

static void run_with_stack_size(int (*func)(void), size_t stsize) {
    char *stack, *send;
    stack = (char *)malloc(stsize);
    send = stack + stsize - 16;
    send = (char *)((uintptr_t)send / 16 * 16);
    asm volatile(
        "mov %%rsp, (%0)\n"
        "mov %0, %%rsp\n"
        :
        : "r"(send));
    func();
    asm volatile("mov (%0), %%rsp\n" : : "r"(send));
    free(stack);
}

int main() {
    run_with_stack_size(main_, 1024 * 1024 * 1024); // run with a 1 GiB stack
    return 0;
}
