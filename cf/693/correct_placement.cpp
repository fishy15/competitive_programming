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

struct mmap {
    map<int, pair<int, int>> m;
    void insert(pair<int, pair<int, int>> x) {
        if (m.count(x.first) && m[x.first] < x.second) return;
        m[x.first] = x.second;
        auto it = m.find(x.first);
        while (next(it) != m.end() && it->second <= next(it)->second) {
            m.erase(next(it));
        }
    }
    pair<int, int> qry(int x) {
        auto it = m.lower_bound(x);
        if (it == m.begin()) return {INF, -1};
        return prev(it)->second;
    }
};

void solve() {
    int n; cin >> n;
    vector<array<int, 3>> nums;
    vector<int> ans(n, -2);

    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        nums.push_back({x, y, i});
    }

    mmap norm;

    for (int i = 0; i < n; i++) {
        auto min_norm = norm.qry(nums[i][0]);
        auto min_rot = norm.qry(nums[i][1]);

        if (min_norm.first < nums[i][1]) {
            ans[nums[i][2]] = min_norm.second;
        }

        if (min_rot.first < nums[i][0]) {
            ans[nums[i][2]] = min_rot.second;
        }
        norm.insert({nums[i][0], {nums[i][1], nums[i][2]}});
    }

    norm.m.clear();

    for (int i = n - 1; i >= 0; i--) {
        auto min_norm = norm.qry(nums[i][0]);
        auto min_rot = norm.qry(nums[i][1]);

        if (min_norm.first < nums[i][1]) {
            ans[nums[i][2]] = min_norm.second;
        }

        if (min_rot.first < nums[i][0]) {
            ans[nums[i][2]] = min_rot.second;
        }
        norm.insert({nums[i][0], {nums[i][1], nums[i][2]}});
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
