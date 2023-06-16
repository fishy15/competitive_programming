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

    vector buckets(k, 0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        x--;

        if (x % k != i % k) {
            buckets[i % k]++;
        }
    }

    int sum = accumulate(buckets.begin(), buckets.end(), 0);
    int one_cnt = count(buckets.begin(), buckets.end(), 1);
    if (sum == 0) {
        cout << "0\n";
    } else if (sum == 2 && one_cnt == 2) {
        cout << "1\n";
    } else {
        cout << "-1\n";
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
