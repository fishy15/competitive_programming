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
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : mi((int)(_v % MOD)) {}
    mi operator+(const mi &m2) const { return mi(v + m2.v); }
    mi operator-(const mi &m2) const { return mi(v - m2.v); }
    mi operator*(const mi &m2) const { return mi((ll) v * m2.v); }
    mi operator/(const mi &m2) const { return mi((ll) v * m2.inv().v); }
    mi &operator+=(const mi &m2) { return *this = *this + m2; }
    mi &operator-=(const mi &m2) { return *this = *this - m2; }
    mi &operator*=(const mi &m2) { return *this = *this * m2; }
    mi &operator/=(const mi &m2) { return *this = *this / m2; }
    mi pow(ll e) const {
        mi res = 1;
        mi n = *this;
        while (e > 0) {
            if (e & 1) res *= n;
            n *= n;
            e >>= 1;
        }
        return res;
    }
    mi inv() const {
        return pow(MOD - 2);
    }
};

mi combo(int l, int r) {
    int x = min(l, r);

    mi lc = 1;
    mi rc = 1;
    mi ans = 1;
    for (int i = 0; i <= x; i++) {
        if (i > 0) {
            lc *= (l - i + 1);
            rc *= (r - i + 1);

            lc /= i;
            rc /= i;
        }

        ans += lc * rc;
    }

    return ans;
}

void solve() {
    int n;
    cin >> n;

    deque<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int edge_left = 0;
    int edge_right = 0;
    while (!nums.empty() && nums.front() == 0) {
        nums.pop_front();
        edge_left++;
    }

    // all only zeroes
    if (nums.empty()) {
        cout << mi(2).pow(n - 1).v << '\n';
        return;
    }

    while (!nums.empty() && nums.back() == 0) {
        nums.pop_back();
        edge_right++;
    }

    mi ans = 1;
    if (edge_left > 0 || edge_right > 0) {
        ans = combo(edge_left, edge_right);
    }

    n = nums.size();

    int l = 0;
    int r = n - 1;
    ll left_sum = 0;
    ll right_sum = 0;
    while (l < n) {
        left_sum += nums[l];

        while (l < r && left_sum > right_sum) {
            right_sum += nums[r];
            r--;
        }

        /* cout << l << ' ' << r << ' ' << left_sum << ' ' << right_sum << '\n'; */

        if (l > r) break;

        if (left_sum == right_sum) {
            int zero_l = 0;
            int zero_r = 0;
            while (l + 1 < n && nums[l + 1] == 0) {
                zero_l++;
                l++;
            }

            while (r >= 0 && nums[r] == 0) {
                zero_r++;
                r--;
            }

            // all between original l and original r 
            if (l > r) {
                // go back to original
                l -= zero_l;
                r += zero_r;

                // deal with this next iteration
                if (nums[l) {
                    continue;

                ans *= mi(2).pow(r - l - 1);

                cout << "mid\n";

                break;
            } else {
                ans *= combo(zero_l, zero_r);
                cout << combo(zero_l, zero_r).v << '\n';
                /* ans *= (zero_l + 1) * (zero_r + 1) + 1; */
            }
        }
        
        l++;
    }

    cout << ans.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
