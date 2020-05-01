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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> ans;
    ll cur = 1;
    int cnt = 0;
    while (cur <= n) {
        n -= cur;
        ans.push_back(cur);
        cur *= 2;
        cnt++;
    }

    vector<int> ans2;
    for (int i = cnt - 1; i >= 0; i--) {
        ans2.push_back(ans[i]);
        if (n > 0) {
            int v = min(n, (1 << i));
            n -= v;
            ans2.push_back(v);
        }
    }

    reverse(ans2.begin(), ans2.end());
    cout << ans2.size() - 1 << '\n';

    for (int i = 0; i < ans2.size() - 1; i++) {
        cout << ans2[i + 1] - ans2[i] << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
