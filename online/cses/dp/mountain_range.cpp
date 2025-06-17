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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

struct node {
    node *left = nullptr;
    node *right = nullptr;
    int v;
    node(int _v) : v(_v) {}
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    vector<pair<int, int>> ord(n);
    rep(i, 0, n) {
        ord[i] = {nums[i], i};
    }

    sort(all(ord), greater<>{});

    auto cur_it = begin(ord);
    set<int> present;
    vector<int> dp(n, 1);
    while (cur_it != end(ord)) {
        auto end_it = cur_it;
        while (end_it != end(ord) && cur_it->first == end_it->first) {
            end_it++;
        }

        for (auto it = cur_it; it != end_it; it++) {
            auto idx = it->second;
            auto loc = present.lower_bound(idx);
            if (loc != begin(present)) {
                auto prev_idx = *prev(loc);
                if (nums[prev_idx] > nums[idx]) {
                    dp[idx] = max(dp[idx], dp[prev_idx] + 1);
                }
            }
            if (loc != end(present)) {
                auto next_idx = *loc;
                if (nums[next_idx] > nums[idx]) {
                    dp[idx] = max(dp[idx], dp[next_idx] + 1);
                }
            }
        }

        for (auto it = cur_it; it != end_it; it++) {
            present.insert(it->second);
        }

        cur_it = end_it;
    }

    cout << *max_element(all(dp)) << '\n';

    return 0;
}
