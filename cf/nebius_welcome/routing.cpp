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

bool vis[20][1 << 20];
int p[20][1 << 20][2];
bool edge[20][20];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
        edge[a][b] = true;
        edge[b][a] = true;
    }

    vector<int> can_vis(n);
    for (int i = 0; i < n; i++) {
        can_vis[i] = 1 << i;
        for (auto e : adj[i]) {
            can_vis[i] |= 1 << e;
        }
    }

    for (int st = 0; st < n; st++) {
        memset(vis, 0, sizeof vis);
        memset(p, -1, sizeof p);

        queue<pair<int, int>> q;
        q.push({st, can_vis[st]});
        vis[st][can_vis[st]] = true;

        while (!q.empty()) {
            auto [v, m] = q.front();
            q.pop();

            for (auto e : adj[v]) {
                int m2 = m | can_vis[e];
                if (!vis[e][m2]) {
                    vis[e][m2] = true;
                    p[e][m2][0] = v;
                    p[e][m2][1] = m;
                    q.push({e, m2});
                }
            }
        }

        int needed = (1 << n) - 1;

        vector<bool> on_cycle(n);
        vector<int> to(n, -1);
        for (int i = 0; i < n; i++) {
            if (edge[st][i] && vis[i][needed]) {
                int cur = i;
                int cur_m = needed;

                to[cur] = st;
                on_cycle[cur] = true;
                while (cur != st) {
                    auto p_node = p[cur][cur_m][0];
                    auto p_mask = p[cur][cur_m][1];

                    cout << cur << ' ' << p_node << '\n';

                    to[p_node] = cur;
                    on_cycle[p_node] = true;

                    cur = p_node;
                    cur_m = p_mask;
                }

                for (auto x : to) {
                    cout << x + 1 << ' ';
                }
                cout << '\n';

                for (int i = 0; i < n; i++) {
                    if (to[i] == -1) {
                        for (auto e : adj[i]) {
                            if (on_cycle[e]) {
                                to[i] = e;
                                break;
                            }
                        }
                    }
                }

                cout << "Yes\n";
                for (auto x : to) {
                    cout << x + 1 << ' ';
                }
                cout << '\n';
                return 0;
            }
        }
    }

    cout << "No\n";

    return 0;
}
