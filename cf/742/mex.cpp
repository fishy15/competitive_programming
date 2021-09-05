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
#define MAXN 300010

using namespace std;

int pxor[MAXN];

void solve() {
    int a, b; cin >> a >> b;
    a--;
    if (pxor[a] == b) {
        cout << a + 1 << '\n';
    } else if ((pxor[a] ^ b) != (a + 1)) {
        cout << a + 2 << '\n';
    } else {
        cout << a + 3 << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int i = 1; i < MAXN; i++) {
        pxor[i] = pxor[i - 1] ^ i;
    }

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
