/*
 * Use a persistent segtree, where version 1 stores just root, then version 2 stores the next depth down, etc.
 * For the k-blocking subtree for node v, we can then query the entire subtree in the (depth_v + k)th 
 * version of the segtree since all the nodes below will be marked with infinity instead of their true 
 * value.
 */
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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100010
#define MAXM 1000010

using namespace std;

struct pst {
    struct node {
        int v;
        node *l, *r;
        node() : node(INF) {}
        node(int v) : v(v), l(nullptr), r(nullptr) {}
    };

    int n;
    vector<node*> root;
    deque<node> buffer;

    pst(int n) : n(n) {
        root.push_back(build(0, n - 1)); 
    }

    node *build(int l, int r) {
        node *cur = new_node();
        if (l != r) {
            int m = (l + r) / 2;
            cur->l = build(l, m);
            cur->r = build(m + 1, r);
        }
        return cur;
    }

    void copy(int pt, int t) {
        if ((int)(root.size()) <= t) {
            root.resize(t + 1);
        }
        root[t] = new_node(*root[pt]);
    }

    void upd(int pt, int t, int x, int v) {
        if ((int)(root.size()) <= t) {
            root.resize(t + 1);
        }
        root[t] = upd(root[pt], x, v, 0, n - 1);
    }

    node *upd(node *p, int x, int v, int l, int r) {
        node *cur = new_node(*p);
        if (l == r) {
            cur->v = v;
        } else {
            int m = (l + r) / 2;
            if (x <= m) {
                cur->l = upd(cur->l, x, v, l, m);
            } else {
                cur->r = upd(cur->r, x, v, m + 1, r);
            }
            cur->v = min(cur->l->v, cur->r->v);
        }
        return cur;
    }

    int qry(int t, int x, int y) { 
        return qry(root[t], x, y, 0, n - 1);
    }

    int qry(node *p, int x, int y, int l, int r) {
        if (y < l || x > r) {
            return INF;
        } else if (x <= l && r <= y) {
            return p->v;
        } else {
            int m = (l + r) / 2;
            return min(qry(p->l, x, y, l, m), qry(p->r, x, y, m + 1, r));
        }
    }

    template<typename... Args>
    node *new_node(Args... args) {
        buffer.emplace_back(args...);
        return &buffer.back();
    }
};

int n, r, m;
int nums[MAXN];
vector<int> adj[MAXN];
int p[MAXM];
int q[MAXM];
int depth[MAXN];
vector<int> at_depth[MAXN];

int t = -1;
int in[MAXN];
int out[MAXN];

void dfs(int v, int p, int d) {
    in[v] = ++t;
    depth[v] = d;
    at_depth[d].push_back(v);
    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v, d + 1);
        }
    }
    out[v] = t;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, r; cin >> n >> r;
    r--;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> p[i] >> q[i];
    }

    pst st(n);

    dfs(r, -1, 1);
    for (int i = 1; i <= n; i++) {
        st.copy(i - 1, i);
        for (int v : at_depth[i]) {
            st.upd(i, i, in[v], nums[v]);
        }
    }

    int last = 0;
    for (int i = 0; i < m; i++) {
        int v = (last + p[i]) % n;
        int k = (last + q[i]) % n;

        int lowest = min(depth[v] + k, n);
        last = st.qry(lowest, in[v], out[v]);
        cout << last << '\n';
    }

    return 0;
}
