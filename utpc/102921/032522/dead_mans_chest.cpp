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

int n;
ll g, m;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        m = max(m, x);
        g = gcd(g, m);
    }

    ll nums = m / g - n;
    if (nums % 2 == 0) {
        cout << "Davy Jones\n";
    } else {
        cout << "Jack Sparrow\n";
    }

    return 0;
}
