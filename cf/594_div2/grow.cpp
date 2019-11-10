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
    vector<int> nums;

    ll sum = 0;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
        sum += x;
    }

    sort(nums.begin(), nums.end());
    
    ll cur = 0;

    for (int i = 0; i < n / 2; i++) {
        cur += nums[i];
    }

    ll ans = cur * cur + (sum - cur) * (sum - cur);

    cout << ans << '\n';

    return 0;
}
