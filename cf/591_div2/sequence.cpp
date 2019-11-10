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

    set<int> cur;
    int l = 0;
    for (int i = 0; i < n; i++) {
        auto pos = upper_bound(cur.begin(), cur.end(), nums[i]);
        if (pos != cur.end()) {
            l = max(nums[i], l);
        }
        cur.insert(nums[i]);
    }


    cur = {};
    int r = INF;
    for (int i = n - 1; i >= 0; i--) {
        auto pos = upper_bound(cur.begin(), cur.end(), nums[i]);
        if (pos != cur.end()) {
            r = min(nums[i], r);
        }
        cur.insert(nums[i]);
    }

    cout << l << ' ' << r << '\n';

    set<int> below;
    set<int> above;

    for (int i = 0; i < n; i++) {
        if (nums[i] <= l) {
            below.insert(i);
        }

        if (nums[i] >= r) {
            above.insert(i);
        }
    }

    cout << min((int)(below.size() + above.size()), n) << '\n';
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int q; cin >> q;
    
    while (q--) {
        solve();
    }

    return 0;
}
