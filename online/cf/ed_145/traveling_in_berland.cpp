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
#include <cassert>

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

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n), b(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    rep(i, 0, n) {
        cin >> b[i];
    }

    auto total_steps = accumulate(all(a), 0LL);
    
    int first_one = -1;
    rep(i, 0, n) {
        if (b[i] == 1) {
            first_one = i;
            break;
        }
    }

    if (first_one == -1) {
        // everything costs two
        rep(i, 0, n) {
            cout << 2 * total_steps << ' ';
        }
        cout << '\n';
        return;
    }
    
    // if the last one was filled, how many ones can we fill here
    vector<ll> if_last(n);
    ll cur_ones = k;
    ll total_ones = k;
    queue<int> ones;
    rep(i, 0, n) {
        int loc = (first_one + i) % n;
        int nxt = (loc + 1) % n;
        cur_ones = max(0LL, cur_ones - a[loc]);
        if (b[loc] == 1) {
            ones.push(loc);
        }
        if (b[nxt] == 1) {
            if_last[nxt] = k - cur_ones;
            if (nxt != first_one) {
                total_ones += k - cur_ones;
                cur_ones = k;
            }
        }
    }

    vector<ll> ans(n);
    rep(i, 0, n) {
        int loc = (first_one + i) % n;
        ans[loc] = 2 * total_steps - (total_ones - cur_ones); 

        // update for the next iteration
        if (b[loc] == 1) {
            // remove it from the list
            ones.pop();
            if (ones.empty()) {
                total_ones = 0;
                cur_ones = 0;
            } else {
                auto nxt_one = ones.front();
                total_ones -= if_last[nxt_one];
            }

            ones.push(loc);
            auto to_add = k - cur_ones ;
            total_ones += to_add;
            cur_ones += to_add;
        }
        cur_ones = max(0LL, cur_ones - a[loc]);
    }

    rep(i, 0, n) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
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
