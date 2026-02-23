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

vector<int> construct_max(int n) {
    if (n == 1) {
        return {1, 1};
    } else if (n == 2) {
        return {1, 2, 1, 2};
    } else {
        vector<int> ans = {1, 2};
        rep(i, 3, n+1) {
            ans.push_back(i);
            ans.push_back(i-2);
        }
        ans.push_back(n-1);
        ans.push_back(n);
        return ans;
    }
}

void solve() {
    int n, k;
    cin >> n >> k;

    auto max_comp = [&](int a) {
        return 2 * a - 1;
    };

    if (n <= k && k <= max_comp(n)) {
        int good_pref = 0;
        while (good_pref + max_comp(n - good_pref) != k) {
            good_pref++;
        }

        vector<int> ans = construct_max(n - good_pref);
        rep(i, 0, good_pref) {
            ans.push_back(n - i);
            ans.push_back(n - i);
        }

        cout << "YES\n";
        for (auto x : ans) {
            cout << x << ' ';
        }
        cout << '\n';
    } else {
        cout << "NO\n";
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
