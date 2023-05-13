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

struct RevStack {
    struct data {
        ll val;
        ll sum_after;
        int len;
        int len_after;
    };

    ll total = 0;
    vector<data> st;

    void add(int x) {
        if (st.empty()) {
            st.push_back({x, 0, 1, 0});
            total += x;
        } else if (x < st.back().val) {
            auto &last = st.back();
            st.push_back({x, last.sum_after + last.val * last.len, 1, last.len + last.len_after});
            total += x;
        } else {
            int tot_size = 1;
            while (!st.empty() && st.back().val <= x) {
                total += (x - st.back().val) * st.back().len;
                tot_size += st.back().len;
                st.pop_back();
            }

            if (st.empty()) {
                st.push_back({x, 0, tot_size, 0});
            } else {
                auto &last = st.back();
                st.push_back({x, last.sum_after + last.val * last.len, tot_size, last.len + last.len_after});
            }

            total += x;
        }
    }

    // sz = how much to cut off
    ll qry(int sz) {
        auto cmp = [](int sz, auto entry) { return sz < entry.len_after; };
        auto entry = *prev(upper_bound(st.begin(), st.end(), sz, cmp));
        return total - entry.sum_after - entry.val * (sz - entry.len_after);
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

    vector<vector<pair<int, int>>> qry(n);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        qry[l].push_back({r, i});
    }

    vector<ll> psum(n + 1);
    for (int i = 0; i < n; i++) {
        psum[i + 1] = nums[i] + psum[i];
    }

    RevStack st;
    vector<ll> ans(q);

    for (int i = n - 1; i >= 0; i--) {
        st.add(nums[i]);
        for (auto [r, idx] : qry[i]) {
            ans[idx] = st.qry(n - r) - (psum[r] - psum[i]);
        }
    }

    for (auto x : ans) {
        cout << x << '\n';
    }

    return 0;
}
