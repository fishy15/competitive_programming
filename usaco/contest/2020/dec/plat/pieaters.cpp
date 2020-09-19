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
#define MAXN 305

using namespace std;

ll n, m;

// max answer between l to r
ll dp[MAXN][MAXN];
// max_eat[x][l][r] is max that eats x between l and r
ll max_eat[MAXN][MAXN][MAXN];

vector<array<ll, 3>> cows;

int main() {
    ifstream fin("pieaters.in");
    ofstream fout("pieaters.out");

    fin >> n >> m;
    for (ll i = 0; i < m; i++) {
        ll w, a, b; fin >> w >> a >> b;
        a--; b--;
        cows.push_back({w, a, b});
        for (ll i = a; i <= b; i++) {
            max_eat[i][a][b] = max(max_eat[i][a][b], w);
        }
    }

    for (ll sz = 1; sz < n; sz++) {
        for (ll a = 0; a < n; a++) {
            ll b = a + sz;
            if (b >= n) break;

            for (ll i = a; i <= b; i++) {
                max_eat[i][a][b] = max(max_eat[i][a][b], max_eat[i][a][b - 1]);
            }

            for (ll i = a; i <= b; i++) {
                max_eat[i][a][b] = max(max_eat[i][a][b], max_eat[i][a + 1][b]);
            }
        }
    }

    for (ll sz = 0; sz < n; sz++) {
        for (ll a = 0; a < n; a++) {
            ll b = a + sz;
            if (b >= n) break;

            for (ll i = a; i <= b; i++) {
                dp[a][b] = max(dp[a][b], dp[a][i] + dp[i + 1][b]);
            }

            for (ll i = a; i <= b; i++) {
                dp[a][b] = max(dp[a][b], dp[a][i - 1] + max_eat[i][a][b] + dp[i + 1][b]);
            }
        }
    }

    fout << dp[0][n - 1] << '\n';
    cout << dp[0][n - 1] << '\n';

    return 0;
}
