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
#include <cstring>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct M {
    const static int n = 6;
    ll m[n][n];
    M() { memset(m, 0, sizeof m); }
    M operator*(const M& m2) {
        M res;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int a = 0; a < n; a++) {
                    res.m[i][j] += m[i][a] * m2.m[a][j];
                    if (res.m[i][j] >= MOD) res.m[i][j] %= MOD;
                }
            }
        }
        return res;
    }
    ll* operator[](const int &x) { return m[x]; }
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
        for (int i = 0; i < n; i++) m.m[i][i] = 1;
        return m;
    }
};

ll n;
int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    M m, st;
    st[0][0] = 1;
    for (int i = 0; i < 6; i++) {
        m[0][i] = 1;
    }
    for (int i = 1; i < 6; i++) {
        m[i][i - 1] = 1;
    }

    m = M::pow(m, n) * st;
    cout << m[0][0] << '\n';

    return 0;
}
