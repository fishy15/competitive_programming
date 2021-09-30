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

void solve() {
    int n; cin >> n;
    vector<string> grid(n);
    
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    pair<int, int> ans = {INF, 0};
    vector<int> row_one;
    for (int i = 0; i < n; i++) {
        bool has_o = false;
        int dot_cnt = 0;
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'O') {
                has_o = true;
                break;
            } else if (grid[i][j] == '.') {
                dot_cnt++;
            }
        }

        if (!has_o) {
            if (ans.first > dot_cnt) {
                ans.first = dot_cnt;
                ans.second = 1;
            } else if (ans.first == dot_cnt) {
                ans.second++;
            }

            if (dot_cnt == 1) {
                row_one.push_back(i);
            }
        }
    }

    vector<int> col_one;
    for (int j = 0; j < n; j++) {
        bool has_o = false;
        int dot_cnt = 0;
        for (int i = 0; i < n; i++) {
            if (grid[i][j] == 'O') {
                has_o = true;
                break;
            } else if (grid[i][j] == '.') {
                dot_cnt++;
            }
        }

        if (!has_o) {
            if (ans.first > dot_cnt) {
                ans.first = dot_cnt;
                ans.second = 1;
            } else if (ans.first == dot_cnt) {
                ans.second++;
            }

            if (dot_cnt == 1) {
                col_one.push_back(j);
            }
        }
    }

    if (ans.first == 1) {
        for (int i : row_one) {
            for (int j : col_one) {
                if (grid[i][j] == '.') {
                    ans.second--;
                    break;
                }
            }
        }
    }

    if (ans.first == INF) {
        cout << "Impossible\n";
    } else {
        cout << ans.first << ' ' << ans.second << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
