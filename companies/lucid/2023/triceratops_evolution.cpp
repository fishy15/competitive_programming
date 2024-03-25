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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    ld g1, p0, p1, p2;
    cin >> g1 >> p0 >> p1 >> p2;

    for (int i = 0; i < n; i++) {
        g1 = (1 - g1) * (1 - g1) * p0
           + 2 * g1 * (1 - g1) * p1
           + g1 * g1 * p2;
    }

    cout << fixed << setprecision(12) << g1 << '\n';

    return 0;
}
