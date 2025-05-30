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

    vector<int> d(n);
    rep(i, 0, n) {
        cin >> d[i];
    }

    vector<array<int, 2>> bounds(n);
    rep(i, 0, n) {
        cin >> bounds[i][0] >> bounds[i][1];
    }

    vector<int> max_after(n);
    max_after[n-1] = bounds[n-1][1];
    for (int i = n-2; i >= 0; i--) {
        max_after[i] = min(max_after[i+1], bounds[i][1]);
    }

    int cur = 0;
    vector<int> my_ones;
    rep(i, 0, n) {
        if (d[i] == -1) {
            if (cur+1 <= max_after[i]) {
                d[i] = 1;
                my_ones.push_back(i);
                cur++;
            } else {
                d[i] = 0;
            }
        } else if (d[i] == 1) {
            if (cur+1 > max_after[i]) {
                if (my_ones.empty()) {
                    cout << "-1\n";
                    return;
                } else {
                    auto idx = my_ones.back();
                    my_ones.pop_back();
                    d[idx] = 0;
                    cur--;
                }
            }
            cur++;
        }
    }

    cur = 0;
    rep(i, 0, n) {
        cur += d[i];
        if (!(bounds[i][0] <= cur && cur <= bounds[i][1])) {
            cout << "-1\n";
            return;
        }
    }

    for (auto x : d) {
        cout << x << ' ';
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
