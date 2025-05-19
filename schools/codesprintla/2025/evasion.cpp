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
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

template<typename T>
using min_pq = priority_queue<T, vector<T>, greater<>>;

vector<ll> time_visited_shortest(const vector<vector<pair<int, ll>>> &adj, int s, int t) {
    int n = sz(adj);
    min_pq<pair<ll, int>> pq;
    vector<ll> dist(n, INFLL);

    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [dd, u] = pq.top();
        pq.pop();

        if (dd != dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dd + w < dist[v]) {
                dist[v] = dd + w;
                pq.push({dist[v], v});
            }
        }
    }

    vector<bool> vis(n);
    queue<int> q;
    q.push(t);
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        vis[u] = true;
        for (auto [v, w] : adj[u]) {
            if (!vis[v] && dist[v] == dist[u] - w) {
                vis[v] = true;
                q.push(v);
            }
        }
    }

    rep(i, 0, n) {
        if (!vis[i]) {
            dist[i] = -1;
        }
    }

    return dist;
}

struct mytime {
    ll t;
    bool eps;

    mytime(ll _t, bool _eps) : t(_t), eps(_eps) {}
    mytime(ll x) : t(x), eps(false) {}
    mytime() : mytime(0) {}

    mytime operator+(const mytime &other) const {
        return {t + other.t, eps || other.eps};
    }

    mytime witheps() const {
        return {t, true};
    }

    bool operator<(const mytime &other) const {
        return tie(t, eps) < tie(other.t, other.eps);
    }

    bool operator>(const mytime &other) const {
        return other < *this;
    }

    bool operator<=(const mytime &other) const {
        return !(*this > other);
    }

    bool operator==(const mytime &other) const {
        return tie(t, eps) == tie(other.t, other.eps);
    }

    bool operator!=(const mytime &other) const {
        return tie(t, eps) != tie(other.t, other.eps);
    }
};

struct state {
    mytime dist;
    int x;
    int stage;
    bool operator<(const state &other) const {
        return tie(dist, x, stage) < tie(other.dist, other.x, other.stage);
    }
    bool operator>(const state &other) const {
        return tie(dist, x, stage) > tie(other.dist, other.x, other.stage);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n, m, s, t, p;
    cin >> n >> m >> s >> t >> p;
    s--;
    t--;
    p--;

    vector<vector<pair<int, ll>>> adj(n);
    rep(i, 0, m) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    auto stage1 = time_visited_shortest(adj, p, s);
    auto stage2 = time_visited_shortest(adj, s, t);
    rep(i, 0, n) {
        if (stage2[i] != -1) {
            stage2[i] += stage1[s];
        }
    }

    // shortest time to arrive t < stage1, stage1 <= t < stage2, >= stage2
    vector<array<mytime, 3>> arrive_stage(n);
    rep(i, 0, n) {
        arrive_stage[i].fill(INFLL);
    }

    min_pq<state> pq;
    auto maybe_push = [&](int v, int st, mytime t) {
        if (t < arrive_stage[v][st]) {
            arrive_stage[v][st] = t;
            pq.push({t, v, st});
        }
    };

    maybe_push(s, 0, mytime(0).witheps());

    auto intersect = [&](mytime start1, mytime end1, mytime start2, mytime end2) {
        return !(end1 < start2 || end2 < start1);
    };

    while (!pq.empty()) {
        auto [dd, u, st] = pq.top();
        pq.pop();

        if (arrive_stage[u][st] != dd) {
            continue;
        }

        if (st == 0) {
            // try staying at this node until after they pass through
            if (stage1[u] == -1) {
                maybe_push(u, 1, dd);
            } else {
                bool temp_exit = false;
                for (auto [v, w] : adj[u]) {
                    if (stage1[u] != stage1[v] + w) {
                        if (stage1[v] != stage1[u] + w && (stage1[u] != stage2[u] || stage2[v] != stage2[u] + w)) {
                            // if its not possible for them to come from here
                            temp_exit = true;
                            break;
                        }
                    }
                }
                if (temp_exit) {
                    maybe_push(u, 1, mytime(stage1[u]).witheps());
                }
            }
        }

        if (st == 1) {
            // try staying at this node until after they pass through
            if (stage2[u] == -1) {
                maybe_push(u, 2, dd);
            } else {
                bool temp_exit = false;
                for (auto [v, w] : adj[u]) {
                    if (stage2[u] != stage2[v] + w) {
                        if (stage2[v] != stage2[u] + w) {
                            // if its not possible for them to come from here
                            temp_exit = true;
                            break;
                        }
                    }
                }
                if (temp_exit) {
                    maybe_push(u, 2, mytime(stage2[u]).witheps());
                }
            }
        }

        for (auto [v, w] : adj[u]) {
            auto reach = dd + 2 * w;
            int new_st = 0;
            if (stage1[v] != -1 && mytime(stage1[v]) <= reach) {
                new_st = 1;
            }
            if (stage2[v] != -1 && mytime(stage2[v]) <= reach) {
                new_st = 2;
            }

            if (mytime(stage1[v]) != reach && mytime(stage2[v]) != reach) {
                bool ok = true;
                if (stage1[u] != -1 && stage1[v] != -1) {
                    if (stage1[v] + w == stage1[u]) {
                        // if they are going v -> u, backwards on the current edge
                        if (intersect(dd, reach, stage1[v], stage1[u])) {
                            ok = false;
                        }
                    }
                }

                if (stage2[u] != -1 && stage2[v] != -1) {
                    if (stage2[v] + w == stage2[u]) {
                        // if they are going v -> u, backwards on the current edge
                        if (intersect(dd, reach, stage2[v], stage2[u])) {
                            ok = false;
                        }
                    }
                }

                if (ok) {
                    maybe_push(v, new_st, reach);
                }
            }
        }
    }

    auto ans = min(arrive_stage[t][0], arrive_stage[t][1]);
    if (ans == mytime(INFLL)) {
        cout << "-1\n";
    } else {
        cout << ans.t << '\n';
    }

    return 0;
}
