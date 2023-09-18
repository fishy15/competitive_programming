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

    int lower_bound(T val) {
        T sum{};
        int pos = 0;

        for (int i = 20; i >= 0; i--) {
            int nxt = pos + (1 << i);
            if (nxt <= n && sum + bit[nxt] < val) {
                sum += bit[nxt];
                pos = nxt;
            }
        }

        return pos;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (auto &x : nums) {
        cin >> x;
        x--;
    }

    vector<int> inc_len(n);
    for (int i = n - 1; i >= 0; i--) {
        if (i < n - 1 && nums[i] <= nums[i + 1]) {
            inc_len[i] = inc_len[i + 1] + 1;
        } else {
            inc_len[i] = 1;
        }
    }

    BIT<int> cur(n);
    vector<int> sort_same_len(n - k + 1);
    for (int i = n - 1; i >= 0; i--) {
        cur.upd(nums[i], 1);
        if (i + k < n) {
            cur.upd(nums[i + k], -1);
        }

        if (i < n - k + 1) {
            auto check = [&](int m) {
                if (m == 0) return true;
                return nums[i + m - 1] == cur.lower_bound(m);
            };

            int l = 0;
            int r = min(k, inc_len[i]);
            int ans = -1;
            while (l <= r) {
                int m = (l + r) / 2;
                if (check(m)) {
                    ans = m;
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }
            
            if (ans == k) {
                sort_same_len[i] = INF;
            } else {
                sort_same_len[i] = i + ans;
            }
        }
    }

    // pick first match since later can't help
    auto sort_idx = max_element(sort_same_len.begin(), sort_same_len.end()) - sort_same_len.begin();
    auto start_it = nums.begin() + sort_idx;
    sort(start_it, start_it + k);

    for (auto x : nums) {
        cout << x + 1 << ' ';
    }
    cout << '\n';

    return 0;
}
