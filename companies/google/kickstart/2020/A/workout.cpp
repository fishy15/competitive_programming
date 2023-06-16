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

void solve() {
    int n, k; cin >> n >> k;
    int p; cin >> p;
    vector<int> diff;

    for (int i = 0; i < n - 1; i++) {
        int x; cin >> x;
        diff.push_back(x - p);
        p = x;
    }

    int l = 1;
    int r = (int)(1e9) + 1;
    int ans = -1;

    while (l <= r) {
        int m = l + (r - l) / 2;
        int cnt = 0;
        for (int i = 0; i < n - 1; i++) {
            if (diff[i] % m == 0) {
                cnt += diff[i] / m - 1;
            } else {
                cnt += diff[i] / m;
            }
        }

        if (cnt <= k) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    cout << ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
        cout << '\n';
    }

    return 0;
}
