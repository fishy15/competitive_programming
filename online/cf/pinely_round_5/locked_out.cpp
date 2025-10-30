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
    vector<set<int>> locs(n);
    rep(i, 0, n) {
        cin >> nums[i];
        nums[i]--;
        locs[nums[i]].insert(i);
    }

    int ans = 0;
    rep(v, 0, n) {
        vector<int> lcs(all(locs[v]));
        reverse(all(lcs));
        for (auto i : lcs) {
            if (v < n-1) {
                auto &nxt_locs = locs[v+1];
                if (!nxt_locs.empty()) {
                    auto nxt = *nxt_locs.rbegin();
                    if (i < nxt) {
                        nxt_locs.erase(nxt);
                        ans++;
                    }
                }
            }
        }
    }

    cout << ans << '\n';
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
