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
#define MAXN 200010

using namespace std;

int n, m;
int a[MAXN];
int b[MAXN];

int find_closest() {
    int ans = INF;
    for (int j = 0; j < n; j++) {
        int d = min(j, n - j);
        if (a[j] != a[0]) {
            ans = min(ans, d);
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    bool got_other = false;

    int ans = 0;
    for (int i = 0; i < m; i++) {
        if (got_other) {
            if (b[i] != b[i - 1]) {
                ans++;
            }
        } else {
            if (b[i] != a[0]) {
                int d = find_closest();
                if (d == INF) {
                    cout << "-1\n";
                    return 0;
                } else {
                    ans += d;
                    got_other = true;
                }
            }
        }
    }

    cout << ans + m << '\n';

    return 0;
}
