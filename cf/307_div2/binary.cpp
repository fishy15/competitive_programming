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
#define MAXN 1000000

using namespace std;

ll n, k, l, m;
ll dp[MAXN + 1];

ll modpow(ll n, ll e, ll m) {
    if (e == 0) return 1LL;
    if (e == 1) return n % m;
    ll res = modpow(n, e / 2, m);
    if (e % 2) {
        return (res * res % m) * n % m;
    }
    return res * res % m;
}

vector<vector<ll>> matrix_mult(vector<vector<ll>> m1, vector<vector<ll>> m2) {
    vector<vector<ll>> ans;

    for (ll i = 0; i < m1.size(); i++) {
        vector<ll> row;
        for (ll j = 0; j < m2[0].size(); j++) {
            ll sum = 0;
            for (ll a = 0; a < m1[0].size(); a++) {
                sum += m1[i][a] * m2[a][j];

                // include if mod is necessary
                sum %= m;
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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k >> l >> m;
    if (l < 64 && k >= (1ULL << l)) {
        cout << "0\n";
        return 0;
    }

    vector<vector<ll>> start = {{1, 0}};
    vector<vector<ll>> mm = {{1, 1}, {1, 0}};
    mm = matrix_expo(mm, n + 2);
    start = matrix_mult(start, mm);
    
    ll bad = start[0][1]; 
    ll good = modpow(2LL, n, m) - bad;
    if (good < 0) good += m;
    ll ans = 1;

    for (int i = 0; i < l; i++) {
        if ((1LL << i) & k) {
            ans *= good;
            ans %= m;
        } else {
            ans *= bad;
            ans %= m;
        }
    }

    cout << ans % m << '\n';

    return 0;
}
