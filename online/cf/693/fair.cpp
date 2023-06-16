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
    int one = 0;
    int two = 0;
    
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x == 1) one++;
        else two++;
    }

    int sum = one + 2 * two;
    if (sum % 2 != 0) {
        cout << "NO\n";
        return;
    }

    for (int i = 0; i <= two; i++) {
        int v = sum / 2 - 2 * i;
        if (v <= one && v >= 0) {
            cout << "YES\n";
            return;
        }
    }

    cout << "NO\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
