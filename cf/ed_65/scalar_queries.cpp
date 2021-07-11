/*
 * If we look at one value in a subarray by itself, the number of times it will be counted is (# of smaller
 * values to the left) + (# of smaller values to the right) + 1. Therefore, we can look at the left and 
 * right halves individually. Let's process the numbers from the smallest upward. If positions a, b, and c
 * (0-indexed) have already been processed, then the total number of smaller values to the left counted 
 * for each left bound is (a + 1) + (b + 1) + (c + 1). In addition, if we are at position i, there are 
 * (n - i) right bounds, so the total number of combinations is (sum of (left indices + 1)) * (n - i). We can
 * do similarly for the right bounds, and then the last term will be counted once for each subarray, meaning
 * that it will be counted (i + 1) * (n - i) times. We can do the range queries for the # of smaller values
 * to the left and right using BITs, so the overall time complexity is O(n log n).
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
#define MAXN 500010

using namespace std;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
        this->v = v;
    }
    mi(ll v) : mi((int)(v % MOD)) {}

    mi operator+(const mi &m2) const { return mi(v + m2.v); }
    mi operator-(const mi &m2) const { return mi(v - m2.v); }
    mi operator*(const mi &m2) const { return mi((ll) v * m2.v); }

    mi &operator+=(const mi &m2) { return *this = *this + m2; }
    mi &operator-=(const mi &m2) { return *this = *this - m2; }
    mi &operator*=(const mi &m2) { return *this = *this * m2; }
};

struct BIT {
    int n;
    vector<mi> st;

    BIT(int n) : n(n + 1) {
        st.resize(n + 1);
    }

    void upd(int x, mi v) {
        x++;
        while (x < n) {
            st[x] += v;
            x += x & -x;
        }
    }

    mi qry(int x) const {
        x++;
        mi res;
        while (x > 0) {
            res += st[x];
            x -= x & -x;
        }
        return res;
    }

    mi qry(int l, int r) {
        if (r < l) return 0;
        return qry(r) - qry(l - 1);
    }
};

int n;
vector<pair<int, int>> nums;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back({x, i});
    }

    sort(nums.begin(), nums.end());

    BIT before(n), after(n);

    mi ans = 0;
    for (auto [val, idx] : nums) {
        mi bef = before.qry(0, idx - 1);
        mi aft = after.qry(idx + 1, n - 1);
        mi combo = bef * mi(n - idx) + aft * mi(idx + 1) + mi(idx + 1) * mi(n - idx);
        ans += mi(val) * combo;

        before.upd(idx, idx + 1);
        after.upd(idx, n - idx);
    }

    cout << ans.v << '\n';

    return 0;
}
