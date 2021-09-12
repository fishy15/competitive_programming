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
#include <cstdio>
#include <cstring>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n; cin >> n;
    string a, b; cin >> a >> b;

    int i = 0;
    int ans = 0;
    while (i < n) {
        if (a[i] + b[i] == 1 + 2 * '0') {
            ans += 2;
            i++;
        } else if (a[i] == '1') {
            if (i < n - 1 && a[i + 1] == '0' && b[i + 1] == '0') {
                ans += 2;
                i += 2;
            } else {
                ans += 0;
                i += 1;
            }
        } else {
            if (i < n - 1 && a[i + 1] == '1' && b[i + 1] == '1') {
                ans += 2;
                i += 2;
            } else {
                ans += 1;
                i += 1;
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
