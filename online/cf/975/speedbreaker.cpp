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
    int n;
    cin >> n;

    vector<int> a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }

    vector<vector<int>> r_of(n);
    rep(i, 0, n) {
        r_of[a[i] - 1].push_back(i);
    }

    vector<int> psum(n + 1);
    int wanted = 0;
    int all_first = -1;
    int all_last = -1;
    rep(r, 0, n) {
        if (!r_of[r].empty()) {
            wanted++;
            auto first = r_of[r][0];
            auto last = r_of[r].back();

            if (all_first == -1) {
                all_first = first;
                all_last = last;
            } else {
                all_first = min(all_first, first);
                all_last = max(all_last, last);
            }

            auto range = all_last - all_first;
            if (range > r) {
                // not possible to form
                cout << "0\n";
                return;
            } else {
                int extra = r - range;
                auto start = max(all_first - extra, 0);
                auto end = min(all_last + extra + 1, n);
                psum[start]++;
                psum[end]--;
            }
        }
    }

    rep(i, 1, n+1) {
        psum[i] += psum[i - 1];
    }

    cout << count(all(psum), wanted) << '\n';
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
