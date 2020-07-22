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
    vector<int> nums;

    for (int i = 0; i < 2 * n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    vector<int> len;
    vector<bool> vis(2 * n);
    while (!vis[0]) {
        pair<int, int> mm;
        for (int i = 0; i < 2 * n; i++) {
            if (!vis[i]) mm = max(mm, {nums[i], i});
        }

        int cnt = 0;
        int pos = mm.second;
        while (pos < 2 * n && !vis[pos]) {
            vis[pos] = true;
            cnt++;
            pos++;
        }

        len.push_back(cnt);
    }

    vector<int> dp1(2 * n);
    vector<int> dp2(2 * n);
    dp1[0] = 1;
    
    for (int l : len) {
        for (int i = 0; i < 2 * n; i++) {
            if (i >= l) {
                dp2[i] |= dp1[i - l];
            }
        }
        dp1 = dp2;
    }

    if (dp1[n]) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
