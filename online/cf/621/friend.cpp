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

int n, x;

void solve() {
    int n, x; cin >> n >> x;
    int m = 0;
    int a = INF;

    for (int i = 0; i < n; i++) {
        int q; cin >> q;
        int ans;
        if (q == x) {
            ans = 1;
        } else if (q > x) {
            ans = 2;
        } else {
            ans = x / q;
            if (ans * q != x) {
                ans++;
            }
        }
        
        a = min(a, ans);
    }

    cout << a << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
