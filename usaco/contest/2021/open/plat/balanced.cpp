#include <iostream>
#include <string>

#define ll long long
#define MOD 1000000007
#define MAXN 160

using namespace std;

struct mi {
    ll v;
    mi() : mi(0) {}
    mi(int v) : v(v) {}

    mi &operator+=(const mi &m2) {
        v += m2.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }

    mi operator+(const mi &m2) const {
        mi m = *this;
        return m += m2;
    }

    mi &operator*=(const mi &m2) {
        v = (ll) v * m2.v % MOD;
        return *this;
    }

    mi operator*(const mi &m2) const {
        mi m = *this;
        return m *= m2;
    }
};

int n;
string grid[MAXN];
mi dp[MAXN][MAXN][MAXN][4];

int pre[MAXN][MAXN];

bool contains(int col, int x, int y) {
    if (x < y) swap(x, y);
    int sum = pre[col + 1][x + 1] - pre[col + 1][y] - pre[col][x + 1] + pre[col][y];
    return sum > 0;
}

mi get_none(int i, int j, int k) {
    mi ans = 0;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
           if (j <= x && y <= k) {
                ans += dp[i - 1][x][y][0];
            }
        }
    }
    return ans;
}

mi get_top(int i, int j, int k) {
    mi ans = 0;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (x < j && (j <= y && y <= k)) {
                ans += dp[i - 1][x][y][0];
                ans += dp[i - 1][x][y][1];
            }
        }
    }
    ans += dp[i - 1][j][k][1];
    return ans;
}

mi get_bot(int i, int j, int k) {
    mi ans = 0;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if ((j <= x && x <= k) && y > k) {
                ans += dp[i - 1][x][y][0];
                ans += dp[i - 1][x][y][2];
            }
        }
    }
    ans += dp[i - 1][j][k][2];
    return ans;
}

mi get_both(int i, int j, int k) {
    mi ans = 0;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (x < j && y > k) {
                ans += dp[i - 1][x][y][0];
                ans += dp[i - 1][x][y][1];
                ans += dp[i - 1][x][y][2];
                ans += dp[i - 1][x][y][3];
            } else if (x == j && y > k) {
                ans += dp[i - 1][x][y][1];
                ans += dp[i - 1][x][y][3];
            } else if (x < j && y == k) {
                ans += dp[i - 1][x][y][2];
                ans += dp[i - 1][x][y][3];
            } else if (x == j && y == k) {
                ans += dp[i - 1][x][y][3];
            }
        }
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '.') {
                pre[i + 1][j + 1]++;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            pre[i][j] += pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
        }
    }

    mi ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = j; k < n; k++) {
                if (contains(i, j, k)) continue;

                dp[i][j][k][0] = 1;
                if (i) {
                    dp[i][j][k][0] += get_none(i, j, k);
                    dp[i][j][k][1] += get_top(i, j, k);
                    dp[i][j][k][2] += get_bot(i, j, k);
                    dp[i][j][k][3] += get_both(i, j, k);
                }

                for (int z = 0; z < 4; z++) {
                    ans += dp[i][j][k][z];
                }
            }
        }
    }

    cout << ans.v << '\n';

    return 0;
}
