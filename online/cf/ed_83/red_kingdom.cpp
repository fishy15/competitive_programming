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

const int beg = 50;

bool check(vector<array<int, 3>> &nim) {
    if (nim.size() < 10 + beg) return false;
    int n = (int)(nim.size());
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (nim[i + beg][j] != nim[n - 6 + i][j]) return false;
        }
    }
    return true;
}

int mex(const vector<int> &vals) {
    for (int i = 0; i < 3; i++) {
        if (!count(vals.begin(), vals.end(), i)) return i;
    }
    return 3;
}

int calc(ll n, int period) {
    if (n < 0) return 0;
    if (n < beg) return n;
    return (n - beg) % period + beg;
}

void solve() {
    int n, x, y, z; cin >> n >> x >> y >> z;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    // 0 = x, 1 = y, 2 = z
    vector<array<int, 3>> nim = {{0, 0, 0}};
    int idx = 1;
    while (!check(nim)) {
        int p0 = max(idx - x, 0);
        int p1 = max(idx - y, 0);
        int p2 = max(idx - z, 0);
        int a = mex({nim[p0][0], nim[p1][1], nim[p2][2]});
        int b = mex({nim[p0][0], nim[p2][2]});
        int c = mex({nim[p0][0], nim[p1][1]});
        nim.push_back({a, b, c});
        idx++;
    }
    int period = idx - beg - 6;
    int ans = 0;
    ll nimval = 0;
    for (int i = 0; i < n; i++) {
        nimval ^= nim[calc(nums[i], period)][0];
    }
    if (nimval == 0) {
        cout << "0\n";
    } else {
        for (int i = 0; i < n; i++) {
            int p0 = calc(nums[i] - x, period);
            int p1 = calc(nums[i] - y, period);
            int p2 = calc(nums[i] - z, period);
            nimval ^= nim[calc(nums[i], period)][0];
            if ((nimval ^ nim[p0][0]) == 0) ans++;
            if ((nimval ^ nim[p1][1]) == 0) ans++;
            if ((nimval ^ nim[p2][2]) == 0) ans++;
            nimval ^= nim[calc(nums[i], period)][0];
        }
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

