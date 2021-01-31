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

struct bit {
    int n;
    vector<int> b;
    bit(int n) : n(n), b(n + 1) {}
    void upd(int x, int v) {
        while (x <= n) {
            b[x] += v;
            x += x & -x;
        }
    }
    int qry(int x) {
        int res = 0;
        while (x) {
            res += b[x];
            x -= x & -x;
        }
        return res;
    }
};

void solve() {
    int n; cin >> n;
    vector<int> nums(n);
    bit b(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    ll ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        ans += b.qry(nums[i]);
        b.upd(nums[i], 1);
    }

    if (ans % 2 == 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
