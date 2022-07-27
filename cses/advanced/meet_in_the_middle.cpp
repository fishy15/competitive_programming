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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

template<typename Iterator>
vector<pair<ll, int>> get_combos(Iterator start, Iterator end) {
    int n = end - start;

    vector<ll> combos(1 << n);

    // setting the powers of 2
    for (int i = 0; i < n; i++) {
        combos[1 << i] = *(start + i);
    }

    for (int m = 1; m < (1 << n); m++) {
        // is not a power of two
        if (combos[m] == 0) {
            int low_bit = m & -m;
            combos[m] = combos[m ^ low_bit] + combos[low_bit];
        }
    }

    sort(combos.begin(), combos.end());
    vector<pair<ll, int>> counts;

    for (auto x : combos) {
        if (counts.empty() || counts.back().first != x) {
            counts.push_back({x, 1});
        } else {
            counts.back().second++;
        }
    }

    return counts;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, x;
    cin >> n >> x;

    vector<ll> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int m = n / 2;

    auto mid = nums.begin() + m;
    auto first = get_combos(nums.begin(), mid);
    auto second = get_combos(mid, nums.end());

    reverse(second.begin(), second.end());
    
    auto it = second.begin();
    ll ans = 0;
    for (auto [val, cnt] : first) {
        while (it != second.end() && it->first + val > x) it++;

        if (it != second.end() && it->first + val == x) {
            ans += (ll) cnt * it->second; 
        }
    }

    cout << ans << '\n';

    return 0;
}
