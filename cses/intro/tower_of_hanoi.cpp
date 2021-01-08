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

vector<pair<int, int>> moves[20][4][4];

vector<pair<int, int>> solve(int n, int start, int mid, int end) {
    if (n == 0) return {};
    if (moves[n][start][end].empty()) {
        for (auto p : solve(n - 1, start, end, mid)) moves[n][start][end].push_back(p);
        moves[n][start][end].push_back({start, end});
        for (auto p : solve(n - 1, mid, start, end)) moves[n][start][end].push_back(p);
    }
    return moves[n][start][end];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;

    auto v = solve(n, 1, 2, 3);
    cout << v.size() << '\n';
    for (auto p : v) {
        cout << p.first << ' ' << p.second << '\n';
    }

    return 0;
}
