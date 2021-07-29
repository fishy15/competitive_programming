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
#define MAXN 100010

using namespace std;

int n, q, k;
int nums[MAXN];
ll psum[MAXN];

ll get(int l, int r) {
    int ans = psum[r];
    if (l) ans -= psum[l - 1];
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q >> k;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 0; i < n - 1; i++) {
        psum[i] += nums[i + 1] - nums[i] - 1;
        if (i) psum[i] += psum[i - 1];
    }

    while (q--) {
        int l, r; cin >> l >> r;
        l--; r--;
        ll res = l != r ? 2 * get(l, r - 1) : 0;
        res += nums[l] - 1;
        res += k - nums[r];
        cout << res << '\n';
    }

    return 0;
}
