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

int qry(int l, int r) {
    cout << "? " << l << ' ' << r << endl;
    int x; cin >> x;
    return x;
}

void answer(int x) {
    cout << "! " << x << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    
    // find the max
    int l = 1;
    int r = n;

    int a = 0; // will be loc of max
    int mx = 0; // max besides n on left side

    while (l <= r) {
        int m = (l + r) / 2;
        int res = qry(1, m);

        if (res == n) {
            a = m;
            r = m - 1;
        } else {
            mx = max(mx, res);
            l = m + 1;
        }
    }

    int st;
    if (mx == n - 1) {
        st = l = 1;
        r = a - 1;
    } else {
        st = l = a + 1;
        r = n;
    }

    while (l <= r) {
        int m = (l + r) / 2;
        int res = qry(st, m);

        if (res == n - 1) {
            a = m;
            r = m - 1;
        } else {
            mx = max(mx, res);
            l = m + 1;
        }
    }

    answer(a);

    return 0;
}
