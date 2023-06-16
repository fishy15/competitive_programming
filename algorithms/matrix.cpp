struct M {
    const static int n = 20;
    mi m[n][n]; 
    M operator*(const M &m2) {
        M res;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int a = 0; a < n; a++) {
                    res[i][j] += m[i][a] * m2[a][j];
                }
            }
        }
        return res;
    }
    mi *operator[](const int x) { return m[x]; }
    const mi *operator[](const int x) const { return m[x]; }
    static M pow(M m, ll e) {
        M res = I();
        while (e > 0) {
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
