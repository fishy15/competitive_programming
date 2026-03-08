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

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    rep(i, 1, n) {
        if (nums[i-1] < nums[i]) {
            cout << "NO\n";
            return;
        }
    }

    rep(i, 0, n) {
        if (!(n - i - 1 <= nums[i] && nums[i] <= n)) {
            cout << "NO\n";
            return;
        }
    }

    set<int> s(all(nums));
    set<int> comp;
    rep(i, 0, n) {
        if (!s.count(i)) {
            comp.insert(i);
        }
    }

    int last = n;
    cout << "YES\n";
    rep(i, 0, n) {
        if (nums[i] == last) {
            cout << *comp.rbegin() << ' ';
            comp.erase(prev(comp.end()));
        } else {
            cout << n << ' ';
        }
        last = nums[i];
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
