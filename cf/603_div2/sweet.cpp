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

    int t; cin >> t;
    while (t--) {
        int a[3]; cin >> a[0] >> a[1] >> a[2];
        sort(a, a + 3);
        int ans = 0;
        ans += a[0];
        int diff = min(a[2] - a[1], a[0]);
        a[0] -= diff;
        a[2] -= diff;
        a[2] -= a[0] / 2;
        a[1] -= a[0] - a[0] / 2;
        ans += min(a[1], a[2]);
        cout << ans << '\n';
    }

    return 0;
}
