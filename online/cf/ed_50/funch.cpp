#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll n, a; cin >> n >> a;

    ll ans = 0;
    if (a % n == 0) {
        ans = a / n;
    } else {
        ans = a / n + 1;
    }

    cout << ans << '\n';
    return 0;
}
