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
#define MAXN 200010

using namespace std;

int n;
vector<int> pts;
array<int, 3> pos[MAXN];
ll dp[2 * MAXN];
vector<array<int, 3>> proc[2 * MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> pos[i][0] >> pos[i][1] >> pos[i][2];
        pts.push_back(pos[i][0]);
        pts.push_back(pos[i][1]);
    }

    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    auto idx = [&](int x) { return lower_bound(pts.begin(), pts.end(), x) - pts.begin() + 1; };

    for (int i = 0; i < n; i++) {
        pos[i][0] = idx(pos[i][0]);
        pos[i][1] = idx(pos[i][1]);
        proc[pos[i][1]].push_back(pos[i]);
    }

    for (int i = 1; i <= (int)(pts.size()); i++) {
        dp[i] = dp[i - 1];
        for (auto &p : proc[i]) {
            dp[i] = max(dp[i], dp[p[0] - 1] + p[2]);
        }
    }

    cout << dp[pts.size()] << '\n';

    return 0;
}
