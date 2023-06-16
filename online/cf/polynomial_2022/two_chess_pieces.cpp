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

    int n, d;
    cin >> n >> d;

    vector adj(n, vector<int>());
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int m1, m2;
    set<int> need1, need2;

    cin >> m1;
    for (int i = 0; i < m1; i++) {
        int x;
        cin >> x;
        x--;

        need1.insert(x);
    }

    cin >> m2;
    for (int i = 0; i < m2; i++) {
        int x;
        cin >> x;
        x--;

        need2.insert(x);
    }

    vector up(n, vector<int>(20));

    auto dfs = y_combinator([&](auto self, int v, int p) -> void {
        up[v][0] = p;
        for (int i = 1; i < 20; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }

        for (auto e : adj[v]) {
            if (e != p) {
                self(e, v);
            }
        }
    });

    auto get_up = [&](int v, int dist) {
        for (int i = 19; i >= 0; i--) {
            if ((dist >> i) & 1) {
                v = up[v][i];
            }
        }

        return v;
    };

    dfs(0, 0);

    vector<int> add1, add2;
    for (auto x : need1) {
        add2.push_back(get_up(x, d));
    }

    for (auto x : need2) {
        add1.push_back(get_up(x, d));
    }

    for (auto x : add1) need1.insert(x);
    for (auto x : add2) need2.insert(x);

    auto calc_ans = [n, &adj](const set<int> &need) {
        vector<bool> need_visit(n);

        auto need_visit_dfs = y_combinator([&adj, &need, &need_visit](auto self, int v, int p) -> bool {
            bool counted = false;

            for (int e : adj[v]) {
                if (e != p) {
                    counted |= self(e, v);
                }
            }

            counted |= (need.count(v) == 1);
            need_visit[v] = counted;
            return counted;
        });

        need_visit_dfs(0, 0);

        auto calc_ans_aux = y_combinator([&adj, &need_visit](auto self, int v, int p, int &cnt) -> void {
            for (int e : adj[v]) {
                if (e != p && need_visit[e]) {
                    cnt += 2;
                    self(e, v, cnt);
                }
            }
        });

        int counter = 0;
        calc_ans_aux(0, 0, counter);

        return counter;
    };

    cout << calc_ans(need1) + calc_ans(need2) << '\n';

    return 0;
}
