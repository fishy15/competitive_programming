struct M {
    const static int n = 100;
    ll m[n][n];
    M() { memset(m, 0, sizeof m); }
    M operator*(const M &m2) {
        M res;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int a = 0; a < n; a++) {
                    res.m[i][j] += m[i][a] * m2[a][j];
                    if (res.m[i][j] >= MOD) res[i][j] %= MOD;
                }
            }
        }
        return res;
    }
    ll *operator[](const int &x) { return m[x]; }
    const ll *operator[](const int &x) const {return m[x]; }
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
        for (int i = 0; i < n; i++) m[i][i] = 1;
        return m;
    }
};
