/*
 * We can solve the problem using divide and conquer (similar idea to CDQ D&C). Suppose we are trying to 
 * solve all the a query within [L, R] that is in both [L, M] and [M + 1, R]. We can use an O(NK) algorithm
 * to calculate mat[i][x][y] for i in [L, M], which represents the number of nondecreasing subsequences with
 * a lower bound of x, a higher bound of y, and all the elements are in [i, M]. We can also calculate 
 * mat[i][x][y] for i in [M + 1, R], which represents the number of nondecreasing subsequences with
 * a lower bound of x, a higher bound of y, and contained within [M + 1, i]. We just need to pick the 
 * appropriate matrices and combine them to answer the query. For the queries that aren't in both halves,
 * we can solve them in their respective halves. Overall, there are log N levels, so the total time 
 * complexity is O(NK^2 log N + QK^2).
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
#define MAXN 50010
#define MAXQ 200010

using namespace std;

struct mi {
    int v;
    mi() : v(0) {};
    mi(int k) : v(k % MOD) {};
    mi operator+=(const mi &m2) {
        v += m2.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    mi operator-=(const mi &m2) {
        v -= m2.v;
        if (v < 0) v += MOD;
        return *this;
    }
    mi operator*(const mi &m2) {
        return mi((ll) v * m2.v % MOD);
    }
};

int n, k, q;
vector<array<int, 3>> qry;
int nums[MAXN];
mi ans[MAXQ];
mi combo[MAXN][22][22];

void calc_before(int l, int r) {
    for (int i = 0; i <= k + 1; i++) {
        for (int j = 0; j <= k + 1; j++) {
            combo[r][i][j] = 0;
        }
    }

    combo[r][0][0] = 1;
    combo[r][0][nums[r]] = 1;
    combo[r][0][k + 1] = 1; // does not include empty
    combo[r][nums[r]][nums[r]] = 1;
    combo[r][nums[r]][k + 1] = 1;
    combo[r][k + 1][k + 1] = 1;

    for (int i = r - 1; i >= l; i--) {
        for (int a = 0; a <= k + 1; a++) {
            for (int b = 0; b <= k + 1; b++) {
                combo[i][a][b] = combo[i + 1][a][b];
            }
        }

        // solve for combo[i][nums[i]][j]
        for (int j = nums[i]; j <= k + 1; j++) {
            for (int a = nums[i]; a <= j; a++) {
                combo[i][nums[i]][j] += combo[i + 1][a][j];
                combo[i][0][j] += combo[i + 1][a][j];
            }
        }

        combo[i][nums[i]][nums[i]] += 1;
        combo[i][0][nums[i]] += 1;
    }
}

void calc_after(int l, int r) {
    for (int i = 0; i <= k + 1; i++) {
        for (int j = 0; j <= k + 1; j++) {
            combo[l][i][j] = 0;
        }
    }

    combo[l][0][0] = 1;
    combo[l][0][nums[l]] = 1;
    combo[l][0][k + 1] = 1; // does not include empty
    combo[l][nums[l]][nums[l]] = 1;
    combo[l][nums[l]][k + 1] = 1;
    combo[l][k + 1][k + 1] = 1;

    for (int i = l + 1; i <= r; i++) {
        for (int a = 0; a <= k + 1; a++) {
            for (int b = 0; b <= k + 1; b++) {
                combo[i][a][b] = combo[i - 1][a][b];
            }
        }

        for (int j = 0; j <= nums[i]; j++) {
            for (int a = j; a <= nums[i]; a++) {
                combo[i][j][nums[i]] += combo[i - 1][j][a];
                combo[i][j][k + 1] += combo[i - 1][j][a];
            }
        }

        combo[i][nums[i]][nums[i]] += 1;
        combo[i][nums[i]][k + 1] += 1;
    }
}

void solve(int l, int r, const vector<array<int, 3>> &cur) {
    vector<array<int, 3>> before;
    vector<array<int, 3>> after;

    if (l == r) {
        for (auto &arr : cur) {
            ans[arr[2]] = 2;
        }
        return;
    }

    int m = (l + r) / 2;
    calc_before(l, m);
    calc_after(m + 1, r);
    for (auto arr : cur) {
        if (arr[1] <= m) {
            before.push_back(arr);
        } else if (arr[0] > m) {
            after.push_back(arr);
        } else {
            mi cur;
            for (int i = 0; i <= k + 1; i++) {
                if (1 <= i && i <= k) {
                    cur += combo[arr[0]][0][i];
                    ans[arr[2]] += cur * combo[arr[1]][i][k + 1];
                } else {
                    ans[arr[2]] += combo[arr[0]][0][i] * combo[arr[1]][i][k + 1];
                }
            }
            ans[arr[2]] += 1;
        }
    }

    if (!before.empty()) {
        solve(l, m, before);
    } 

    if (!after.empty()) {
        solve(m + 1, r, after);
    }
}

int main() {
    ifstream fin("nondec.in");
    ofstream fout("nondec.out");

    fin >> n >> k;
    for (int i = 0; i < n; i++) {
        fin >> nums[i];
    }
    
    fin >> q;
    for (int i = 0; i < q; i++) {
        int l, r; fin >> l >> r;
        l--; r--;
        qry.push_back({l, r, i});
    }

    solve(0, n - 1, qry);

    for (int i = 0; i < q; i++) {
        fout << ans[i].v << '\n';
    }

    return 0;
}
