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
#include <functional>
#include <numeric>

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
    int n;
    cin >> n;

    ll last_sum = 0;
    ll other_sum = 0;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (i % 2 == (n - 1) % 2) {
            last_sum += x;
        } else {
            other_sum += x;
        }
    }

    if (n % 2 == 1 || last_sum >= other_sum) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;
    
    while (t--) {
        solve();
    }

    return 0;
}
