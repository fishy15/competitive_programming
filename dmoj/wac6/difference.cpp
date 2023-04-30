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
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

int n;
ll nums[MAXN];
int idx[MAXN];

struct DSU {
    vector<int> dsu;
    vector<int> sz;
    vector<ll> mini, maxi;
    DSU(int n) : dsu(n), sz(n, 1), mini(nums, nums + n), maxi(nums, nums + n) {
        iota(dsu.begin(), dsu.end(), 0);
    }
    int find(int x) {
        if (x == dsu[x]) return x;
        return dsu[x] = find(dsu[x]);
    }
    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            dsu[y] = x;
            sz[x] += sz[y];
            mini[x] = min(mini[x], mini[y]);
            maxi[x] = min(maxi[x], maxi[y]);
        }
    }
};

bool check(ll k) {
    DSU dsu(n);
    for (int i = 0; i < n - 1; i++) {
        if (nums[idx[i + 1]] - nums[idx[i]] <= k) {
            dsu.join(idx[i], idx[i + 1]);
        }
    }
    for (int i = 0; i < n - 1; i++) {
        int x = dsu.find(i);
        int y = dsu.find(i + 1);
        if (x != y && dsu.maxi[x] > dsu.mini[y]) return false;
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    iota(idx, idx + n, 0);
    sort(idx, idx + n, [](const int &a, const int &b) {
        return nums[a] < nums[b];
    });

    ll l = 0;
    ll r = 1e18;
    ll ans = -1;

    while (l <= r) {
        ll m = l + (r - l) / 2;
        bool res = check(m);
        if (res) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    cout << ans << '\n';

    return 0;
}
