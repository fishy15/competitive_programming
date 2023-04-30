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
    int n, k;
    cin >> n >> k;

    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        cnt[x]++;
    }

    int one_count = 0;
    int two_count = 0;

    for (auto [_, c] : cnt) {
        if (c == 1) {
            one_count++;
        } else {
            two_count++;
        }
    }

    if (2 * min(two_count, k) + one_count >= n && 2 * k >= n) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
