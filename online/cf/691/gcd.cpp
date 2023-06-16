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
#define MAXN 200010

using namespace std;

int n, m;
ll a[MAXN];
ll b[MAXN];
ll rest_gcd;

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];

    sort(a, a + n);

    if (n == 1) {
        for (int i = 0; i < m; i++) {
            cout << a[0] + b[i] << ' ';
        }
        cout << '\n';
        return 0;
    }

    rest_gcd = a[1] - a[0];

    for (int i = 2; i < n; i++) {
        rest_gcd = gcd(rest_gcd, a[i] - a[0]);
    }

    for (int j = 0; j < n; j++) {
        cout << gcd(a[0] + b[j], rest_gcd) << ' ';
    }
    cout << '\n';

    return 0;
}
