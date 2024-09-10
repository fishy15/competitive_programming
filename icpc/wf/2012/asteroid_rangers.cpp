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

struct Node {
    Node *p = 0, *pp = 0, *c[2];
    bool flip = 0;
    Node() { c[0] = c[1] = 0; fix(); }
    void fix() {
        if (c[0]) c[0]->p = this;
        if (c[1]) c[1]->p = this;
    }
    void pushFlip() {
        if (!flip) return;
        flip = 0; swap(c[0], c[1]);
        if (c[0]) c[0]->flip ^= 1;
        if (c[1]) c[1]->flip ^= 1;
    }
    int up() { return p ? p->c[1] == this : -1; }
    void rot(int i, int b) {
        int h = i ^ b;
        Node *x = c[i], *y = b == 2 ? x : x->c[h], *z = b ? y : x;
        if ((y->p = p)) p->c[up()] = y;
        c[i] = z->c[i ^ 1];
        if (b < 2) {
            x->c[h] = y->c[h ^ 1];
            y->c[h ^ 1] = x;
        }
        z->c[i ^ 1] = this;
        fix(); x->fix(); y->fix();
        if (p) p->fix();
        swap(pp, y->pp);
    }
    void splay() {
        for (pushFlip(); p; ) {
            if (p->p) p->p->pushFlip();
            p->pushFlip(); pushFlip();
            int c1 = up(), c2 = p->up();
            if (c2 == -1) p->rot(c1, 2);
            else p->p->rot(c2, c1 != c2);
        }
    }
    Node* first() {
        pushFlip();
        return c[0] ? c[0]->first() : (splay(), this);
    }
};

struct LinkCut {
    vector<Node> node;
    LinkCut(int N) : node(N) {}

    void link(int u, int v) {
        assert(!connected(u, v));
        makeRoot(&node[u]);
        node[u].pp = &node[v];
    }
    void cut(int u, int v) {
        Node *x = &node[u], *top = &node[v];
        makeRoot(top); x->splay();
        assert(top == (x->pp ?: x->c[0]));
        if (x->pp) x->pp = 0;
        else {
            x->c[0] = top->p = 0;
            x->fix();
        }
    }
    bool connected(int u, int v) {
        Node* nu = access(&node[u])->first();
        return nu == access(&node[v])->first();
    }
    void makeRoot(Node* u) {
        access(u);
        u->splay();
        if (u->c[0]) {
            u->c[0]->p = 0;
            u->c[0]->flip = 1;
            u->c[0]->pp = u;
            u->c[0] = 0;
            u->fix();
        }
    }
    Node* access(Node *u) {
        u->splay();
        while (Node* pp = u->pp) {
            pp->splay(); u->pp = 0;
            if (pp->c[1]) {
                pp->c[1]->p = 0; pp->c[1]->pp = pp; }
            pp->c[1] = u; pp->fix(); u = pp;
        }
        return u;
    }
};

struct line {
    int x, y, z;
    int vx, vy, vz;
    int id;

    array<ld, 3> loc_at(ld t) const {
        ld x1 = x + vx * t;
        ld y1 = y + vy * t;
        ld z1 = z + vz * t;
        return{x1, y1, z1};
    }
};

struct swap_info {
    ld time;
    int i; // first edge being swapped
    int j; // second edge being swapped
    
    bool operator<(const swap_info &sw) const {
        return time > sw.time;
    }
};

basic_string<int> poly_sq(const basic_string<int> &p) {
    auto deg = sz(p) - 1;
    basic_string<int> res;
    res.resize(2 * deg + 1);
    rep(i, 0, deg+1) {
        rep(j, 0, deg+1) {
            res[i + j] += p[i] * p[j];
        }
    }
    return res;
}

basic_string<int> poly_add(const basic_string<int> &p1, const basic_string<int> &p2) {
    basic_string<int> res;
    res.resize(max(sz(p1), sz(p2)));
    rep(i, 0, max(sz(p1), sz(p2))) {
        if (i < sz(p1)) res[i] += p1[i];
        if (i < sz(p2)) res[i] += p2[i];
    }
    return res;
}

basic_string<int> poly_sub(const basic_string<int> &p1, const basic_string<int> &p2) {
    basic_string<int> res;
    res.resize(max(sz(p1), sz(p2)));
    rep(i, 0, max(sz(p1), sz(p2))) {
        if (i < sz(p1)) res[i] += p1[i];
        if (i < sz(p2)) res[i] -= p2[i];
    }
    return res;
}

