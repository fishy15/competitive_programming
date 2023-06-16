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

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> psum(m + 1, 1);
    psum[0] = 0;

    int left = 0;
    int right = 0;
    set<int> normal;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (x == -1) {
            left++;
        } else if (x == -2) {
            right++;
        } else {
            psum[x] = 0;
            normal.insert(x - 1);
        }
    }

    partial_sum(psum.begin(), psum.end(), psum.begin());
    auto get = [&](int l, int r) { return psum[r] - psum[l]; };
   
    int ans = 0;
    for (int mid : normal) {
        int before = min(get(0, mid), left);
        int after = min(get(mid + 1, m), right);
        ans = max<int>(ans, before + after + normal.size());
    }

    // start with a left
    if (!normal.count(m - 1)) {
        ans = max<int>(ans, min(left, get(0, m)) + normal.size());
    }

    // start with a right
    if (!normal.count(0)) {
        ans = max<int>(ans, min(right, get(0, m)) + normal.size());
    }

    cout << ans << '\n';
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
