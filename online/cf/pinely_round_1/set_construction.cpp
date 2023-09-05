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

// change if necessary
#define MAXN 1000000

using namespace std;

template<int len = 1>
void solve(int n) {
    if (n > len) {
        solve<std::min(2*len, 100)>(n);
        return;
    }

    vector<string> grid(n);
    for (auto &s : grid) {
        cin >> s;
    }

    vector<vector<int>> child(n);
    vector<int> deg(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '1') {
                child[i].push_back(j);
                deg[j]++;
            }
        }
    }

    vector<bitset<len>> in_set(n);
    for (int i = 0; i < n; i++) {
        in_set[i][i] = 1;
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        auto t = q.front();
        q.pop();

        for (int x : child[t]) {
            in_set[x] |= in_set[t];
            deg[x]--;
            if (deg[x] == 0) {
                q.push(x);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        vector<int> all_set;
        for (int j = 0; j < n; j++) {
            if (in_set[i][j]) {
                all_set.push_back(j);
            }
        }

        cout << all_set.size() << ' ';
        for (auto x : all_set) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
    }
}

void solve() {
    int n;
    cin >> n;
    solve(n);
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
