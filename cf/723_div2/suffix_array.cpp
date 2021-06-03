/*
 * We note that all of the indices that have an A will be at the beginning of the string, then all of the 
 * indices that have a B, etc. Therefore, we want to check if two adjacent indices are forced to be 
 * different or not. For suf[i] and suf[i + 1], those indices can be the same character if the suffix
 * starting at suf[i] + 1 is lexicographically less than the suffix starting at suf[i + 1] + 1. Figuring out
 * how many times this is not the case tells us what characters must be distinct.
 *
 * Now, we can model this problem as a series of differences. The first difference tells us how many 
 * characters we have to move forward to get the character at suf[0], the second difference tells us how 
 * many characters more we have to move forward to go from the character at suf[0] to the character at 
 * suf[1], etc. The last difference is from the character at suf[n - 1] to the last character in the 
 * alphabet. The sum of these differences must be k - 1. If we pre-subtract the differences that are forced
 * to be non-zero, this is equivalent to stars and bars. 
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
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int v) : v(v) {}

    mi &operator*=(const mi &m2) {
        v = (ll) v * m2.v % MOD;
        return *this;
    }

    mi operator*(const mi &m2) const {
        mi m = *this;
        return m *= m2;
    }

    mi pow(ll e) const {
        mi res = 1;
        mi n = *this;
        while (e) {
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

int n, k;
int suf[MAXN];
int idx[MAXN];

mi prod(int start, int len) {
    mi res = 1;
    for (int i = 0; i < len; i++) {
        res *= i + start;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> suf[i];
        idx[suf[i]] = i;
    }
    idx[n] = -1;

    int needed = 0;
    for (int i = 0; i < n - 1; i++) {
        if (idx[suf[i] + 1] > idx[suf[i + 1] + 1]) {
            needed++;
        }
    }

    int tot = k - needed + n - 1;

    if (tot < n) {
        cout << "0\n";
        return 0;
    }

    cout << (prod(tot - n + 1, n) * prod(1, n).inv()).v << '\n';

    return 0;
}
