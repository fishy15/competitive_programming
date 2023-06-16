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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n;

int cross(pair<int, int> &v1, pair<int, int> &v2) {
    return v1.first * v2.second - v1.second * v2.first;
}

bool cw(pair<int, int> &a, pair<int, int> &b, pair<int, int> &c) {
    pair<int, int> v1 = {b.first - a.first, b.second - a.second};
    pair<int, int> v2 = {c.first - b.first, c.second - b.second};
    return cross(v1, v2) < 0;
}

bool ccw(pair<int, int> &a, pair<int, int> &b, pair<int, int> &c) {
    pair<int, int> v1 = {b.first - a.first, b.second - a.second};
    pair<int, int> v2 = {c.first - b.first, c.second - b.second};
    return cross(v1, v2) > 0;
}

void solve() {
    vector<pair<int, int>> pts;
    set<pair<int, int>> pts2;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        pts2.insert({a, b});
    }

    for (auto p : pts2) {
        pts.push_back(p);
    }

    n = pts.size();

    if (n <= 2) {
        cout << n << '\n';
        for (auto p : pts) {
            cout << p.first << ' ' << p.second << '\n';
        }
        return;
    }

    vector<pair<int, int>> upper = {pts[0]};
    for (int i = 1; i < n; i++) {
        int sz = upper.size();
        while (sz > 1 && !cw(upper[sz - 2], upper[sz - 1], pts[i])) {
            upper.pop_back();
            sz = upper.size();
        }

        upper.push_back(pts[i]);
    }

    vector<pair<int, int>> lower = {pts[0]};
    for (int i = 1; i < n; i++) {
        int sz = lower.size();
        while (sz > 1 && !ccw(lower[sz - 2], lower[sz - 1], pts[i])) {
            lower.pop_back();
            sz = lower.size();
        }

        lower.push_back(pts[i]);
    }

    cout << upper.size() + lower.size() - 2 << '\n';
    for (int i = 0; i < lower.size(); i++) {
        cout << lower[i].first << ' ' << lower[i].second << '\n';
    }

    for (int i = upper.size() - 2; i > 0; i--) {
        cout << upper[i].first << ' ' << upper[i].second << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    while (n > 0) {
        solve();
        cin >> n;
    }

    return 0;
}
