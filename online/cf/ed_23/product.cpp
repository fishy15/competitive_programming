// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
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

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n; cin >> n;
    map<ll, ll> nums;

    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        nums[x]++;
    }

    nums[INF] = 1;
    nums[INF + 1] = 1;

    ll ans[3];
    int pos = 0;

    for (const pair<int, int> &p : nums) {
        ans[pos] = p.second;
        pos++;
        if (pos == 3) break;
    }

    // aaa, aab, abc, abb
    if (ans[0] >= 3) {
        cout << ans[0] * (ans[0] - 1) * (ans[0] - 2) / 6 << '\n';
    } else if (ans[0] == 2) {
        cout << ans[1] << '\n';
    } else if (ans[1] == 1) {
        cout << ans[2] << '\n';
    } else {
        cout << ans[1] * (ans[1] - 1) / 2;
    }

    return 0;
}
