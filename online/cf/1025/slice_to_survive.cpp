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

int moves(int x) {
    int moves = 0;
    while (x > 1) {
        x = (x + 1) / 2;
        moves++;
    }
    return moves;
}

void solve() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    a--;
    b--;

    auto n2 = min(a+1, n-a);
    auto m2 = min(b+1, m-b);
    auto ans = min(
        moves(n2) + moves(m) + 1,
        moves(n) + moves(m2) + 1
    );
    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
