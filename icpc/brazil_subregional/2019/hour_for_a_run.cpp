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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int v, n;
    cin >> v >> n;

    ll total = v * n;
    rep(i, 1, 10) {
        // want i / 10 to be satisfies
        // x / total >= i / 10
        // => x >= i / 10 * total, round up
        auto ans = (i * total + 9) / 10;
        cout << ans << ' ';
    }
    cout << '\n';

    return 0;
}
