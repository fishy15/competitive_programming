#include <iostream>
#include <vector>
#include <array>
#include <cstring>

#define ll long long
#define MOD 1000000007
#define MAXN 70

using namespace std;

struct M {
    static const int maxn = 60;
    ll m[maxn][maxn];
    M() { memset(m, 0, sizeof m); }
    M operator*(const M &m2) const {
        M res;
        for (int i = 0; i < maxn; i++) {
            for (int j = 0; j < maxn; j++) {
                for (int k = 0; k < maxn; k++) {
                    res[i][k] += m[i][j] * m2[j][k] % MOD;
                    if (res[i][j] >= MOD) res[i][j] -= MOD;
                }
            }
        }
        return res;
    }
    const ll *operator[](const int x) const { return m[x]; }
    ll *operator[](const int x) { return m[x]; }
    static M I() {
        M res;
        for (int i = 0; i < maxn; i++) res[i][i] = 1;
        return res;
    }
};

int n, k, q;
vector<array<int, 4>> qry;
M path, start;
int cur_bs = -1;
int cur_s = -1;

ll seq[1030][1030];
ll tot[1030][11];
ll len[1030][60];

void calc_num() {
    for (int t = 1; t < (1 << k); t++) {
        for (int mask = 1; mask < (1 << k); mask++) {
            int lsb = mask & (-mask);
            int prev = mask - (mask & (-mask));
            for (int m2 = 0; m2 < lsb; m2++) {
                seq[t][mask] += seq[t - 1][prev + m2];
            }
        }
    }

    for (int t = 0; t < (1 << k); t++) {
        for (int x = 0; x < k; x++) {
            for (int m = 0; m < (1 << k); m++) {
                if ((m & -m) == (1 << x)) {
                    tot[t][x] += seq[t][m];
                }
            }
        }
    }
}

void calc_path(int s) {
    for (int t = 0; t < (1 << k); t++) {
        for (int x = 0; x < n; x++) {
            len[t][x] = start[s][x];
        }
        start = start * path;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k >> q;

    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < n; j++) {
            if (s[j] == '1') {
                path[i][j]++;
            }
        }
    }

    while (q--) {
        int bs, s, bt, t;
        cin >> bs >> s >> bt >> t;
        s--; t--;
        bs--; bt--;
        if (s != cur_s || bs != cur_bs) {
            memset(seq, 0, sizeof seq);
            memset(tot, 0, sizeof tot);
            memset(len, 0, sizeof len);
            seq[0][1 << bs]++;
            start = M();
            start[s][s]++;
            calc_num();
            calc_path(s);
            cur_s = s;
            cur_bs = bs;
        }

        ll ans = 0;
        for (int cur = 0; cur < (1 << k); cur++) {
            ans += tot[cur][bt] * len[cur][t] % MOD;
            if (ans >= MOD) ans -= MOD;
        }

        cout << ans << '\n';
    }
}
