// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
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

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            ans += x;
        }

        if (ans % n != 0) {
            ans += n - (ans % n);
        }

        ans /= n;

        cout << ans << '\n';
    }

    return 0;
}
