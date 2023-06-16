// :pray: :steph:
// :pray: :bakekaga:
 
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
 
void solve () {
    int n, p, k; cin >> n >> p >> k;
    vector<int> nums;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }
    sort(nums.begin(), nums.end());
    vector<int> psum(n + 1);
    for (int i = 0; i < n; i++) {
        psum[i + 1] = psum[i] + nums[i];
    }
 
    int ans2 = 0;
    for (int i = 0; i < n; i++) {
        int p1 = p;
        int cur = 0;
        for (int j = i + k - 1; j < n; j += k) {
            if (p1 < nums[j]) {
                break;
            }
            p1 -= nums[j];
            cur += k;
        }

        int l = 0;
        int r = i;
        int ans = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (mid <= p1) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        /* cout << p1 << ' ' << ans << '\n'; */
 
        if (ans == -1) {
            ans2 = max(ans2, cur);
        } else {
            ans2 = max(ans2, cur + ans);
        }
    }
 
    if (psum[n] <= p) {
        cout << n << '\n';;
        return;
    }
 
    cout << ans2 << '\n';
}
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    int q; cin >> q;
    while (q--) {
        solve();
    }
 
    return 0;
}
