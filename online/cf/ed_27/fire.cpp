/*
 * We can binary search on the time. For some time t, we can use sweepline to figure out the lowest x value 
 * and lowest y value that aren't contained in a square. The new square that we add must contain these
 * points, so we add another one centered at (x + t, y + t) and check again if everything is contained.
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

int n, m, k;
vector<pair<int, int>> start;

int bad_y(map<int, int> loc) {
    int cur = 0;
    for (auto p : loc) {
        cur += p.second;
        if (p.first > 0 && p.first <= m && cur <= 0) {
            return p.first;
        }
    }
    return -1;
}

pair<int, int> bad(map<int, vector<array<int, 3>>> proc) {
    map<int, int> m;
    m[1] = 0; // mark we need to check 1
    m[::m] = 0; // mark we need to check m

    int badx = INF;
    int bady = INF;
    for (auto &p : proc) {
        for (auto &arr : p.second) {
            m[arr[0]] += arr[2];
            m[arr[1] + 1] -= arr[2];
        }
        if (p.first > 0 && p.first <= n) {
            int res = bad_y(m);
            if (res != -1) {
                badx = min(badx, p.first);
                bady = min(bady, res);
            }
        }
    }
    if (badx == INF) return {-1, -1};
    return {badx, bady};
}

bool check(int x) {
    map<int, vector<array<int, 3>>> m;

    m[1] = {}; // mark we need to check 1
    m[n] = {}; // mark we need to check n
    for (int i = 0; i < k; i++) {
        m[start[i].first - x].push_back({start[i].second - x, start[i].second + x, 1});
        m[start[i].first + x + 1].push_back({start[i].second - x, start[i].second + x, -1});
    }

    auto res = bad(m);
    if (res.first != -1) {
        m[res.first].push_back({res.second, res.second + 2 * x, 1});
        m[res.first + 2 * x + 1].push_back({res.second, res.second + 2 * x, -1});
        res = bad(m);
        return res.first == -1;
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> k;

    for (int i = 0; i < k; i++) {
        int x, y; cin >> x >> y;
        start.push_back({x, y});
    }

    int l = 0;
    int r = max(n, m);
    int ans = -1;

    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            r = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }

    cout << ans << '\n'; 

    return 0;
}
