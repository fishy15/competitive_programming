#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void solve() {
    string s;
    cin >> s;
    
    int n = (int) s.size();
    vector dp(n + 1, array<ll, 2>{});
    
    for (int i = n - 1; i >= 0; i--) {
        ll mul = n - i;
        if (s[i] == '0') {
            dp[i][0] = dp[i + 1][0] + 2 * mul;
            dp[i][1] = dp[i + 1][0] + mul;
        } else {
            dp[i][0] = dp[i + 1][1] + mul;
            dp[i][1] = dp[i + 1][1] + 2 * mul;
        }
    }
    
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += dp[i][0];
    }
    
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        solve();
    }
}
