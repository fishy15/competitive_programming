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

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<typename T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T _x=0, T _y=0) : x(_x), y(_y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y) == tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x,y+p.y); }
    P operator-(P p) const { return P(x-p.x,y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    bool half() const { return y < 0 || (y == 0 && x < 0); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    P perp() const { return P(-y, x); }
};

using P = Point<ld>;

bool circleInter(P a, P b, double r1, double r2, pair<P, P>* out) {
    if (a == b) { assert(r1 != r2); return false; }
    P vec = b - a;
    double d2 = vec.dist2(), sum = r1+r2, dif = r1-r2,
           p = (d2 + r1*r1 - r2*r2)/(d2*2), h2 = r1*r1 - p*p*d2;
    if (sum*sum < d2 || dif*dif > d2) return false;
    P mid = a + vec*p, per = vec.perp() * sqrt(fmax(0, h2) / d2);
    *out = {mid - per, mid + per};
    return true;
}

struct DSU {
    vector<int> dsu;
    vector<int> size;
    DSU(int n) : dsu(n), size(n, 1) {
        iota(all(dsu), 0);
    }
    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }
    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (size[x] < size[y]) swap(x, y);
            dsu[y] = x;
            size[x] += size[y];
        }
    }
};

bool intersects(const pair<P, ld> &c1, const pair<P, ld> &c2) {
    auto d = (c1.first - c2.first).dist();
    return d <= (c1.second + c2.second);
}

bool contained(const pair<P, ld> &small, const pair<P, ld> &big) {
    auto d = (big.first - small.first).dist() + small.second;
    return d <= big.second;
}

bool cmp(P a, P b, P p) {
    a = a - p, b = b - p;
    return a.half() == b.half() ? a.cross(b) > 0 : a.half() < b.half();
}

struct event {
    P p;
    int typ;
    int other;
    int other_typ;
};

struct intersection {
    int c1, c2;
    intersection(int _c1, int _c2, int typ) : c1(_c1), c2(_c2) {
        if (typ == 1) {
            swap(c1, c2);
        }
    }
    bool operator<(const intersection &other) const {
        return tie(c1, c2) < tie(other.c1, other.c2);
    }
    bool operator==(const intersection &other) const {
        return tie(c1, c2) == tie(other.c1, other.c2);
    }
};

struct edge {
    intersection i1, i2;
};

// vec of {idx of other circle, first or second} 
vector<edge> get_segments(pair<P, ld> &circ, const vector<pair<P, ld>> &all_circs, int cur_idx) {
    vector<event> events;
    int cur = 0;
    rep(i, 0, sz(all_circs)) {
        auto &c = all_circs[i];
        if (c != circ) {
            if (contained(circ, c)) {
                return {};
            } else {
                pair<P, P> pts;
                if (circleInter(circ.first, c.first, circ.second, c.second, &pts)) {
                    events.push_back({pts.first, +1, i, 0});
                    events.push_back({pts.second, -1, i, 1});
                    if (!cmp(pts.first, pts.second, circ.first)) {
                        // if first is later, then add 1 to init
                        cur++;
                    }
                }
            }
        }
    }

    if (events.empty()) {
        return {};
    }

    sort(all(events), 
         [&](const auto a, const auto b) { return cmp(a.p, b.p, circ.first);
    });

    auto last = events.back();
    vector<edge> res;
    for (auto e : events) {
        if (cur == 0) {
            auto last_i = intersection{cur_idx, last.other, last.other_typ};
            auto cur_i = intersection{cur_idx, e.other, e.other_typ};
            res.push_back(edge{last_i, cur_i});
        }
        cur += e.typ;
        last = e;
    }

    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<P, ld>> circs(n);
    rep(i, 0, n) {
        int x, y, r;
        cin >> x >> y >> r;
        circs[i] = {P{(ld) x, (ld) y}, r};
    }

    DSU circ_comp(n);
    rep(i, 0, n) {
        rep(j, i+1, n) {
            if (intersects(circs[i], circs[j])) {
                circ_comp.join(i, j);
            }
        }
    }

    int num_cc = 0;
    rep(i, 0, n) {
        if (i == circ_comp.find(i)) {
            num_cc++;
        }
    }

    vector<intersection> inters;
    vector<edge> edges;
    rep(i, 0, n) {
        for (auto x : get_segments(circs[i], circs, i)) {
            inters.push_back(x.i1);
            inters.push_back(x.i2);
            edges.push_back(x);
        }
    }

    sort(all(inters));
    inters.erase(unique(all(inters)), end(inters));

    DSU edge_dsu(sz(inters));
    for (auto e : edges) {
        auto idx1 = lower_bound(all(inters), e.i1) - begin(inters);
        auto idx2 = lower_bound(all(inters), e.i2) - begin(inters);
        edge_dsu.join(idx1, idx2);
    }

    int num_seg_cc = 0;
    rep(i, 0, sz(inters)) {
        if (i == edge_dsu.find(i)) {
            num_seg_cc++;
        }
    }

    if (num_cc < num_seg_cc) {
        cout << "1\n";
    } else {
        cout << "0\n";
    }

    return 0;
}
