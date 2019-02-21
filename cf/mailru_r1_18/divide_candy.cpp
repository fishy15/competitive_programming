#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

int main() {
    int n, m; cin >> n >> m;
    vector<int> mods(m);

    for (ll i = 1; i <= n; i++) {
        int val = (i * i) % m;
        mods[val]++;
    }

    ll ans = 0;
    for (int i = 0; i <= m; i++) {
        ans += mods[i] * mods[m - i];
    }

    cout << ans << '\n';
}
