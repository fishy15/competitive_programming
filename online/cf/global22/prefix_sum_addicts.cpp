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

    vector<ll> psums(k);
    for (int i = 0; i < k; i++) {
        cin >> psums[i];
    }

    if (k == 1) {
        cout << "Yes\n";
    } else {
        for (int i = k - 1; i > 0; i--) {
            psums[i] -= psums[i - 1];
        }

        for (int i = 2; i < k; i++) {
            // these are differences
            if (psums[i - 1] > psums[i]) {
                cout << "No\n";
                return;
            }
        }

        ll sum_needed = psums[0];
        ll leq_than = psums[1];
        ll terms = n - k + 1;

        if (sum_needed <= leq_than * terms) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
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
