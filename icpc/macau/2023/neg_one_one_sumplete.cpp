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
#include <climits>

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

    int n;
    cin >> n;

    vector<string> grid(n);
    for (auto &row : grid) {
        cin >> row;
    }

    vector<int> r(n), c(n);
    for (auto &x : r) cin >> x;
    for (auto &x : c) cin >> x;

    vector<int> cur_r(n), cur_c(n);
    vector cur_grid(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '+') {
                cur_grid[i][j] = 1;
                cur_r[i]++;
                cur_c[j]++;
            }
        }
    }

    priority_queue<pair<int, int>> cols_left;
    for (int j = 0; j < n; j++) {
        int diff = cur_c[j] - c[j];
        if (diff < 0) {
            cout << "No\n";
            return 0;
        } else if (diff > 0) {
            cols_left.push({diff, j});
        }
    }

    for (int i = 0; i < n; i++) {
        int diff = cur_r[i] - r[i];
        if (diff < 0) {
            cout << "No\n";
            return 0;
        }

        vector<pair<int, int>> nxt;
        for (int a = 0; a < diff; a++) {
            if (cols_left.empty()) {
                cout << "No\n";
                return 0;
            }

            auto [cnt, j] = cols_left.top();
            cols_left.pop();

            cur_grid[i][j] ^= 1;
            cur_r[i]--;
            cur_c[j]--;
            
            if (cnt > 1) {
                nxt.push_back({cnt - 1, j});
            }
        }

        for (auto p : nxt) {
            cols_left.push(p);
        }
    }

    if (cur_r != r || cur_c != c) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << cur_grid[i][j];
            }
            cout << '\n';
        }
    }

    return 0;
}
