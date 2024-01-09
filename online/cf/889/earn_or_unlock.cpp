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
#include <bitset>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    bitset<2 * MAXN> reachable;
    reachable[0] = true;

    bitset<2 * MAXN> mask;
    mask = ~mask; // initially set to all 1s

    for (int i = 0; i < n; i++) {
        reachable |= (reachable & mask) << nums[i];
        mask.reset(i);
    }

    vector<ll> psum(n);
    for (int i = 0; i < n; i++) {
        if (i > 0) psum[i] += psum[i - 1];
        psum[i] += nums[i];
    }

    ll ans = 0;
    for (int i = 0; i < 2 * n; i++) {
        auto c = psum[min(i, n - 1)];
        if (reachable[i]) {
            ans = max(ans, c - i);
        }
    }

    cout << ans << '\n';

    return 0;
}
