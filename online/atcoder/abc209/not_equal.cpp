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

int n;
int c[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    sort(c, c + n);

    ll ans = 1;
    for (int i = 0; i < n; i++) {
        if (c[i] > i) {
            ans = ans * (c[i] - i) % MOD;
        } else {
            ans = 0;
        }
    }

    cout << ans << '\n';

    return 0;
}
