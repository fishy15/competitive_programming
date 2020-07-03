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

int n, a, b;
long double cur[700];
long double nxt[700];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> a >> b;
    cur[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= 6 * n; j++) {
            for (int k = 1; k <= 6; k++) {
                nxt[j + k] += cur[j] / 6;
            }
        }
        for (int j = 0; j <= 6 * n; j++) {
            cur[j] = nxt[j];
            nxt[j] = 0;
        }
    }

    long double ans = 0;
    for (int i = a; i <= b; i++) {
        ans += cur[i];
    }

    cout << fixed << setprecision(6) << ans << '\n';

    return 0;
}
