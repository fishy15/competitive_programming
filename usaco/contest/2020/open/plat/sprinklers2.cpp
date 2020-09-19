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

int n;
string grid[MAXN];

ll top[MAXN][MAXN];
ll bottom[MAXN][MAXN];
ll open[MAXN];

ll modpow(ll n, ll e, ll m) {
    if (e == 0) return 1LL;
    if (e == 1) return n % m;
    ll res = modpow(n, e / 2, m);
    if (e % 2) {
        return (res * res % m) * n % m;
    }
    return res * res % m;
}

ll calc(int l, int r) {
    ll op = open[min(r, n - 1)];
    if (l > 0) {
        op -= open[max(0, l - 1)];
    }
    if (op <= 1) return 0;
    return modpow(2, op - 2, MOD);
}

int main() {
    ifstream fin("sprinklers2.in");
    ofstream fout("sprinklers2.out");

    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> grid[i];
    }

    for (int i = 0; i < n; i++) {
        if (grid[0][i] == '.') open[0]++;
    }

    for (int i = 1; i < n; i++) {
        open[i] += open[i - 1];
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '.') open[i]++;
        }
    }

    ll ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        // there are no As in this row
        if (grid[i][n - 1] == '.') {
            ll v = open[n - 1];
            if (i > 0) v -= open[i - 1];
            top[i][n - 1] += modpow(2, v - 1, MOD);
            if (top[i][n - 1] >= MOD) top[i][n - 1] -= MOD;
        }

        // there is a c
        for (int c = 0; c < n; c++) {
            if (grid[i][c] == '.' || n < 5) {
                for (int h = i; h < n; h++) {
                    if (grid[h][c + 1] == '.') {
                        if (h == n - 1) top[i][c] += modpow(2, open[h] - open[i - 1] - 2, MOD);
                        else top[i][c] += top[h + 1][c + 1] * calc(i, h) % MOD;
                        if (top[i][c] >= MOD) top[i][c] -= MOD;
                    }
                }
            }
        }

        // there are no Cs in this row
        if (grid[i][0] == '.') {
            ll v = 1;
            if (i < n - 1) {
                if (grid[i + 1][n - 1] == '.') v = top[i + 1][0];
                else v = 0;
            }
            v *= modpow(2, open[i] - 1, MOD);
            v %= MOD;
            ans += v;
            if (ans >= MOD) ans -= MOD;
        }
        
        // sum up tops in row
        for (int j = n - 2; j >= 0; j--) {
            top[i][j] += top[i][j + 1];
            if (top[i][j] >= MOD) top[i][j] -= MOD;
        }
    }

    ans += top[0][0];
    if (ans >= MOD) ans -= MOD;

    fout << ans << '\n';

    return 0;
}
