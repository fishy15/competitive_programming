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
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct point {
    ll x, y;
    point operator+(const point &p2) const {
        return {x + p2.x, y + p2.y};
    }
    point operator-(const point &p2) const {
        return {x - p2.x, y - p2.y};
    }
    bool operator==(const point &p2) const {
        return x == p2.x && y == p2.y;
    }
    bool operator<(const point &p2) const {
        if (x == p2.x) return y < p2.y;
        return x < p2.x;
    }
};

ld cross(const point &p1, const point &p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

bool collinear(const point &a, const point &b, const point &c) {
    return cross(b - a, c - b) == 0;
}

bool ccw(const point &a, const point &b, const point &c) {
    return cross(b - a, c - b) > 0;
}

bool cw(const point &a, const point &b, const point &c) {
    return cross(b - a, c - b) < 0;
}

bool valid(point a, point b, point c, point x) {
    if (collinear(a, b, c) || collinear(a, b, x) || collinear(a, c, x) || collinear(b, c, x)) {
        return false;
    }

    if (cw(a, x, b) && cw(b, x, c) && cw(c, x, a)) {
        return true;
    }

    if (ccw(a, x, b) && ccw(b, x, c) && ccw(c, x, a)) {
        return true;
    }

    return false;
}

ld get_p(point a, point b, point c) {
    point s1 = a - b;
    point s2 = b - c;
    point s3 = c - a;
    return hypot(s1.x, s1.y) + hypot(s2.x, s2.y) + hypot(s3.x, s3.y);
}

ld get_p(point a, point b, point c, point d) {
    point s1 = a - b;
    point s2 = b - c;
    point s3 = c - d;
    point s4 = d - a;
    return hypot(s1.x, s1.y) + hypot(s2.x, s2.y) + hypot(s3.x, s3.y) + hypot(s4.x, s4.y);
}

void solve() {
    int n; cin >> n;
    vector<point> white(n);
    point blue;

    for (int i = 0; i < n; i++) {
        cin >> white[i].x >> white[i].y;
    }

    cin >> blue.x >> blue.y;

    ld ans = INFLL;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (valid(white[i], white[j], white[k], blue)) {
                    ans = min(ans, get_p(white[i], white[j], white[k]));
                }
            }
        }
    }

    map<point, point> front;
    map<point, point> back;
    
    for (int i = 0; i < n; i++) {
        point v = blue - white[i];
        point orig = v;

        ll g = gcd(abs(v.x), abs(v.y));
        v.x /= g;
        v.y /= g;

        if (v.y > 0 || (v.y == 0 && v.x > 0)) {
            if (!front.count(v)) {
                front[v] = orig;
            } else {
                point cur = front[v];
                if (hypot(orig.x, orig.y) < hypot(cur.x, cur.y)) {
                    front[v] = orig;
                }
            }
        } else {
            v.x *= -1;
            v.y *= -1;
            if (!back.count(v)) {
                back[v] = orig;
            } else {
                point cur = back[v];
                if (hypot(orig.x, orig.y) < hypot(cur.x, cur.y)) {
                    back[v] = orig;
                }
            }
        }
    }

    for (auto [a, v] : front) {
        if (!back.count(a)) continue;
        for (auto [a2, v2] : front) {
            if (!back.count(a2)) continue;
            if (a == a2) continue;
            auto b = back[a];
            auto b2 = back[a2];
            ans = min(ans, get_p(v, v2, b, b2));
        }
    }

    if (fabs(ans - INFLL) > eps) {
        cout << ans << '\n';
        return;
    }

    cout << "IMPOSSIBLE\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;

    cout << fixed << setprecision(12);
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
