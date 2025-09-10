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

struct node {
    array<node *, 26> child;
    ll size;
    node() {
        child.fill(nullptr);
        size = 1;
    }
};

ll get_size(node *n) {
    return n == nullptr ? 0 : n->size;
}

node *join(node *left, node *right) {
    if (left == nullptr) {
        return right;
    } else if (right == nullptr) {
        return left;
    } else {
        left->size = 1;
        rep(i, 0, 26) {
            left->child[i] = join(left->child[i], right->child[i]);
            left->size += get_size(left->child[i]);
        }
        return left;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<ll> c(n);
    rep(i, 0, n) {
        cin >> c[i];
    }

    string s;
    cin >> s;

    vector<vector<int>> adj(n);
    rep(i, 0, n-1) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<ll> dif(n);
    auto dfs = [&](auto &&self, int v, int p) -> node * {
        node *res = new node();
        for (auto e : adj[v]) {
            if (e != p) {
                auto e_node = self(self, e, v);

                int pos = s[e] - 'a';
                res->child[pos] = join(res->child[pos], e_node);
            }
        }

        rep(i, 0, 26) {
            res->size += get_size(res->child[i]);
        }
        dif[v] = res->size;
        return res;
    };
    dfs(dfs, 0, 0);

    int ans = 0;
    int cnt = 0;
    rep(i, 0, n) {
        if (dif[i] + c[i] > ans) {
            ans = dif[i] + c[i];
            cnt = 1;
        } else if (dif[i] + c[i] == ans) {
            cnt++;
        }
    }

    cout << ans << '\n';
    cout << cnt << '\n';

    return 0;
}
