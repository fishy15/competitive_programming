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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 0; i < n; i++) {
        int ans = 0;

        // before
        int cur_max = 0;
        for (int j = i; j >= 0; j--) {
            if (nums[j] > cur_max) {
                ans++;
                cur_max = nums[j];
            }
        }

        // after
        cur_max = 0;
        for (int j = i; j < n; j++) {
            if (nums[j] > cur_max) {
                ans++;
                cur_max = nums[j];
            }
        }

        cout << ans - 2 << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
