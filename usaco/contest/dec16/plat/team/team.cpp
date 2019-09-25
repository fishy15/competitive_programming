// :pray: :fishy:

#include <iostream>
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
#define MOD 1000000009

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000

using namespace std;

int n, m, k;
vector<ll> j;
vector<ll> p;
ll dp[MAXN + 1][MAXN + 1][11];

int main() {
    ifstream fin("team.in");
    ofstream fout("team.out");

    fin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        ll x; fin >> x; 
        j.push_back(x);
    }

    for (int i = 0; i < m; i++) {
        ll x; fin >> x;
        p.push_back(x);
    }

    dp[0][0][0] = 1;

    for (int a = 0; a <= k; a++) {
        for (int b = 0; b < n; b++) {
            for (int c = 0; c < m; c++) {
                if (a > 0 && j[b] > p[c]) {
                    dp[b + 1][c + 1][a] += dp[b][c][a - 1];
                }
            }
        }

        for (int b = 0; b <= n; b++) {
            for (int c = 0; c <= m; c++) {
                if (b > 0) {
                    dp[b][c][a] += dp[b - 1][c][a];
                }

                if (c > 0) {
                    dp[b][c][a] += dp[b][c - 1][a];
                }

                if (b > 0 && c > 0) {
                    dp[b][c][a] -= dp[b - 1][c - 1][a];
                }

                while (dp[b][c][a] < 0) {
                    dp[b][c][a] += MOD;
                }

                while (dp[b][c][a] > MOD) {
                    dp[b][c][a] -= MOD;
                }
            }
        }
    }

    fout << dp[n][m][k] << '\n';

    return 0;
}
