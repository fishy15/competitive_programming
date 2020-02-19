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

ll n, k;
vector<vector<ll>> grid;

vector<vector<ll>> matrix_mult(vector<vector<ll>> m1, vector<vector<ll>> m2) {
    vector<vector<ll>> ans;

    for (ll i = 0; i < m1.size(); i++) {
        vector<ll> row;
        for (ll j = 0; j < m2[0].size(); j++) {
            ll sum = 0;
            for (ll a = 0; a < m1[0].size(); a++) {
                sum += m1[i][a] * m2[a][j];

                // include if mod is necessary
                sum %= MOD;
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

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        grid.push_back(vector<ll>());
        for (int j = 0; j < n; j++) {
            int x; cin >> x;
            grid[i].push_back(x);
        }
    }

    auto res = matrix_expo(grid, k);
    ll ans = 0;

    for (auto v : res) {
        for (auto x : v) {
            ans += x;
            if (ans > MOD) ans -= MOD;
        }
    }

    cout << ans << '\n';

    return 0;
}
