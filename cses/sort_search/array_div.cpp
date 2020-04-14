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
#define MAXN 200000

using namespace std;

int n, k;
ll nums[MAXN];

bool check(ll s) {
    int cnt = 0;
    ll cur = 0;

    for (int i = 0; i < n; i++) {
        if (cur + nums[i] > s) {
            cnt++;
            cur = 0;
        }
        cur += nums[i];
    }
    
    cnt++;
    return cnt <= k;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    ll m = 1;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        m = max(nums[i], m);
    }

    ll l = m;
    ll r = 1LL * MAXN * 1000000000;
    ll ans = -1;

    for (int i = 1; i <= 10; i++) { 
        check(i);
    }

    while (l <= r) {
        ll m = l + (r - l) / 2;
        if (check(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    cout << ans << '\n';

    return 0;
}
