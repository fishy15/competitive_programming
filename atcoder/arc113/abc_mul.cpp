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

int k;
ll ans;

ll calc(int x) {
    ll ans = 0;
    for (int i = 1; i <= x; i++) {
        ans += x / i;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> k;
    for (int i = 1; i <= k; i++) {
        ans += calc(k / i);
    }

    cout << ans << '\n';

    return 0;
}
