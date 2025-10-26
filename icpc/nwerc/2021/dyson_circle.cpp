#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T _x=0, T _y=0) : x(_x), y(_y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y) == tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
};

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

    vector<P> around;
    around.reserve(4 * n);
    ll sum_xy, diff_xy;
    bool on_line = (n > 1);
    rep(i, 0, n) {
        ll x, y;
        cin >> x >> y;
        around.push_back(P(x-1, y));
        around.push_back(P(x+1, y));
        around.push_back(P(x, y+1));
        around.push_back(P(x, y-1));
        if (i == 0) {
            sum_xy = x + y;
            diff_xy = x - y;
        } else if (sum_xy != x + y && diff_xy != x - y) {
            on_line = false;
        }
    }

    auto chull = convexHull(around);
    ll ans = 0;
    rep(i, 0, sz(chull)) {
        auto cur = chull[i];
        auto nxt = chull[(i + 1) % sz(chull)];
        auto diff = cur - nxt;
        auto needed = max(abs(diff.x), abs(diff.y)) + 1;
        ans += needed - 2;
    }

    ans += sz(chull);
    if (on_line) {
        ans++;
    }

    cout << ans << '\n';
    return 0;
}

