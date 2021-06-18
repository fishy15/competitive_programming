/*
ID: aaryan1
TASK: rockers
LANG: C++11
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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n, t, m;
int songs[30];

// dp[used][time]
int dp[30][30];
int nxt[30][30];

int maxi(int& a, int b) {
    return a = max(a, b);
}

int main() {
    ifstream fin("rockers.in");
    ofstream fout("rockers.out");

    fin >> n >> t >> m;
    for (int i = 0; i < n; i++) {
        fin >> songs[i];
    }

    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            dp[i][j] = -1;
        }
    }

    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        if (songs[i] > t) continue;

        // copy
        for (int j = 0; j < 30; j++) {
            for (int k = 0; k < 30; k++) {
                nxt[j][k] = dp[j][k];
            }
        }

        // process
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < t; k++) {
                if (dp[j][k] == -1) continue;
                if (songs[i] == t) {
                    if (k == 0) {
                        maxi(nxt[j + 1][0], dp[j][k] + 1);
                    } else {
                        maxi(nxt[j + 2][0], dp[j][k] + 1);
                    }
                } else if (k + songs[i] == t) {
                    maxi(nxt[j + 1][0], dp[j][k] + 1);
                } else if (k + songs[i] > t) {
                    maxi(nxt[j + 1][songs[i]], dp[j][k] + 1);
                } else {
                    maxi(nxt[j][k + songs[i]], dp[j][k] + 1);
                }
            }
        }

        // copy
        for (int j = 0; j < 30; j++) {
            for (int k = 0; k < 30; k++) {
                dp[j][k] = nxt[j][k];
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < t; j++) {
            maxi(ans, dp[i][j]);
        }
    }

    fout << maxi(ans, dp[m][0]) << '\n';

    return 0;
}
