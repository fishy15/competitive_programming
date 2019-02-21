#include <iostream>
#include <vector>

#define MOD 1000000007
#define ll long long

using namespace std;

ll dp[100001];

void mod(ll &n) {
    while (n < 0) {
        n += MOD;
    }

    n %= MOD;
}

ll val(int pos) {
    if (pos == 0) {
        return 0;
    }

    return dp[pos - 1];
}

int main() {
    int n, k; cin >> n >> k;

    dp[0] = 1;
    for (int i = 1; i <= 1e5; i++) {
        dp[i] = dp[i - 1];

        if (i >= k) {
            dp[i] += dp[i - k];
        }

        mod(dp[i]);
    }

        for (int i = 0; i < 10; i++) {
        cout << dp[i] << ' ';
    } cout << endl;

    for (int i = 1; i <= 1e5; i++) {
        dp[i] += dp[i - 1];
        mod(dp[i]);
    }

    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        cout << val(b) - val(a - 1) << '\n';
    }

    return 0;
}