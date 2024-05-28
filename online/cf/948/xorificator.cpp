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
#include <random>
#include <chrono>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

using u64 = unsigned long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

u64 randint() {
    return uniform_int_distribution(0ULL, -1ULL)(rng);
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (auto &row : grid) {
        cin >> row;
    }

    vector<u64> hsh(n);
    for (auto &x : hsh) {
        x = randint();
    }

    // hash -> {cnt, i, j that is set}
    map<u64, array<int, 3>> cnt;
    for (int j = 0; j < m; j++) {
        u64 all_zero = 0;
        for (int i = 0; i < n; i++) {
            if (grid[i][j] == '1') {
                all_zero ^= hsh[i];
            }
        }

        for (int i = 0; i < n; i++) {
            auto &entry = cnt[all_zero ^ hsh[i]];
            entry[0]++;
            entry[1] = i;
            entry[2] = j;
        }
    }

    array<int, 3> best{};
    for (auto [_, c] : cnt) {
        best = max(best, c);
    }

    auto [ans, bi, bj] = best;
    string str;
    for (int i = 0; i < n; i++) {
        if ((i == bi) == (grid[i][bj] == '0')) {
            str += '1';
        } else {
            str += '0';
        }
    }

    cout << ans << '\n';
    cout << str << '\n';
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