basic_string<int> edge_dist2_poly(const line &l1, const line &l2) {
    basic_string<int> poly_x = {l1.x - l2.x, l1.vx - l2.vx};
    basic_string<int> poly_y = {l1.y - l2.y, l1.vy - l2.vy};
    basic_string<int> poly_z = {l1.z - l2.z, l1.vz - l2.vz};
    return poly_add(poly_add(poly_sq(poly_x), poly_sq(poly_y)), poly_sq(poly_z));
}

basic_string<int> diff_edge_poly(const line &l1, const line &l2, const line &l3, const line &l4) {
    return poly_sub(edge_dist2_poly(l1, l2), edge_dist2_poly(l3, l4));
}

vector<ld> inters_after(basic_string<int> &poly) {
    ld a = poly[2];
    ld b = poly[1];
    ld c = poly[0];

    vector<ld> res;

    if (a == 0) {
        if (b != 0) {
            ld sol = -c / b;
            res.push_back(sol);
        }
    } else {
        auto discrim = b*b - 4 * a * c;
        if (discrim < 0) {
            return {};
        } else if (discrim < eps) {
            ld sol = -b / (2 * a);
            res.push_back(sol);
        } else {
            auto sol1 = (-b - sqrt(discrim)) / (2 * a);
            auto sol2 = (-b + sqrt(discrim)) / (2 * a);
            auto lo_sol = min(sol1, sol2);
            auto hi_sol = max(sol1, sol2);
            res.push_back(lo_sol);
            res.push_back(hi_sol);
        }
    }

    return res;
}

ld dist2(array<ld, 3> p1, array<ld, 3> p2) {
    auto dx = p1[0] - p2[0];
    auto dy = p1[1] - p2[1];
    auto dz = p1[2] - p2[2];
    return dx*dx + dy*dy + dz*dz;
}

void solve(int n) {
    vector<line> lines(n);
    rep(i, 0, n) {
        auto &[x, y, z, vx, vy, vz, id] = lines[i];
        cin >> x >> y >> z >> vx >> vy >> vz;
        id = i;
    }

    vector<pair<int, int>> edges;
    rep(i, 0, n) {
        rep(j, i+1, n) {
            edges.push_back({i, j});
        }
    }

    auto dist_at = [&](auto e, ld t) {
        auto line1 = lines[e.first];
        auto line2 = lines[e.second];
        return dist2(line1.loc_at(t), line2.loc_at(t));
    };

    auto when_swap = [&](auto e1, auto e2) {
        auto poly = 
            diff_edge_poly(
                lines[edges[e1].first],
                lines[edges[e1].second],
                lines[edges[e2].first],
                lines[edges[e2].second]
            );
        return inters_after(poly);
    };

    vector<int> edges_ord(sz(edges));
    iota(all(edges_ord), 0);
    sort(all(edges_ord), [&](auto e1, auto e2) {
        return dist_at(edges[e1], 0) < dist_at(edges[e2], 0);
    });

    LinkCut lc(n);
    vector<bool> present(sz(edges));
    for (auto i : edges_ord) {
        auto e = edges[i];
        if (!lc.connected(e.first, e.second)) {
            lc.link(e.first, e.second);
            present[i] = true;
        }
    }

    priority_queue<swap_info> pq;
    auto construct_swap = [&](int i, int j) {
        auto times = when_swap(i, j);

        if (dist_at(edges[i], -INF) > dist_at(edges[j], -INF)) {
            swap(i, j);
        }

        for (auto t : times) {
            if (t > 0) {
                pq.push({t, i, j});
            }
            swap(i, j);
        }
    };

    rep(i, 0, sz(edges)) {
        rep(j, i+1, sz(edges)) {
            construct_swap(i, j);
        }
    }

    int changes = 1;
    while (!pq.empty()) {
        auto [t, i, j] = pq.top();
        pq.pop();

        if (present[i] && !present[j]) {
            lc.cut(edges[i].first, edges[i].second);
            present[i] = false;
            if (!lc.connected(edges[j].first, edges[j].second)) {
                // it is better to swap to using j
                lc.link(edges[j].first, edges[j].second);
                present[j] = true;
                changes++;
            } else {
                // keep using i
                lc.link(edges[i].first, edges[i].second);
                present[i] = true;
            }
        }
    }

    cout << changes << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    int tc = 1;
    while (cin >> n) {
        cout << "Case " << tc << ": ";
        solve(n);
        tc++;
    }

    return 0;
}
