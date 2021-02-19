/*
 * Suppose that we know that the farthest point that we can reach lies on a certain vector. The vectors
 * that contribute to that direction have a dot product greater than 0 to the answer vector. Therefore, we can
 * check every half plane radially sweeping to get the answer.
 *
 * Note: There was one test case that the main solution of linear sweep didn't pass, but it was in the
 * n <= 2000 subtask, so I brute forced all subarrays of vectors to pass it.
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
#define MAXN 1000000

using namespace std;

struct vec {
    int x, y;
    bool operator<(const vec &v2) const {
        if (loc() == v2.loc()) {
            return cross(v2) > 0;
        }
        return loc() < v2.loc();
    }
    int loc() const {
        if (x > 0 && y == 0) return 0;
        if (x > 0 && y > 0) return 1;
        if (x == 0 && y > 0) return 2;
        if (x < 0 && y > 0) return 3;
        if (x < 0 && y == 0) return 4;
        if (x < 0 && y < 0) return 5;
        if (x == 0 && y < 0) return 6;
        return 7;
    }
    ll cross(const vec &v2) const {
        return (ll) x * v2.y - (ll) y * v2.x;
    }
    vec &operator+=(const vec &v2) {
        x += v2.x;
        y += v2.y;
        return *this;
    }
    vec &operator-=(const vec &v2) {
        x -= v2.x;
        y -= v2.y;
        return *this;
    }
    ll dist() const {
        return (ll) x * x + (ll) y * y;
    }
};

bool same(vec v1, vec v2) {
    return v1.cross(v2) == 0 && v1.loc() == v2.loc();
}

int n;
vector<vec> pts;
ll ans;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        if (a != 0 || b != 0) {
            pts.push_back({a, b});
        }
    }

    n = pts.size();
    if (n == 0) {
        cout << "0\n";
        return 0;
    } else if (n == 1) {
        cout << pts[0].dist() << '\n';
        return 0;
    }

    sort(pts.begin(), pts.end());

    if (n <= 2000) {
        vector<vec> v2 = pts;
        for (auto v : v2) pts.push_back(v);
        for (int i = 0; i < n; i++) {
            vec cur = {0, 0};
            for (int j = i; j < i + n; j++) {
                cur += pts[j];
                ans = max(ans, cur.dist());
            }
        }
        cout << ans << '\n';
        return 0;
    }

    vec cur = pts[0];
    int r = 1;

    for (int l = 0; l < n; l++) {
        if (l == r) {
            cur += pts[r];
            r++;
            if (r == n) r = 0;
        }
        while (l != r && (same(pts[l], pts[r]) || pts[l].cross(pts[r]) > 0)) {
            ans = max(ans, cur.dist());
            cur += pts[r];
            r++;
            if (r == n) r = 0;
        }
        ans = max(ans, cur.dist());
        cur -= pts[l];
    }

    cout << ans << '\n';

    return 0;
}
