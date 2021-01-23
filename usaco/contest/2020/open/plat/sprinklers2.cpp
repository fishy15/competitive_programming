/*
 * The boundary between the two different colors must be a line that only goes down and right from the
 * top left to the bottom right corner. For each edge in the grid, we can represent two arrays that count
 * the number of paths that go along that edge so far and work our way down. Because using a . square to
 * change from horizontal to vertical means that the color on that square will be fixed, so we multiply
 * by 1/2. At the end, we multiply by 2^(# of . squares) to get the answer.
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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 2010

using namespace std;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(ll v) : v(v) {}
    mi &operator+=(const mi &m2) {
        v += m2.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    mi operator+(const mi &m2) {
        mi m(v);
        return m += m2;
    }
    mi &operator*=(const mi &m2) {
        v = (ll)v * m2.v % MOD;
        return *this;
    }
    mi operator*(const mi &m2) {
        mi m(v);
        return m *= m2;
    }
    mi pow(int e) {
        mi res = 1;
        mi cur = *this;
        while (e) {
            if (e & 1) res *= cur;
            cur *= cur;
            e >>= 1;
        }
        return res;
    }
    mi inv() {
        return this->pow(MOD - 2);
    }
};

int n;
string grid[MAXN];
mi rsum[MAXN][MAXN];
mi csum[MAXN][MAXN];
mi inv2 = mi(2).inv();
int cnt;

int main() {
    ifstream fin("sprinklers2.in");
    ofstream fout("sprinklers2.out");

    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> grid[i];
    }

    for (int i = 0; i <= n + 1; i++) {
        rsum[0][i] = 1;
        csum[i][0] = 1;
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            int ni = i + 1;
            int nj = j + 1;
            if (i < n && j < n && grid[i][j] == '.') { 
                cnt++;
                csum[ni][nj] += rsum[ni - 1][nj] * inv2;
                rsum[ni][nj] += csum[ni][nj - 1] * inv2;
            }
            rsum[ni][nj] += rsum[ni][nj - 1];
            csum[ni][nj] += csum[ni - 1][nj];
        }
    }

    mi ans = rsum[n][n] + csum[n][n];
    fout << (ans * mi(2).pow(cnt)).v << '\n';

    return 0;
}
