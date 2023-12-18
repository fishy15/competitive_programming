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

ll count_inversions(const vector<int> &nums) {
    int n = nums.size();

    int zero_after = n / 2;
    ll ans = 0;

    for (auto x : nums) {
        if (x == 0) {
            zero_after--;
        } else {
            ans += zero_after;
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    int p = 0;
    while ((1 << p) < n) p++;

    vector<vector<int>> num_splits = {nums};
    vector inv_cnts(p, array<ll, 2>{});
    for (int i = p - 1; i >= 0; i--) {
        vector<vector<int>> nxt;
        for (const auto &split : num_splits) {
            vector<int> dig_only(split.size());
            int sz = split.size();
            for (int j = 0; j < sz; j++) {
                auto x = split[j];
                dig_only[j] = ((x & (1 << i)) == 0) ? 0 : 1;
            }

            ll invs = count_inversions(dig_only);
            inv_cnts[i][0] += invs;
            inv_cnts[i][1] += (ll) (sz / 2) * (sz / 2) - invs;

            vector<int> split0, split1;
            for (auto x : split) {
                if ((x & (1 << i)) == 0) {
                    split0.push_back(x);
                } else {
                    split1.push_back(x);
                }
            }
            nxt.push_back(split0);
            nxt.push_back(split1);
        }
        num_splits = nxt;
    }

    ll zero_only = 0;
    ll best = 1;
    for (int i = 0; i < p; i++) {
        zero_only += inv_cnts[i][0];
        best += min(inv_cnts[i][0], inv_cnts[i][1]);
    }

    cout << min(zero_only, best) << '\n';

    return 0;
}
