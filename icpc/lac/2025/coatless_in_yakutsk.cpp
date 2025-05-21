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

    int c, n;
    cin >> c >> n;

    vector<int> temp(n);
    rep(i, 0, n) {
        cin >> temp[i];
    }

    auto check = [&](int t) {
        int cur = 0;
        rep(i, 0, n) {
            if (temp[i] < t) {
                cur++;
                if (cur > c) {
                    return false;
                }
            } else {
                cur = 0;
            }
        }

        return true;
    };

    int l = -50;
    int r = 50;
    int ans = 50;
    while (l <= r) {
        int m = (l + r) / 2;
        if (check(m)) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    cout << ans << '\n';

    return 0;
}
