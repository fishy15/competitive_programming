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
#define MAXN 300010

using namespace std;

ll n, k;
int nums[MAXN];

int count_leq(ll x) {
    return upper_bound(nums, nums + n, x) - nums;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int mm = *max_element(nums, nums + n);
    ll to_same = 0;
    for (int i = 0; i < n; i++) {
        to_same += mm - nums[i];
    }

    if (to_same <= k) {
        ll tot = k;
        for (int i = 0; i < n; i++) {
            tot += nums[i];
        }
        cout << tot / n << '\n';
    } else {
        sort(nums, nums + n);

        ll sum = 0; 
        for (int i = 0; i < n; i++) {
            sum += nums[i];
        }

        for (int i = mm; i >= 1; i--) {
            ll tot_needed = 0;
            int prev = 0;
            for (ll j = i; j <= 2 * mm; j += i) {
                int leq = count_leq(j);
                tot_needed += j * (leq - prev);
                prev = leq;
            }

            if (tot_needed - sum <= k) {
                cout << i << '\n';
                return 0;
            }
        }
    }

    return 0;
}
