/*
 * We can use a matrix, where each shop is represented twice: once for what we can travel in 1 unit of time,
 * and once for what we can travel in 2 units of time. Since calculating this overcounts the paths that
 * do not include all of the shops, we need to subtract them out using PIE (first removing the ones that 
 * miss a single shop, then adding back the ones that miss two shops, etc).
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
#define MOD 5557

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n, m, t;
int stop = 51;
vector<array<int, 3>> edge;

struct M {
    const static int n = 52;
    short m[n][n];
    M() { memset(m, 0, sizeof m); }
    M operator*(const M &m2) {
        M res;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int a = 0; a < n; a++) {
                    short &cur = res.m[i][j];
                    cur += (int) m[i][a] * m2.m[a][j] % MOD;
                    if (cur >= MOD) cur -= MOD;
                }
            }
        }
        return res;
    }
    static M pow(M &m, ll e) {
        M res = I();
        while (e) {
            if (e & 1) res = res * m;
            m = m * m;
            e >>= 1;
        }
        return res;
    }
    static M I() {
        M m;
        for (int i = 0; i < n; i++) {
            m.m[i][i] = 1;
        }
        return m;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        string ok; cin >> ok;

        int mask = 0;
        if (ok.find('B') != string::npos) mask += 1;
        if (ok.find('J') != string::npos) mask += 2;
        if (ok.find('M') != string::npos) mask += 4;
        if (ok.find('P') != string::npos) mask += 8;

        edge.push_back({a, b, mask});
    }

    cin >> t;

    ll ans = 0;
    for (int mm = 0; mm < 16; mm++) {
        int mul = 1;
        if (!(mm & 1)) mul *= -1;
        if (!(mm & 2)) mul *= -1;
        if (!(mm & 4)) mul *= -1;
        if (!(mm & 8)) mul *= -1;

        M mat, start;
        for (const auto &[a, b, mask] : edge) {
            // don't visit shop
            mat.m[2 * a + 1][2 * b + 1]++;
            if (b == 0) {
                mat.m[2 * a + 1][stop]++;
            }

            // visit shop
            if ((mask | mm) == mm) {
                mat.m[2 * a][2 * b + 1]++;
                if (b == 0) {
                    mat.m[2 * a][stop]++;
                }
            }
        }


        // copy values from t=2 to t=1
        for (int i = 0; i < n; i++) {
            mat.m[2 * i + 1][2 * i]++;
        }

        // keep circulating
        mat.m[stop][stop]++;

        start.m[1][1]++;

        M res = start * M::pow(mat, t);
        ans += res.m[1][stop] * mul;
        if (ans >= MOD) ans -= MOD;
        if (ans < 0) ans += MOD;
    }

    cout << ans << '\n';

    return 0;
}
