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

template<typename T>
struct BIT {
    int n;
    vector<T> bit;

    BIT(int n) : n(n), bit(n + 1) {}

    void upd(int x, int v) {
        x++;
        while (x <= n) {
            bit[x] += v;
            x += x & -x;
        }
    }

    T qry(int r) {
        T res{};
        while (r > 0) {
            res += bit[r];
            r -= r & -r;
        }
        return res;
    }

    T qry(int l, int r) {
        return qry(r) - qry(l);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    BIT<int> int_sum(n);
    vector<bool> is_point(n);

    auto upd_vars = [&](int l, int r) {
        // l to r forms a group
        if (l + 1 == r) {
            int_sum.upd(l, 1);
            is_point[l] = true;
        } else {
            int_sum.upd(l, 1);
            int_sum.upd(r - 1, 1);
            is_point[l] = true;
            is_point[r - 1] = true;
        }
    };

    int l = 0;
    for (int i = 1; i < n; i++) {
        if (nums[i] > nums[i - 1]) {
            upd_vars(l, i);
            l = i;
        }
    }

    upd_vars(l, n);

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;

        int ans = int_sum.qry(l, r);
        if (!is_point[l]) ans++;
        if (l + 1 != r && !is_point[r - 1]) ans++;
        cout << ans << '\n';
    }

    return 0;
}
