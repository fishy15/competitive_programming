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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

constexpr int MAXN = 300;

vector<vector<int>> compute_states() {
    vector res(MAXN, vector(MAXN, -1));
    rep(i, 0, MAXN) {
        rep(j, 0, MAXN) {
            if (abs(i - j) <= 1) {
                continue;
            }

            vector<int> reachable;
            rep(i2, 0, i) {
                auto v = res[i2][j];
                if (v != -1) {
                    reachable.push_back(v);
                }
            }
            rep(j2, 0, j) {
                auto v = res[i][j2];
                if (v != -1) {
                    reachable.push_back(v);
                }
            }
            sort(all(reachable));
            int mex = 0;
            for (auto x : reachable) {
                if (mex == x) {
                    mex++;
                }
            }
            res[i][j] = mex;
        }
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    auto state = compute_states();

    int t;
    cin >> t;

    auto is_winning = [&](int x1, int y1, int x2, int y2) {
        if (abs(x1 - x2) + abs(y1 - y2) == 1) {
            return false;
        } else if (abs(x1 - x2) <= 1 || abs(y1 - y2) <= 1) {
            return true;
        } else {
            return (state[x1][x2] ^ state[y1][y2]) != 0;
        }
    };

    while (t--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--;
        y1--;
        x2--;
        y2--;

        int cnt = 0;
        for (int x = x1-1; x >= 0; x--) {
            if (x == x2 && y1 == y2) break;
            if (!is_winning(x, y1, x2, y2)) {
                cnt++; 
            }
        }
        for (int x = x2-1; x >= 0; x--) {
            if (x1 == x && y1 == y2) break;
            if (!is_winning(x1, y1, x, y2)) {
                cnt++; 
            }
        }
        for (int y = y1-1; y >= 0; y--) {
            if (x1 == x2 && y == y2) break;
            if (!is_winning(x1, y, x2, y2)) {
                cnt++; 
            }
        }
        for (int y = y2-1; y >= 0; y--) {
            if (x1 == x2 && y1 == y) break;
            if (!is_winning(x1, y1, x2, y)) {
                cnt++; 
            }
        }
        cout << cnt << '\n';
    }

    return 0;
}
