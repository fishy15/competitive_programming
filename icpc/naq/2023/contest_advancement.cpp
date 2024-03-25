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

    int n, k, c;
    cin >> n >> k >> c;

    vector<pair<int, int>> t(n);
    for (auto &[x, y] : t) {
        cin >> x >> y;
        x--;
        y--;
    }

    vector<int> added_s(n);
    set<array<int, 2>> wins;

    for (int i = 0; i < n; i++) {
        if ((int) wins.size() == k) break;
        if (added_s[t[i].second] < c) {
            added_s[t[i].second]++;
            wins.insert({i, t[i].first});
        }
    }

    for (int i = 0; i < n; i++) {
        if ((int) wins.size() == k) break;
        wins.insert({i, t[i].first});
    }

    for (auto [_, x] : wins) {
        cout << x + 1 << '\n';
    }

    return 0;
}
