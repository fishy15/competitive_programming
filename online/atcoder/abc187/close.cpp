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

int n, m;
bool edge[20][20];
bool ok[1 << 20];
int dp[1 << 20];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        edge[a][b] = true;
        edge[b][a] = true;
    }

    for (int i = 0; i < (1 << n); i++) {
        vector<int> cur;
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) cur.push_back(j);
        }

        int sz = cur.size();
        bool works = true;
        for (int j = 0; j < sz; j++) {
            for (int k = j + 1; k < sz; k++) {
                if (!edge[cur[j]][cur[k]]) {
                    works = false;
                    goto done;
                }
            }
        }

        done: 
        if (works) ok[i] = true;
    }

    for (int i = 1; i < (1 << n); i++) {
        dp[i] = n + 1;
    }

    int p = 1;
    for (int i = 1; i < (1 << n); i++) {
        if ((1 << p) == i) p++;
        if (ok[i]) {
            dp[i] = min(dp[i], 1);
            int m2 = (1 << n) - 1 - i;
            /* m2 = m2 & ((1 << p) - 1); */
            for (int j = m2; j > 0; j = (j - 1) & m2) {
                dp[i ^ j] = min(dp[i ^ j], dp[j] + 1);
            }
        }
    }

    cout << dp[(1 << n) - 1] << '\n';

    return 0;
}
