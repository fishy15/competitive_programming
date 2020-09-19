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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1005

using namespace std;

int n, k;
int nums[MAXN];
ll dp[MAXN][MAXN][20][20];

ll query(int l, int r, int lo, int hi) {
    if (r < l || hi < lo) {
        return 0;
    }

    if (dp[l][r][lo][hi] != -1) {
        return dp[l][r][lo][hi];
    }

    ll res = 0;
    if (l == r) {
        if (lo <= nums[l] && nums[r] <= hi) {
            res = 1;
        }
    } else {
        if (nums[l] == lo) {
            for (int i = lo; i <= hi; i++) {
                res += query(l + 1, r, i, hi);
                if (res > MOD) res -= MOD;
            }
        }

        if (nums[r] == hi) {
            for (int i = lo; i <= hi; i++) {
                res += query(l + 1, r, lo, i);
                if (res > MOD) res -= MOD;
            }
        }

        if (nums[l] == lo && nums[r] == hi) {
            for (int i = lo; i <= hi; i++) {
                for (int j = i; j <= hi; j++) {
                    res -= query(l + 1, r - 1, i, j);
                    if (res < 0) res += MOD;
                }
            }
        }
    }

    return dp[l][r][lo][hi] = res;
}

int main() {
    ifstream fin("nondec.in");
    ofstream fout("nondec.out");

    fin >> n >> k;

    for (int i = 0; i < n; i++) {
        fin >> nums[i];
        nums[i]--;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int a = 0; a < 20; a++) {
                for (int b = 0; b < 20; b++) {
                    dp[i][j][a][b] = -1;
                }
            }
        }
    }

    int q; fin >> q;
    for (int i = 0; i < q; i++) {
        int l, r; fin >> l >> r;
        ll ans = 0;
        for (int lo = 0; lo < 20; lo++) {
            for (int hi = lo; hi < 20; hi++) {
                ans += query(l - 1, r - 1, lo, hi);
                if (ans > MOD) ans -= MOD;
            }
        }

        fout << ans << '\n';
    }

    return 0;
}
