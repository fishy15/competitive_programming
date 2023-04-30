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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    while (q--) {
        ll k;
        cin >> k;

        int r = 0;

        ll cur_sum = 0;
        pair<int, int> ans = {0, INF};

        while (r < n && cur_sum < k) {
            cur_sum += nums[r];
            r++;
        }

        if (cur_sum == k) {
            ans.first = 0;
            ans.second = r;
        }

        for (int l = 1; l < n; l++) {
            cur_sum -= nums[l - 1];
            while (r < n && cur_sum < k) {
                cur_sum += nums[r];
                r++;
            }

            if (cur_sum == k && r - l < ans.second - ans.first) {
                ans = {l, r};
            }
        }

        cout << ans.first << ' ' << ans.second - 1 << '\n';
    }

    return 0;
}
