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
    int n; cin >> n;
    ll cur = 0;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        cur ^= x;
    }
    if (cur) {
        cout << "first\n";
    } else {
        cout << "second\n";
    }
}

int t;
int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> t;
    while (t--) solve();

    return 0;
}
