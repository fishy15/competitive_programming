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

constexpr ll INF = 0x3f3f3f3f * 1LL;
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

#define sz(x) (int) (x).size()
#define all(x) (x).begin(), (x).end()

template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y) == tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
};

typedef Point<ll> pt;

void reorder_polygon(vector<pt> &P) {
    int pos = 0;
    for (int i = 1; i < sz(P); i++) {
        if (P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x))
            pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
}

vector<pt> minkowski(vector<pt> P, vector<pt> Q) {
    reorder_polygon(P);
    reorder_polygon(Q);

    P.push_back(P[0]);
    P.push_back(P[1]);
    Q.push_back(Q[0]);
    Q.push_back(Q[1]);

    vector<pt> result;
    int i = 0, j = 0;
    while (i < sz(P) - 2 || j < sz(Q) - 2) {
        result.push_back(P[i] + Q[j]);
        auto cross = (P[i + 1] - P[i]).cross(Q[j + 1] - Q[j]);
        if (cross >= 0 && i < sz(P) - 2) ++i;
        if (cross <= 0 && j < sz(Q) - 2) ++j;
    }
    return result;
}

typedef Point<ll> P;

vector<P> convexHull(vector<P> pts) {
    if (sz(pts) <= 1) return pts;
    sort(all(pts));
    vector<P> h(sz(pts)+1);
    int s = 0, t = 0;
    for (int it = 2; it--; s = --t, reverse(all(pts)))
        for (P p : pts) {
            while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
            h[t++] = p;
        }
    return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    // represents dual of the lines
    vector<P> a(n+1), b(n+1), c(n+1);
    int max_a = 0;
    int max_b = 0;
    int max_c = 0;
    for (int i = 0; i <= n; i++) {
        int x;
        cin >> x;
        a[i] = P(i, x);
        max_a = max(max_a, x);
    }
    for (int i = 0; i <= n; i++) {
        int x;
        cin >> x;
        b[i] = P(i, x);
        max_b = max(max_b, x);
    }
    for (int i = 0; i <= n; i++) {
        int x;
        cin >> x;
        c[i] = P(i, x);
        max_c = max(max_c, x);
    }

    a.push_back(P(0, -INF));
    a.push_back(P(n, -INF));
    b.push_back(P(0, -INF));
    b.push_back(P(n, -INF));
    c.push_back(P(0, -INF));
    c.push_back(P(n, -INF));

    auto ahull = convexHull(a);
    auto bhull = convexHull(b);
    auto chull = convexHull(c);

    auto tot = minkowski(minkowski(ahull, bhull), chull);

    set<int> s;
    for (int i = 0; i <= 3*n; i++) s.insert(i);

    for (auto p : tot) {
        if (p.x >= 0 && p.y >= 0) {
            s.erase(p.x);
        }
    }

    cout << s.size() << '\n';
    for (auto x : s) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}
