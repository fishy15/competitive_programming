#include <iostream>

#define ll long long
#define MOD 998244353

using namespace std;

int main() {
    int n; cin >> n;
    ll fact = 1;
    ll ans = 1;

    for (int i = 2; i <= n; i++) {
        ans = (ans + fact - 1) * i % MOD;
        fact *= i;
        fact %= MOD;
    }

    cout << ans << '\n';
}
