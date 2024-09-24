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

using ld = long double;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    ld ans = 0;
    ld tot = 1;

    for (int i = k; i >= 1; i--) {
        ld cur = 1;
        for (int j = 0; j < n; j++) {
            cur *= 1 - (ld) 1.0 / i;
        }
        ans += i * (1 - cur) * tot;
        tot *= cur;
    }

    cout << fixed << setprecision(6) << ans << '\n';

    return 0;
}
