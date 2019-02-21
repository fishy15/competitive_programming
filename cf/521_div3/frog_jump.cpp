#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int n; cin >> n;
    vector<ll> anss;
    for (int i = 0; i < n; i++) {
        ll a, b, k; cin >> a >> b >> k;
        ll ans = (a - b) * (k / 2);

        if (k % 2 == 1) {
            ans += a;
        }
        
        anss.push_back(ans);
    }

    for (ll x : anss) {
        cout << x << '\n';
    }
    return 0;
}
