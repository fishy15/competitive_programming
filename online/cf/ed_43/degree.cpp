/*
 * We can build the graph recursively. If n = 0, then the graph is a single point. If n = 1, then we form a 
 * completely connected graph with d_1 + 1 points. Otherwise, we can build (d_1, d_2, ..., d_n) from 
 * (d_2 - d_1, d_3 - d_1, ..., d_n-1 - d_1). To this graph, we can add d_n - d_n-1 points that are not
 * connected to the original graph and then d_1 points that are connected to everything (including the
 * newly added points). Each degree in the old graph increases by d_1, the first set of points added have 
 * a degree of d_1, the second set of points added have a degree of d_n, and there will be d_n + 1 points
 * inductively.
 */

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
#define MAXN 1000000

using namespace std;

int n, sz;
int nums[MAXN];
vector<pair<int, int>> ans;

void solve(int l, int r, int sub) {
    if (l >= r) {
        sz++;
    } else if (r - l == 1) {
        for (int i = 0; i < nums[l] - sub + 1; i++) {
            for (int j = i + 1; j < nums[l] - sub + 1; j++) {
                ans.push_back({i, j});
            }
        }
        sz += nums[l] - sub + 1;
    } else {
        solve(l + 1, r - 1, nums[l]);
        sz += nums[r - 1] - nums[r - 2];
        for (int i = 0; i < nums[l] - sub; i++) {
            for (int j = 0; j < sz; j++) {
                ans.push_back({j, sz});
            }
            sz++;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    solve(0, n, 0);

    cout << ans.size() << '\n';
    for (auto [x, y] : ans) {
        cout << x + 1 << ' ' << y + 1 << '\n';
    }

    return 0;
}
