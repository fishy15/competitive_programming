#pragma GCC target("popcnt")

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
#include <bitset>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

using namespace std;

constexpr int MAXN = 3000;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<bitset<MAXN>> grid;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;

        grid.emplace_back();
        for (int j = 0; j < n; j++) {
            grid.back()[j] = (s[j] == '1');
        }
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ll total = (grid[i] & grid[j]).count();
            ans += total * (total - 1) / 2;
        }
    }

    cout << ans << '\n';

    return 0;
}
