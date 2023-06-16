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

int n, k;
long double ans;
long double tot = 1;
int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = k; i >= 1; i--) {
        long double cur = 1;
        for (int j = 0; j < n; j++) {
            cur *= 1 - 1.0 / i;
        }
        ans += i * (1 - cur) * tot;
        tot *= cur;
    }

    cout << fixed << setprecision(6) << ans << '\n';

    return 0;
}
