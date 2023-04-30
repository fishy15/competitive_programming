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
#define MAXN 500010

using namespace std;

int n;
ll nums[MAXN];
pair<int, ll> dp[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> nums[i];
    }

    int cur = 0;
    ll sum = 0;
    
    for (int i = 1; i <= n; i++) {
        sum += nums[i];
        while (cur + 1 < i && dp[cur + 1].second <= sum - nums[cur + 1]) {
            cout << cur << ' ' << i << ' ' << sum << ' ' << dp[cur].second << '\n';
            sum -= nums[cur + 1];
            cur++;
        }
        cout << cur << ' ' << i << ' ' << sum << ' ' << dp[cur].second << '\n';
        dp[i] = {dp[cur].first + 1, sum};
    }

    cout << dp[n].first << '\n';

    return 0;
}
