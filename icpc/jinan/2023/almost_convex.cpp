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

#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define sz(x) (int) (x).size()
#define all(x) (x).begin(), (x).end()

// change if necessary
#define MAXN 1000000

using namespace std;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    int id;
    explicit Point(T x=0, T y=0, int id=0) : x(x), y(y), id(id) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y) == tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    double angle() const { return atan2(y, x); }
};

using P = Point<ll>;
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

    vector<P> pts;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        pts.emplace_back(x, y, i);
    }

    auto chull = convexHull(pts);

    vector<bool> in_chull(sz(pts));
    for (auto p : chull) {
        in_chull[p.id] = true;
    }

    int ans = 1;
    vector<bool> valid(sz(chull), true);

    for (auto p : pts) {
        if (!in_chull[p.id]) {
            auto other_pts = pts;
            auto it = find(all(other_pts), p);
            other_pts.erase(it);

            // if we are an internal point
            sort(other_pts.begin(), other_pts.end(), [p](auto pt1, auto pt2) {
                auto c = p.cross(pt1, pt2);
                if (c < 0) return true;
                if (c > 0) return false;
 
                auto d1 = p.dot(pt1);
                auto d2 = p.dot(pt2);
                return d1 < d2;
            });

            int chull_idx = 0;
            fill(all(valid), true);
            for (auto op : other_pts) {
                if (!(op == p)) {
                    if (in_chull[op.id]) {
                        chull_idx++;
                        if (chull_idx == sz(chull)) {
                            chull_idx = 0;
                        }
                    } else {
                        valid[chull_idx] = false;
                    }
                }
            }

            ans += count(all(valid), true);
        }
    }

    cout << ans << '\n';


    return 0;
}

