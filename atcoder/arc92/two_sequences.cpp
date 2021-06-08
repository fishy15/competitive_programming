/*
 * We can solve for each bit independently. For bit k (in location 2^k), the bits >k don't matter, so we can
 * mod by 2^(k + 1). Then, we need to count how many times bit k is set in the addition. For each value of
 * a_i, we can binary search for the values where b_j has that bit set. Specifically, this is when 
 * 2^k <= sum < 2 * 2^k or 3 * 2^k <= sum < 4 * 2^k. If the total count is odd, we can add that bit to the 
 * answer.
 */

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
#define MAXN 1000000

using namespace std;

int solve(int n, int k, vector<int> &a, vector<int> &b) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        auto lb = [&](int x) { return lower_bound(b.begin(), b.end(), x); };
        int t = 1 << k;
        cnt += lb(2 * t - a[i]) - lb(t - a[i]);
        cnt += lb(4 * t - a[i]) - lb(3 * t - a[i]);
    }

    return (cnt & 1) * (1 << k);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<int> a(n), b(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    // solve for each bit
    int ans = 0;
    for (int k = 0; k <= 28; k++) {
        vector<int> a_new, b_new;
        for (int x : a) {
            a_new.push_back(x & ((1 << (k + 1)) - 1));
        }
        
        for (int x : b) {
            b_new.push_back(x & ((1 << (k + 1)) - 1));
        }

        ans += solve(n, k, a_new, b_new);
    }

    cout << ans << '\n';

    return 0;
}
