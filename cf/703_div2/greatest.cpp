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

int n;
int second;

int qry(int x, int y) {
    if (x > y) swap(x, y);
    cout << "? " << x << ' ' << y << endl;
    int res; cin >> res;
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    second = qry(1, n);

    // check which half
    int ns = -1;
    int l = 1;
    int r = second - 1;
    if (second != 1) {
        ns = qry(1, second);
    }

    if (ns != second) {
        l = second + 1;
        r = n;

        int ans = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            int res = qry(second, m);
            if (res == second) {
                ans = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        cout << "! " << ans << endl;
    } else {
        int ans = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            int res = qry(second, m);
            if (res == second) {
                ans = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        cout << "! " << ans << endl;
    }

    return 0;
}
