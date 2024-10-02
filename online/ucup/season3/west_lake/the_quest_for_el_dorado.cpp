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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

template<typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<array<int, 3>>> adj(n);
    vector<int> companies;
    rep(i, 0, m) {
        int u, v, c, l;
        cin >> u >> v >> c >> l;
        u--;
        v--;
        c--;
        adj[u].push_back({v, c, l});
        adj[v].push_back({u, c, l});
        companies.push_back(c);
    }

    // {company, dist}
    vector<pair<int, int>> tickets(k);
    rep(i, 0, k) {
        cin >> tickets[i].first >> tickets[i].second;
        tickets[i].first--;
        companies.push_back(tickets[i].first);
    }

    sort(all(companies));
    companies.erase(unique(all(companies)), end(companies));

    auto compress_company = [&](int x) {
        return lower_bound(all(companies), x) - begin(companies);
    };


    // {length, to}
    vector<min_pq<pair<int, int>>> unused_edges(sz(companies));

    // ticket used, dist on ticket
    vector<pair<int, ll>> dist(n, {INF, INF});

    auto proc = [&](auto &pq, int u) {
        auto [cur_ticket, cur_used] = dist[u];
        auto [cur_company, max_dist] = tickets[cur_ticket];
        for (auto [v, c, l] : adj[u]) {
            if (c == cur_company && cur_used + l <= max_dist) {
                auto new_dist = pair{cur_ticket, cur_used + l};
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                    pq.push({new_dist.second, v});
                }
            } else {
                unused_edges[compress_company(c)].push({l, v});
            }
        }
    };

    rep(i, 0, k) {
        min_pq<pair<ll, int>> dijk_pq;

        if (i == 0) {
            dist[0] = {0, 0};
            proc(dijk_pq, 0);
        }

        auto [cur_company, max_dist] = tickets[i];

        // add all extra edges for initial state
        auto &comp_pq = unused_edges[compress_company(cur_company)];
        while (!comp_pq.empty()) {
            auto [l, v] = comp_pq.top();
            if (l > max_dist) {
                break;
            }
            comp_pq.pop();
            auto new_dist = pair<int, ll>{i, l};
            if (new_dist < dist[v]) {
                dist[v] = new_dist;
                dijk_pq.push({l, v});
            }
        }

        while (!dijk_pq.empty()) {
            auto [dd, v] = dijk_pq.top();
            dijk_pq.pop();
            if (dist[v] == pair{i, dd}) {
                proc(dijk_pq, v);
            }
        }
    }

    rep(i, 0, n) {
        cout << (dist[i].first != INF);
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
