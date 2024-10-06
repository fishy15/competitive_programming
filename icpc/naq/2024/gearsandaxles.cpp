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

    int n;
    cin >> n;

    map<int, vector<int>> at_size;
    rep(i, 0, n) {
        int s, c;
        cin >> s >> c;
        at_size[s].push_back(c);
    }

    ld ans = 0;
    for (auto &[_, v] : at_size) {
        sort(all(v));
        auto s = sz(v);
        rep(i, 0, s / 2) {
            ans += log(v[s - i - 1]) - log(v[i]);
        }
    }

    cout << fixed << setprecision(10);
    cout << ans << '\n';

    return 0;
}
