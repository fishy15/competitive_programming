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

int t, n;
int a[100];
int b[100];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> t >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    sort(a, a + n);
    sort(b, b + n);

    if (t == 1) {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += max(a[i], b[i]);
        }
        cout << ans << '\n';
    } else {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += max(a[i], b[n - i - 1]);
        }
        cout << ans << '\n';
    }

    return 0;
}
