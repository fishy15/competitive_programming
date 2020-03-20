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
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200000

using namespace std;

ll n, k;
ll nums[MAXN];
ll pos[MAXN + 1];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (ll i = 0; i < n; i++) {
        cin >> nums[i];
        pos[nums[i]] = i;
    }

    vector<ll> ans;
    ll s = 0;
    for (ll i = n; i > n - k; i--) {
        s += i;
        ans.push_back(pos[i]);
    }

    sort(ans.begin(), ans.end());

    ll a = 1LL;
    for (ll i = 0; i < k - 1; i++) {
        a *= ans[i + 1] - ans[i];
        a %= MOD;
    }

    cout << s << ' ' << a << '\n';

    return 0;
}
