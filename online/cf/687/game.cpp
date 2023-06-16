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

int n, k;
int nums[MAXN];
int cnt[MAXN];
ll cur;
ll ans;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    k++;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    sort(nums, nums + n);

    for (int i = 0; i < n; i++) {
        cnt[i] = i / k;
        ans += (ll) cnt[i] * nums[i];
    }

    for (int i = n - 1; i >= 0; i--) {
        cur += nums[i];
        if (cur < 0) break;
        if (i % k == 0) continue;
        ans += cur;
    }

    cout << ans << '\n';


    return 0;
}
