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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

constexpr int LIMIT = 50;

vector<pair<int, int>> combine(const vector<pair<int, int>> &left, const vector<pair<int, int>> &right) {
    vector<pair<int, int>> res(sz(left) + sz(right));
    merge(all(left), all(right), begin(res));
    return res;
}

struct group {
    bool big;
    vector<pair<int, int>> trees;

    static group combine(const group &group1, const group &group2) {
        if (group1.big || group2.big || sz(group1.trees) + sz(group2.trees) > LIMIT) {
            return group{true, {}};
        } else {
            vector<pair<int, int>> res(sz(group1.trees) + sz(group2.trees));
            merge(all(group1.trees), all(group2.trees), begin(res));
            return group{false, res};
        }
    }
};

group retrieve(const vector<pair<int, int>> &trees, int y1, int y2) {
    auto it1 = lower_bound(all(trees), pair{y1, 0});
    auto it2 = upper_bound(all(trees), pair{y2+1, 0});
    if (it2 - it1 > LIMIT) {
        return group{true, {}};
    } else {
        vector<pair<int, int>> subsection(it1, it2);
        return group{false, subsection};
    }
}

struct segtree {
    int n;
    vector<vector<pair<int, int>>> st;
    segtree(const vector<vector<pair<int, int>>> &trees) : n(sz(trees)), st(2 * n) {
        copy(all(trees), begin(st) + n);
        for (int i = n - 1; i > 0; i--) {
            st[i] = combine(st[2*i], st[2*i+1]);
        }
    }
    group qry(int l, int r, int y1, int y2) {
        l += n; r += n;
        group res{false, {}};
        while (l <= r) {
            if (l % 2 == 1) res = group::combine(res, retrieve(st[l++], y1, y2));
            if (r % 2 == 0) res = group::combine(res, retrieve(st[r--], y1, y2));
            l /= 2;
            r /= 2;
        }
        return res;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<array<int, 3>> trees(n);
    vector<int> xs;
    vector<int> ys;
    for (auto &[x, y, h] : trees) {
        cin >> x >> y >> h;
        xs.push_back(x);
        ys.push_back(y);
    }

    vector<array<int, 4>> qry(q);
    for (auto &[x1, y1, x2, y2] : qry) {
        cin >> x1 >> y1 >> x2 >> y2;
        xs.push_back(x1);
        xs.push_back(x2);
        ys.push_back(y1);
        ys.push_back(y2);
    }

    sort(all(xs));
    xs.erase(unique(all(xs)), end(xs));
    sort(all(ys));
    ys.erase(unique(all(ys)), end(ys));

    auto comp_x = [&](int x) { return lower_bound(all(xs), x) - begin(xs); };
    auto comp_y = [&](int y) { return lower_bound(all(ys), y) - begin(ys); };

    for (auto &[x, y, h] : trees) {
        x = comp_x(x);
        y = comp_y(y);
    }

    for (auto &[x1, y1, x2, y2] : qry) {
        x1 = comp_x(x1);
        x2 = comp_x(x2);
        y1 = comp_y(y1);
        y2 = comp_y(y2);
    }

    vector<vector<pair<int, int>>> tree_groups(sz(xs));
    for (auto [x, y, h] : trees) {
        tree_groups[x].push_back({y, h});
    }
    for (auto &v : tree_groups) {
        sort(all(v));
    }

    segtree st(tree_groups);

    for (auto [x1, y1, x2, y2] : qry) {
        auto trees = st.qry(x1, x2, y1, y2);
        if (trees.big) {
            cout << "1\n";
        } else {
            vector<int> heights;
            for (auto [y, h] : trees.trees) {
                heights.push_back(h);
            }

            bool works = false;
            sort(all(heights));
            rep(i, 0, sz(heights) - 2) {
                if (heights[i] + heights[i+1] > heights[i+2]) {
                    works = true;
                    break;
                }
            }

            if (works) {
                cout << "1\n";
            } else {
                cout << "0\n";
            }
        }
    }

    return 0;
}
