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
#define MOD 12345

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct M {
    const static int n = 123;
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

ll n, c;
vector<int> cond[30];
int prod[30];
int prod2[30];
int tot = 1;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> c;
    for (int i = 0; i < c; i++) {
        char t; int m; cin >> t >> m;
        cond[t - 'A'].push_back(m);
    }

    for (int i = 0; i < 26; i++) {
        if (!cond[i].empty()) {
            prod[i] = tot;
            for (int j : cond[i]) tot *= j;
            prod2[i] = tot;
        }
    }
    M m;
    for (int i = 0; i < tot; i++) {
        for (int j = 0; j < 26; j++) {
            if (prod[j]) {
                int nxt = (i + prod[j]) % prod2[j] + i / prod2[j] * prod2[j];
                m[i][nxt]++;
            }
        }
    }

    m = M::pow(m, n);
    ll ans = 0;
    for (int i = 0; i < tot; i++) {
        bool works = true;
        for (int j = 0; j < 26; j++) {
            if (prod[j]) {
                int val = (i % prod2[j]) / prod[j];
                bool any = false;
                for (int k : cond[j]) {
                    if (val % k == 0) {
                        any = true;
                        break;
                    }
                }
                if (!any) {
                    works = false; 
                    break;
                }
            }
        }
        if (works) {
            ans += m[0][i];
            if (ans >= MOD) ans -= MOD;
        }
    }
    cout << ans << '\n';

    return 0;
}
