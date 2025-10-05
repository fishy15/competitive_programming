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

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> nums(n);
    vector<int> psum(n+1);
    rep(i, 0, n) {
        cin >> nums[i];
        psum[i+1] = nums[i] + psum[i];
    }

    vector<int> double_psum(n);
    rep(i, 0, n-1) {
        auto c = (nums[i] == nums[i+1]) ? 1 : 0;
        double_psum[i+1] = double_psum[i] + c;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;

        if ((r - l) % 3 == 0 && (psum[r] - psum[l]) % 3 == 0) {
            if (l < r && (double_psum[r-1] - double_psum[l]) == 0) {
                cout << (r - l) / 3 + 1 << '\n';
            } else {
                cout << (r - l) / 3 << '\n';
            }
        } else {
            cout << "-1\n";
        }
    }
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
