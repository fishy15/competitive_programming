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
#define MAXN 100010

using namespace std;

int n, k;
int a[MAXN];

int l_end[MAXN];
int r_end[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        if (i > 0 && a[i - 1] < a[i]) {
            r_end[i] = r_end[i - 1] + 1;
        } else {
            r_end[i] = 1;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        if (i < n - 1 && a[i] < a[i + 1]) {
            l_end[i] = l_end[i + 1] + 1;
        } else {
            l_end[i] = 1;
        }
    }

    int ans = *max_element(r_end, r_end + n);
    for (int i = k + 1; i < n; i++) {
        int p = i - k - 1;
        if (a[p] < a[i]) {
            ans = max(ans, r_end[p] + l_end[i]);
        }
    }

    cout << ans << '\n';

    return 0;
}
