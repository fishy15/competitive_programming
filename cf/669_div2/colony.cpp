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
    int n, k; cin >> n >> k;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int cnt = 1;
    while (true) {
        int i = 0;
        for (; i < n - 1; i++) {
            if (nums[i] < nums[i + 1]) break;
        }

        if (i == n - 1) {
            cout << "-1\n";
            return;
        } else {
            nums[i]++;
            if (k == cnt) {
                cout << i + 1 << '\n';
                return;
            }
        }

        cnt++;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
