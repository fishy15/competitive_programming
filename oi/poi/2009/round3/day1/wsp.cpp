/*
 * If we can go from A to B and A to C (where A < B, C), then it is better to go A to C. Also, if we can go
 * from A to B and C to D (where A < B < C < D), then it is better to take A to D. Using this, we can 
 * generate O(n) lines that could potentially be taken, and we want to try to find the lower convex 
 * hull of these lines. We can iterate over the lines in clockwise order and maintain the convex hull
 * of intersection points. Once we have the convex hull, we can add the distances between consecutive
 * nodes.
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
#define ld double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100010

using namespace std;

struct point {
    ld x, y;
    point operator+(const point &p2) const {
        return {x + p2.x, y + p2.y};
    }
    point operator-(const point &p2) const {
        return {x - p2.x, y - p2.y};
    }
    point operator*(ld r) const {
        return {x * r, y * r};
    }
};

ld cross(const point &p1, const point &p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

bool ccw(const point &a, const point &b, const point &c) {
    return cross(b - a, c - b) >= 0;
}

point isect(const point &a, const point &b, const point &c, const point &d) {
    point d1 = b - a;
    point d2 = d - c;
    return a + d1 * (cross(c - a, d2) / cross(d1, d2));
}

int n, m;
point pts[MAXN];
vector<int> bad[MAXN];
point chull[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y;
    }

    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        bad[x].push_back(y);
    }

    int p = 0;
    int sz = 0;
    for (int i = 0; i < n; i++) {
        p = max(i, p);
        sort(bad[i].begin(), bad[i].end(), greater<int>());
        bad[i].push_back(0);
        int pp = n;
        for (int j : bad[i]) {
            if (j + 1 != pp) {
                j = pp - 1;
                if (j <= p) break;
                p = j;
                if (!sz) {
                    chull[0] = pts[i];
                    chull[1] = pts[j];
                    sz += 2;
                } else {
                    if (ccw(pts[i], pts[j], chull[sz - 1])) {
                        while (sz - 1 && ccw(pts[i], pts[j], chull[sz - 1])) sz--;
                        point x = isect(chull[sz - 1], chull[sz], pts[i], pts[j]);
                        chull[sz] = x;
                        sz++;
                    }
                    chull[sz] = pts[j];
                    sz++;
                }
                break;
            }
            pp = j;
        }
        bad[i] = {};
    }

    ld ans = 0;
    for (int i = 0; i < sz - 1; i++) {
        ans += hypot(chull[i].x - chull[i + 1].x, chull[i].y - chull[i + 1].y);
    }

    cout << fixed << setprecision(9) << ans << '\n';

    return 0;
}
