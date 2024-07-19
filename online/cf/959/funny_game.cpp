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

    vector<pair<int, int>> ans(n);
    vector<bool> present(n, true);
    for (int i = n-1; i >= 1; i--) {
        vector<vector<int>> slots(i);
        rep(j, 0, n) {
            if (present[j]) {
                slots[nums[j] % i].push_back(j);
            }
        }

        rep(j, 0, i) {
            if (sz(slots[j]) >= 2) {
                auto x = slots[j][0];
                auto y = slots[j][1];
                ans[i - 1] = {x, y};
                present[y] = false;
                break;
            }
        }
    }

    cout << "YES\n";
    rep(i, 0, n-1) {
        cout << ans[i].first + 1 << ' ' << ans[i].second + 1 << '\n';
    }
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
