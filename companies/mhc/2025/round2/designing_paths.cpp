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
#include <future>

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

struct graph {
    struct node {
        pair<ll, ll> dist;
        int orig, route_idx;
        vector<int> adj;
    };

    vector<node> nodes;

    int add_node(int orig, int idx) {
        node n{{INFLL, 0}, orig, idx, {}};
        nodes.push_back(n);
        return sz(nodes) - 1;
    }
};

struct testcase {
    int n, k, m;
    vector<vector<int>> routes;
    ll ans;
    
    static testcase read() {
        int n, k, m;
        cin >> n >> k >> m;

        vector<vector<int>> routes(m);
        rep(i, 0, m) {
            int l;
            cin >> l;
            rep(j, 0, l) {
                int x;
                cin >> x;
                x--;
                routes[i].push_back(x);
            }
        }

        return testcase{n, k, m, routes};
    }

    void solve() {
        ans = 0;

        graph g;
        vector<int> first(n);

        // create original graph
        rep(i, 0, n) {
            first[i] = g.add_node(i, -1);
        }

        rep(i, 0, m) {
            int last = -1;
            for (auto x : routes[i]) {
                auto cur = g.add_node(x, i);
                
                // add node <==> original
                g.nodes[cur].adj.push_back(first[x]);

                g.nodes[first[x]].adj.push_back(cur);

                // add node from last node
                if (last != -1) {
                    g.nodes[last].adj.push_back(cur);
                }

                last = cur;
            }
        }

        priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> pq;
        g.nodes[first[0]].dist = {0, 0};
        pq.push({0, 0, first[0]});
        while (!pq.empty()) {
            auto [d, t, v] = pq.top();
            pq.pop();
            if (g.nodes[v].dist != pair{d, t}) {
                continue;
            }

            for (auto e : g.nodes[v].adj) {
                pair<ll, ll> nd;
                if (g.nodes[v].route_idx == -1) {
                    // if we are original, then we start everything with 0 rides taken
                    nd = pair{d + 1, 0};
                } else if (g.nodes[e].route_idx == -1) {
                    // can always transition back to original 
                    nd = pair{d, 0};
                } else {
                    if (t < k) {
                        nd = pair{d, t + 1};
                    } else {
                        nd = pair{d + 1, 1};
                    }
                }

                if (nd < g.nodes[e].dist) {
                    g.nodes[e].dist = nd;
                    pq.push({nd.first, nd.second, e});
                }
            }
        }

        rep(i, 0, n) {
            auto d = g.nodes[first[i]].dist.first;
            if (d == INFLL) {
                ans += (ll) -1 * (i + 1);
            } else {
                ans += (ll) d * (i + 1);
            }
        }
    }
};

vector<testcase> tests;

const int PARALLEL=8;
void paralleltests(int l=0, int r=PARALLEL-1) {
    if (l==r) {
        for(int i=l;i<(int)tests.size();i+=PARALLEL) {
            tests[i].solve();
        }
        return;
    }
    ll mid = (l+r)/2;
    auto handle = std::async(launch::async,paralleltests, l,mid);
    paralleltests(mid+1,r);
    handle.wait();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    rep(i, 0, t) {
        tests.push_back(testcase::read());
    }

    paralleltests();

    rep(i, 0, t) {
        cout << "Case #" << i + 1 << ": " << tests[i].ans << '\n';
    }

    return 0;
}
