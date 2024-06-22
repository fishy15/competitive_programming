#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr ll INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++)
        cin >> nums[i];
        
    vector dp(n, vector<ll>(n, INF));
    for(int i = 0; i < n; i++)
        dp[i][i] = 0;

    vector<ll> rev(600);
    vector<ll> pmin(n);
    vector<ll> smin(n);
    vector<ll> cost(n);
    for(int i = n-1; i >= 0; i--) {
        vector<int> arr = {nums[i]};
        for(int j = i+1; j < n; j++) {
            auto it = lower_bound(all(arr), nums[j]);
            arr.insert(it, nums[j]);

            bool nodup = true;

            // compute reverse 
            for (int k = 0; k < sz(arr); k++) {
                rev[arr[k]] = k;
                if (k > 0 && arr[k] == arr[k-1]) {
                    nodup = false;
                    break;
                }
            }

            if (!nodup) break;

            // compute prefix mins
            ll curmin = INF;
            for (int k = i; k <= j; k++) {
                pmin[k] = curmin = min(curmin, rev[nums[k]]);
            }

            curmin = INF;
            for (int k = j; k >= i; k--) {
                smin[k] = curmin = min(curmin, rev[nums[k]]);
            }

            // compute costs
            for (int k = i; k < j; k++) {
                cost[k] = (j - i + 1) - max(pmin[k], smin[k+1]);
            }

            for(int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k]+dp[k+1][j]+cost[k]);
            }
        }
    }
    
    vector<ll> ans(n+1, INF);
    ans[0] = 0;
    for (int i = 0; i < n; i++) {
        vector<int> curint;
        for (int j = i; j < n; j++) {
            auto it = lower_bound(all(curint), nums[j]);
            curint.insert(it, nums[j]);
            // rest is checked by dp being INF
            if (curint[0] == 1 && curint.back() == curint.size()) {
                ans[j+1] = min(ans[j+1], ans[i] + dp[i][j]);
            }
        }
    }

    if (ans[n] == INF) {
        cout << "impossible\n";
    } else {
        cout << ans[n] << '\n';
    }
}
