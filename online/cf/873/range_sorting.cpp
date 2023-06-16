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

vector<int> get_ans(vector<int> &nums) {
    int l = 0;
    int n = nums.size();
    priority_queue<int> pq;
    /* cout << l << ": "; */

    BIT<int> in_set(n);
    vector<int> res;
    /* for (int r = 1; r <= l; r++) cout << "  "; */
    for (int r = l + 1; r <= n; r++) {
        int num = nums[r - 1];
        in_set.upd(num, 1);

        auto insert_idx = in_set.qry(num);
        while (!pq.empty() && pq.top() > insert_idx) {
            pq.pop();
        }
        pq.push(r - l);
        res.push_back((r - l) - pq.size());
    }

    return res;
}

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    auto nums_sorted = nums;
    sort(nums_sorted.begin(), nums_sorted.end());

    vector<int> opp(n);
    for (int i = 0; i < n; i++) {
        nums[i] = lower_bound(nums_sorted.begin(), nums_sorted.end(), nums[i]) - nums_sorted.begin();
        opp[i] = (n - 1) - nums[i];
    }

    reverse(opp.begin(), opp.end());

    auto cur = get_ans(nums);
    auto diffs = get_ans(opp);
    for (int i = 0; i < n - 1; i++) {
        diffs[i] = diffs[i + 1] - diffs[i];
    }
    diffs.pop_back();

    reverse(cur.begin(), cur.end());
    reverse(diffs.begin(), diffs.end());

    int total_rem = 0;
    ll cur_sum = accumulate(cur.begin(), cur.end(), 0LL);
    ll ans = cur_sum;

    auto clean = [&]() {
        while (!cur.empty() && cur.back() <= total_rem) {
            cur_sum += (total_rem - cur.back());
            cur.pop_back();
        }
    };

    for (int i = 0; i < n - 1; i++) {
        cur_sum -= (int) cur.size() * diffs[i];
        total_rem += diffs[i];
        clean();

        ans += cur_sum;

        cout << cur_sum << ' ' << cur.size() << '\n';
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
