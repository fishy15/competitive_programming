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
    int cnt[3] = {0, 0, 0};

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        cnt[nums[i] % 3]++;
    }

    int ans = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 3; j++) {
            int nxt = (j + 1) % 3;
            if (cnt[nxt] < n / 3) {
                int d = n / 3 - cnt[nxt];
                cnt[nxt] += d;
                cnt[j] -= d;
                ans += d;
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
