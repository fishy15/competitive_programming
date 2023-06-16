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

int solve(int n, int k, int start) {
    if (start == 0) {
        if (k < n / 2) {
            return 2 * k + 1;
        } else {
            int rest = n - n / 2;
            return 2 * solve(rest, k - n / 2, n % 2);
        }
    } else {
        if (k < (n + 1) / 2) {
            return 2 * k;
        } else {
            int rest = n - (n + 1) / 2;
            return 2 * solve(rest, k - (n + 1) / 2, (n + 1) % 2) + 1;
        }
    }
}

void solve() {
    int n, k;
    cin >> n >> k;
    k--;
    cout << solve(n, k, 0) + 1 << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int q;
    cin >> q;

    while (q--) {
        solve();
    }

    return 0;
}
