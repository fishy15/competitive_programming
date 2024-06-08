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

    ld a, b;
    cin >> a >> b;

    int n, x1, xn;
    cin >> n >> x1 >> xn;

    if (n == 2) {
        cout << x1 << '\n';
        cout << xn << '\n';
        return 0;
    }

    vector<pair<ld, ld>> contrib;
    contrib.push_back({1, 0});
    contrib.push_back({0, 1});

    for (int i = 0; i < n - 2; i++) {
        auto back1 = contrib.back();
        auto back2 = end(contrib)[-2];

        auto res = pair{
            back1.first * a + back2.first * b,
            back1.second * a + back2.second * b,
        };

        contrib.push_back(res);
    }

    ld x2 = xn;
    x2 -= contrib.back().first * x1;
    x2 /= contrib.back().second;

    cout << fixed << setprecision(16);

    cout << x1 << '\n';
    for (int i = 1; i < n-1; i++) {
        auto val = contrib[i].first * x1 + contrib[i].second * x2;
        cout << val << '\n';
    }
    cout << xn << '\n';

    return 0;
}
