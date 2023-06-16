/*
 * Let dp[a][b][x] represent the number of paths from a to b that use a max button value of x. We can then
 * combine dp[a][b][x] to dp[c][d][x] by pressing button x + 1 on some node that connects b to c. To 
 * transition from x to x + 1, we can loop over the middle node and calculate arrays before and after, where
 * before[i] is the number of paths from i to the middle node, and after[i] is the number of paths from the
 * middle node to i. We then can add dp[a][b][x + 1] += before[a] * after[b]. We can answer the queries
 * by representing the starting value {s, bs} by a node that connects to s only if x == bs (and similarly 
 * for the end).
 */

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
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct mi {
    int v;
    mi(int v = 0) : v(v) {}
    mi &operator+=(const mi &m2) {
        v += m2.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    mi operator+(const mi &m2) {
        mi m(v);
        return m += m2;
    }
    mi &operator*=(const mi &m2) {
        v = (ll)v * m2.v % MOD;
        return *this;
    }
    mi operator*(const mi &m2) {
        mi m(v);
        return m *= m2;
    }
};

int n, k, q;
pair<int, int> in_val[120];
pair<int, int> out_val[120];
mi dp[120][120][60];
bool adj[60][60];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k >> q;

    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < n; j++) {
            adj[i][j] = (s[j] == '1');
        }
    }

    for (int i = 0; i < n; i++) {
        in_val[i] = {i, -1};
        out_val[i] = {i, -1};
    }

    for (int i = 0; i < q; i++) {
        cin >> in_val[n + i].second >> in_val[n + i].first;
        cin >> out_val[n + i].second >> out_val[n + i].first;
        in_val[n + i].first--;
        in_val[n + i].second--;
        out_val[n + i].first--;
        out_val[n + i].second--;
    }

    for (int x = 0; x < k; x++) {
        // copy values 
        if (x) {
            for (int i = 0; i < n + q; i++) {
                for (int j = 0; j < n + q; j++) {
                    dp[i][j][x] += dp[i][j][x - 1];
                }
            }
        }

        // transition w/ value in the middle
        for (int i = 0; i < n; i++) {
            vector<mi> before(n + q);
            vector<mi> after(n + q);

            for (int j = 0; j < n + q; j++) {
                if (x > 0) {
                    for (int a = 0; a < n; a++) {
                        if (adj[a][i]) {
                            before[j] += dp[j][a][x - 1];
                        }
                    }
                }

                if (x > 0) {
                    for (int a = 0; a < n; a++) {
                        if (adj[i][a]) {
                            after[j] += dp[a][j][x - 1];
                        }
                    }
                }

                // connect from query to main dp
                if (in_val[j].first == i && in_val[j].second == x) {
                    before[j] += 1;
                }

                if (out_val[j].first == i && out_val[j].second == x) {
                    after[j] += 1;
                }
            }

            // represents nothing before or after
            before[i] += 1;
            after[i] += 1;

            for (int st = 0; st < n + q; st++) {
                for (int en = 0; en < n + q; en++) {
                    dp[st][en][x] += before[st] * after[en];
                }
            }
        }
    }

    for (int i = n; i < n + q; i++) {
        cout << dp[i][i][k - 1].v << '\n';
    }

    return 0;
}
