/*
 * Suppose we have 3 vectors (v1, v2, and v3) which all have a magnitude <= R. We can prove that one pair
 * in {v1, v2, v3, -v1, -v2, -v3} will sum to <= R as well. This is because if we plot each vector and its
 * negative, at least two of them must be in the same 60 degree sector, so the distance between them must
 * be <= R. We can then use divide and conquer to figure out two vectors that are less than R = 1e6. These
 * two can then be combined to get a vector that is <= R * sqrt(2) in distance, which fits the final 
 * contraint.
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
#define MAXN 100010

using namespace std;

struct vec {
    int x, y;
    vector<pair<int, int>> sgn;

    vec() {}
    vec(int x, int y, int idx) : x(x), y(y) {
        sgn = {{idx, 1}};
    }

    ll merge_d(const vec &v2, int mul) const {
        ll dx = x + v2.x * mul;
        ll dy = y + v2.y * mul;
        return dx * dx + dy * dy;
    }

    vec merge(const vec &v2, int mul) const {
        vec res;
        res.x = x + v2.x * mul;
        res.y = y + v2.y * mul;

        res.sgn = sgn;
        for (auto [idx, i] : v2.sgn) {
            res.sgn.push_back({idx, mul * i});
        }
        
        return res;
    }
};

int n;
vector<vec> pts;
ll small_limit = 1000000000000;
ll big_limit   = 2250000000000;
int ans[MAXN];

array<vec, 2> merge(vec a, vec b, vec c) {
    if (a.merge_d(b, 1) <= small_limit) {
        return {a.merge(b, 1), c};
    } else if (a.merge_d(b, -1) <= small_limit) {
        return {a.merge(b, -1), c};
    } if (a.merge_d(c, 1) <= small_limit) {
        return {a.merge(c, 1), b};
    } else if (a.merge_d(c, -1) <= small_limit) {
        return {a.merge(c, -1), b};
    } if (b.merge_d(c, 1) <= small_limit) {
        return {b.merge(c, 1), a};
    } else {
        return {b.merge(c, -1), a};
    } 
}

vector<vec> solve(int l, int r) {
    if (l == r) {
        return {pts[l]};
    } else {
        int m = (l + r) / 2;
        auto list = solve(l, m);
        auto rest = solve(m + 1, r);
        list.insert(list.end(), rest.begin(), rest.end());

        while (list.size() > 2) {
            auto a = list.back(); list.pop_back();
            auto b = list.back(); list.pop_back();
            auto c = list.back(); list.pop_back();
            array<vec, 2> res = merge(a, b, c);
            list.insert(list.end(), res.begin(), res.end());
        }

        return list;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        pts.emplace_back(x, y, i);
    }

    if (n == 1) {
        cout << "1\n";
        return 0;
    }

    vector<vec> ans_v = solve(0, n - 1);
    vec res;
    if (ans_v[0].merge_d(ans_v[1], 1) <= big_limit) {
        res = ans_v[0].merge(ans_v[1], 1);
    } else {
        res = ans_v[0].merge(ans_v[1], -1);
    }

    for (auto [idx, i] : res.sgn) {
        ans[idx] = i;
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';

    return 0;
}
