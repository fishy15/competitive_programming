/*
 * We can use the segtree over the values to compute the shortest path after all of the updates. 
 * Specifically, if we have a shortest path through the left half and a shortest path through the right
 * half, then we can simply use the shortest path between the two nodes in the middle to connect them. 
 * However, we also have to make sure that the last edge used in the path for the left half is not the first
 * edge used in the shortest path between the two middle nodes (and similarly for the middle sequence to the
 * path for the right half). To get around this, we can store multiple options which use specific first and
 * last edge values.
 *
 * More specifically, we only need 5 shortest paths, where no 2 paths use the same first and last edge and 
 * no 3 paths use the same first edge or last edge. To see why this is true, suppose we fix the path used
 * for the first half and the path used for the second half. In the path that joins the two halves, at max 
 * one edge is unable to be used because of the left path. If 3 paths ended with the same edge, at max one
 * of them would be unusable, so the longer of the two paths is useless (since we can always choose the 
 * smaller one). Therefore, we need at max 2 edges that use the same starting or ending edge. We can then
 * just test all 125 combinations (5 left half * 5 middle * 5 right half) when combining two nodes in the
 * segtree. To find all of the shortest paths needed, we can use modified dijkstra, so the time complexity 
 * is O(NM log N + 125 (L + T log L)). 
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
#define MAXN 2010
#define MAXL 100010

using namespace std;

struct path {
    int start, end;
    ll length;

    path(int s, int e, ll l) : start(s), end(e), length(l) {}
    path() : path(0, 0, 0) {}
};

struct min_cost {
    vector<path> min;
};

int n, m, t, l;
int nums[MAXL];
min_cost min_dist[MAXN][MAXN];
vector<int> adj[MAXN];
vector<pair<int, ll>> edge;

bool same(int x, int y) {
    return x == y || (x ^ 1) == y;
}

bool set_vals(vector<path> &cur, ll cost, int first, int last) {
    if (cur.size() >= 5) return false;

    int x_cnt = 0;
    int y_cnt = 0;
    for (auto &p : cur) {
        if (p.start == first) x_cnt++;
        if (p.end == last) y_cnt++;
        if (p.start == first && p.end == last) return false;
    }

    if (x_cnt < 2 && y_cnt < 2) {
        cur.emplace_back(first, last, cost);
        return true;
    }

    return false;
}

// segtree stuff
struct segtree {
    struct node {
        int l, r, sz;
        vector<path> combo;

        node(int l, int r, int sz) : l(l), r(r), sz(sz) {}
        node() : node(0, 0, 0) {}
        int size() const { return sz; }
    };

    static int n;
    node st[4 * MAXL];

    void combo(node &ans, const vector<path> &left, const vector<path> &right) {
        map<pair<int, int>, ll> m;
        for (auto &p1 : left) {
            for (auto &p2 : right) {
                if (same(p1.end, p2.start) || p2.length == 0) continue;
                pair<int, int> pp = {p1.start, p2.end};
                if (!m.count(pp)) {
                    m[pp] = p1.length + p2.length;
                } else {
                    m[pp] = min(m[pp], p1.length + p2.length);
                }
            }
        }

        vector<path> v;
        for (auto p : m) {
            v.emplace_back(p.first.first, p.first.second, p.second);
        }

        sort(v.begin(), v.end(), [](const path &p1, const path &p2) {
            return p1.length < p2.length;
        });

        for (auto p : v) {
            set_vals(ans.combo, p.length, p.start, p.end);
        }
    }

    void combo(node &ans, const vector<path> &left, const vector<path> &right, int x1, int x2) {
        map<pair<int, int>, ll> m;
        for (auto &p1 : left) {
            for (auto &p2 : right) {
                for (auto &join : min_dist[x1][x2].min) {
                    if (same(p1.end, join.start) || same(join.end, p2.start) || join.length == 0) continue;
                    pair<int, int> pp = {p1.start, p2.end};
                    if (!m.count(pp)) {
                        m[pp] = p1.length + p2.length + join.length;
                    } else {
                        m[pp] = min(m[pp], p1.length + p2.length + join.length);
                    }
                }
            }
        }
        vector<path> v;

        for (auto p : m) {
            v.emplace_back(p.first.first, p.first.second, p.second);
        }

        sort(v.begin(), v.end(), [](const path &p1, const path &p2) {
            return p1.length < p2.length;
        });

        for (auto p : v) {
            set_vals(ans.combo, p.length, p.start, p.end);
        }
    }

    node merge(const node &left, const node &right) {
        node ans;
        ans.l = left.l;
        ans.r = right.r;
        ans.sz = left.sz + right.sz;

        if (left.size() == 1) {
            for (path &p : min_dist[left.l][right.r].min) {
                if (p.length > 0) {
                    ans.combo.push_back(p);
                }
            }
            return ans;
        }

        if (right.size() == 1) {
            combo(ans, left.combo, min_dist[left.r][right.l].min);
        } else {
            combo(ans, left.combo, right.combo, left.r, right.l);
        }

        return ans;
    }

    void build(int v = 1, int l = 0, int r = n - 1) {
        if (l == r) {
            st[v] = node(nums[l], nums[l], 1);
        } else {
            int m = (l + r) / 2;
            build(2 * v, l, m);
            build(2 * v + 1, m + 1, r);
            st[v] = merge(st[2 * v], st[2 * v + 1]);
        }
    }

    void upd(int x, int y, int v = 1, int l = 0, int r = n - 1) {
        if (l == r) {
            nums[x] = y;
            st[v] = node(nums[l], nums[l], 1);
        } else {
            int m = (l + r) / 2;
            if (x <= m) {
                upd(x, y, 2 * v, l, m);
            } else {
                upd(x, y, 2 * v + 1, m + 1, r);
            }
            st[v] = merge(st[2 * v], st[2 * v + 1]);
        }
    }
} st;

int segtree::n = 1;

void dijk(int x) {
    // {dist, pos, first edge, last edge}
    priority_queue<array<ll, 4>, vector<array<ll, 4>>, greater<array<ll, 4>>> pq;
    min_dist[x][x].min.emplace_back(x, x, 0);

    for (int e : adj[x]) {
        auto [nxt, cost] = edge[e];
        pq.push({cost, nxt, e, e});
    }

    while (!pq.empty()) {
        auto [cost, pos, first, last] = pq.top();
        pq.pop();

        bool res = set_vals(min_dist[x][pos].min, cost, first, last);
        if (!res) continue;

        for (int e : adj[pos]) {
            if (!same(e, last)) {
                auto [nxt, cost2] = edge[e];
                pq.push({cost + cost2, nxt, first, e});
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> t >> l;
    for (int i = 0; i < m; i++) {
        int a, b; ll c;
        cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back(edge.size());
        edge.push_back({b, c});
        adj[b].push_back(edge.size());
        edge.push_back({a, c});
    }

    for (int i = 0; i < n; i++) {
        dijk(i);
    }

    for (int i = 0; i < l; i++) {
        cin >> nums[i];
        nums[i]--;
    }

    segtree::n = l;
    st.build();

    for (int i = 0; i < t; i++) {
        int p, q; cin >> p >> q;
        p--; q--;
        st.upd(p, q); 

        if (st.st[1].combo.empty()) {
            cout << "-1\n";
        } else {
            ll ans = INFLL;
            for (auto &p : st.st[1].combo) {
                ans = min(ans, p.length);
            }
            cout << ans << '\n';
        }
    }

    return 0;
}
