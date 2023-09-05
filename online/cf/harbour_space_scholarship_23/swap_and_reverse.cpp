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

    string s;
    cin >> s;

    if (k % 2 == 0) {
        sort(s.begin(), s.end());
        cout << s << '\n';
    } else {
        // parity is always preserved
        string even, odd;
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                even += s[i];
            } else {
                odd += s[i];
            }
        }

        sort(even.begin(), even.end());
        sort(odd.begin(), odd.end());

        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                cout << even[i / 2];
            } else {
                cout << odd[i / 2];
            }
        }
        cout << '\n';
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
