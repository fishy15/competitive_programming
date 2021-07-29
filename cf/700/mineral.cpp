/*
 * We can store a persistent segtree, which spans over each color, and the operation of the segtree will be
 * xor. For each color, we can compute some hash value (to minimize chance of different colors affecting 
 * each other). Having a color an even number of times will mean that the xor is 0, so a non-zero xor means
 * that value appears an odd number of times on the path. To build the persistent segtree, we DFS from 1,
 * and the segtree for node v will be a copy of the segtree for its parent + an update number at vertex v.
 *
 * With this segtree, we can get the xor of the hash values on the path from 1 to v, and we can use this 
 * information to get the hash value of the path from any point to another. If the hash of that path is 0, 
 * then there is no color that appears an odd number of times (assuming no collisions), and a non-zero hash
 * means that there is at least one odd value on the path. Additionally, because we only want colors between
 * some values L and R, we can only query between those to get the hash value.
 *
 * Finally, we need to figure out how to actually find an odd value given that one exists. We can do this
 * by binary searching on the segtree. If m is the midpoint of [x, y] and there exists a non-zero hash value
 * in the interval, then we can either check [x, m] or [m + 1, y]. If a range lies completely outside of the
 * L and R values that we are concerned with, then we can return -1. Otherwise, we can continue to check 
 * the halves that don't have zero values until we find an interval of size 1 that contains a non-zero hash
 * value. This is the answer, so we can return that. If nothing is found, then -1 will be returned.
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
#include <random>
#include <chrono>
#include <climits>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 300010

using namespace std;

int n, q;
int nums[MAXN];
vector<int> adj[MAXN];
int in[MAXN];
int out[MAXN];
int up[MAXN][20];
ll rr[MAXN];
int t = 0;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct pst {
    struct node {
        ll v;
        int l, r;
        node *c[2];
    };

    int sz = 0;
    node all[3 * 20 * MAXN];

    void upd(node *p, int x, ll v) {
        if (p->l == p->r) {
            p->v ^= v;
        } else {
            int m = (p->l + p->r) / 2;
            if (x <= m) {
                p->c[0] = new_node(p->c[0]);
                upd(p->c[0], x, v);
            } else {
                p->c[1] = new_node(p->c[1]);
                upd(p->c[1], x, v);
            }
            p->v = p->c[0]->v ^ p->c[1]->v;
        }
    }

    ll qry(node *p, int x, int y) {
        if (x <= p->l && p->r <= y) return p->v;
        if (x > p->r || y < p->l) return 0;
        return qry(p->c[0], x, y) ^ qry(p->c[1], x, y);
    }

    node *new_node(int l, int r) {
        node n;
        n.l = l;
        n.r = r;
        n.v = 0;
        if (l != r) {
            int m = (l + r) / 2;
            n.c[0] = new_node(l, m);
            n.c[1] = new_node(m + 1, r);
        } else {
            n.c[0] = nullptr;
            n.c[1] = nullptr;
        }
        all[sz++] = n;
        return all + sz - 1;;
    }

    node *new_node(const node *n2) {
        all[sz++] = *n2;
        return all + sz - 1;
    }

    vector<node*> st;

    pst(int l, int r) {
        st.push_back(new_node(l, r));
    }

    void upd(int t, int x, ll v) {
        upd(st[t], x, v);
    }

    ll qry(int t, int x, int y) {
        return qry(st[t], x, y);
    }
};

using node = pst::node;

pst pst(0, MAXN); 

void dfs(int v, int p) {
    in[v] = t++;

    if (v) pst.st[v] = pst.new_node(pst.st[p]);
    pst.upd(v, nums[v], rr[nums[v]]);

    up[v][0] = p;
    for (int i = 1; i < 20; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }

    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v);
        }
    }
    out[v] = t++;
}

bool anc(int x, int y) {
    return in[x] <= in[y] && out[y] <= out[x];
}

int lca(int x, int y) {
    if (anc(x, y)) return x;
    if (anc(y, x)) return y;
    for (int i = 19; i >= 0; i--) {
        if (!anc(up[x][i], y)) {
            x = up[x][i];
        }
    }
    return up[x][0];
}

int search(node *a, node *b, int lca, int l, int r, int x, int y) {
    if (x > r || y < l) return -1; 
    ll v = a->v ^ b->v;
    if (x <= nums[lca] && nums[lca] <= y) v ^= rr[nums[lca]];
    if (!v) return -1;
    if (x == y) return x;
    int m = (x + y) / 2;
    int res = search(a->c[0], b->c[0], lca, l, r, x, m);
    if (res == -1) res = search(a->c[1], b->c[1], lca, l, r, m + 1, y);
    return res;
}

ll randint() {
    return uniform_int_distribution<ll>(LLONG_MIN, LLONG_MAX)(rng);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        rr[i] = randint();
    }

    pst.st.resize(n);
    dfs(0, 0);

    for (int i = 0; i < q; i++) {
        int u, v, l, r; cin >> u >> v >> l >> r;
        u--; v--;
        int lc = lca(u, v);
        cout << search(pst.st[u], pst.st[v], lc, l, r, 0, MAXN) << '\n';
    }

    return 0;
}
