vector<vector<ll>> matrix_mult(vector<vector<ll>> m1, vector<vector<ll>> m2) {
    vector<vector<ll>> ans;

    for (ll i = 0; i < m1.size(); i++) {
        vector<ll> row;
        for (ll j = 0; j < m2[0].size(); j++) {
            ll sum = 0;
            for (ll a = 0; a < m1[0].size(); a++) {
                sum += m1[i][a] * m2[a][j];

                // include if mod is necessary
                if (sum > MOD) {
                    sum -= MOD;
                }
            }
            
            row.push_back(sum);
        }

        ans.push_back(row);
    }

    return ans;
}

vector<vector<ll>> matrix_expo(vector<vector<ll>> m, ll n) {
    if (n == 1) {
        return m;
    }

    vector<vector<ll>> temp = matrix_expo(m, n / 2);

    if (n % 2 == 0) {
        return matrix_mult(temp, temp);
    }

    return matrix_mult(matrix_mult(temp, temp), m);
}
