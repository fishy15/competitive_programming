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

bool ok(int x) {
    if (x == 1) return false;

    int sum = 1;
    for (int y = 2; y * y <= x; y++) {
        if (x % y == 0) {
            sum += y;
            if (y * y != x) {
                sum += x / y;
            }
        }
    }

    return sum == x;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    for (int i = 1; i <= 500; i++) {

    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (ok(x)) ans++;
    }

    cout << ans << '\n';

    return 0;
}
