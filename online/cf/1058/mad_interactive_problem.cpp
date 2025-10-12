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

vector<int> nums;

int ask(const set<int> &s) {
    cout << "? " << sz(s) << ' ';
    for (auto x : s) {
        cout << x+1 << ' ';
    }
    cout << endl;
    int res = 0;
#ifdef LOCAL
    set<int> seen;
    for (auto x : s) {
        if (seen.count(nums[x])) {
            res = max(res, nums[x]);
        }
        seen.insert(nums[x]);
    }
#else
    cin >> res;
#endif
    return res;
}

void answer(const vector<int> &v) {
    cout << "! ";
    for (auto x : v) cout << x << ' ';
    cout << endl;

#ifdef LOCAL
    if (v == nums) {
        cout << "GOOD\n";
    } else {
        cout << "BAD\n";
    }
#endif
}

void solve() {
    int n;
    cin >> n;

#ifdef LOCAL
    nums.resize(2 * n);
    rep(i, 0, 2 * n) {
        cin >> nums[i];
    }
#endif

    vector<int> ans(2 * n);
    set<int> cur = {0};

    rep(i, 1, 2*n) {
        cur.insert(i); 
        auto res = ask(cur);
        if (res > 0) {
            ans[i] = res;
            cur.erase(i);
        }
    }

    cur = {2 * n - 1};
    for (int i = 2 * n - 2; i >= 0; i--) {
        cur.insert(i); 
        if (ans[i] == 0) {
            auto res = ask(cur);
            if (res > 0) {
                ans[i] = res;
                cur.erase(i);
            }
        }
    }

    answer(ans);
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
