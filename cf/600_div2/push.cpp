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

void solve() {
    int n;
    vector<int> a;
    vector<int> b;

    cin >> n;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a.push_back(x);
    }

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        b.push_back(x);
    }

    int prev = 0;
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        int d = b[i] - a[i];
        if (d < 0) {
            cout << "NO\n";
            return;
        } else if (d > 0) {
            if (prev != d) {
                cnt++;
            }
        }

        prev = d;
    }

    if (cnt <= 1) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
