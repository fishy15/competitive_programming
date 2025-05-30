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

void solve() {
    int n;
    cin >> n;

    vector<int> sides(n);
    rep(i, 0, n) {
        cin >> sides[i];
    }

    sort(all(sides));

    rep(i, 0, n-1) {
        if (sides[i] == sides[i+1]) {
            auto x = sides[i];
            sides.erase(begin(sides) + i);
            sides.erase(begin(sides) + i);

            rep(j, 0, n-3) {
                auto y = sides[j];
                auto z = sides[j+1];
                if (2 * x + y > z && 2 * x + z > y) {
                    cout << x << ' ' << x << ' ' << y << ' ' << z << '\n';
                    return;
                }
            }

            break;
        }
    }

    cout << "-1\n";
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
