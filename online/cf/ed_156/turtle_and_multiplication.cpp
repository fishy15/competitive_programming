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
#include <cassert>

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

constexpr int MAXN = 300'000;
bool is_prime[MAXN + 1];
vector<int> primes;

void precomp() {
    fill(begin(is_prime) + 2, end(is_prime), true);
    for (ll i = 2; i <= MAXN; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = i * i; j <= MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

ll comp_edges(ll n) {
    ll edges = n * (n - 1) / 2 + n;
    if (n % 2 == 0) {
        // every node has odd degree, so subtract (n - 2) / 2 edges
        edges -= (n - 2) / 2;
    }
    return edges;
}

using vi = vector<int>;
using pii = pair<int, int>;
#define pb push_back
vi eulerWalk(vector<vector<pii>>& gr, int nedges, int src=0) {
	int n = sz(gr);
	vi D(n), its(n), eu(nedges), ret, s = {src};
	D[src]++; // to allow Euler paths, not just cycles
	while (!s.empty()) {
		int x = s.back(), y, e, &it = its[x], end = sz(gr[x]);
		if (it == end){ ret.pb(x); s.pop_back(); continue; }
		tie(y, e) = gr[x][it++];
		if (!eu[e]) {
			D[x]--, D[y]++;
			eu[e] = 1; s.pb(y);
		}}
	for (int x : D) if (x < 0 || sz(ret) != nedges+1) return {};
	return {ret.rbegin(), ret.rend()};
}

void solve() {
    int n;
    cin >> n;

    ll groups = 1;
    while (comp_edges(groups) + 1 < n) {
        groups++;
    }

    vector<vector<pair<int, int>>> adj(groups);
    int edge_num = 0;
    rep(i, 0, groups) {
        adj[i].push_back({i, edge_num});
        edge_num++;
        rep(j, i+1, groups) {
            if (groups % 2 == 0 && i % 2 == 0 && i + 1 == j) {
                if (i == 0) {
                    adj[i].push_back({j, edge_num});
                    adj[j].push_back({i, edge_num});
                    edge_num++;
                }
            } else {
                adj[i].push_back({j, edge_num});
                adj[j].push_back({i, edge_num});
                edge_num++;
            }
        }
    }

    auto edges = eulerWalk(adj, edge_num);
    rep(i, 0, n) {
        cout << primes[edges[i]] << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
