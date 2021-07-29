// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
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

void solve() {
    int n; cin >> n;
    vector<int> nums;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    map<int, int> lower;
    map<int, int> upper;
    for (int i = 0; i < n; i++) {
        if (lower.count(nums[i])) {
            upper[nums[i]] = i;
        } else {
            lower[nums[i]] = i;
            upper[nums[i]] = i;
        }
    }

    vector<pair<int, int>> bound2;

    for (auto x : lower) {
        //cout << "1 " << x.first << ' ' << x.second << '\n';
        bound2.push_back({x.second, 0});
    }

    int pos = 0;
    for (auto x : upper) {
        bound2[pos].second = x.second;
        pos++;
    }

    int l = 0;
    int r = 1;
    int ans = INF;

    /* for (pair<int, int> p: bound2) { */
    /*     cout << p.first << ' ' << p.second << "qqqq\n"; */
    /* } */

    while (l < pos) {
        //cout << '\t' << l << ' ' << r << '\n';
        while (r < pos && bound2[r].first > bound2[r - 1].second) {
            r++;
        }

        ans = min(pos - (r - l), ans);
        //cout << l << ' ' << r << '\n';
        l = r;
        r++;
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int q; cin >> q;
    while (q--) {
        solve();
    }

    return 0;
}
