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

struct op_state {
    int abs_value;
    int flip_count;
    bool pos;
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<int> nums(n);
    rep(i, 0, n) {
        cin >> nums[i];
    }

    vector<pair<char, int>> ops(q);
    rep(i, 0, q) {
        cin >> ops[i].first >> ops[i].second;
    }

    int num_flips = 0;

    vector<op_state> st;
    rep(i, 0, q) {
        auto [dir, x] = ops[i];
        if (dir == '<') {
            if (x > 0) {
                num_flips++;
                x--;
            }
            x = abs(x);
            while (!st.empty() && st.back().abs_value >= x) {
                st.pop_back();
            }
            st.push_back({x, num_flips, true});
        } else {
            if (x < 0) {
                num_flips++;
                x++;
            }
            x = abs(x);
            while (!st.empty() && st.back().abs_value >= x) {
                st.pop_back();
            }
            st.push_back({x, num_flips, false});
        }
    }

    for (auto x : nums) {
        auto it = lower_bound(all(st), op_state{abs(x), -1, false}, [](const auto &op1, const auto &op2) {
            return op1.abs_value < op2.abs_value;
        });
        int prev_flips = 0;
        if (it != begin(st)) {
            it--; 
            if (it->pos) {
                x = abs(x);
            } else {
                x = -abs(x);
            }
            prev_flips = it->flip_count;
        }

        if ((num_flips - prev_flips) % 2 == 1) {
            x *= -1;
        }

        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}
