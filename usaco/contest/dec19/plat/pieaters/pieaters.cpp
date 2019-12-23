// :pray: :steph:
// :pray: :bakekaga:

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

int n, m; 
vector<array<int, 3>> cows;
int dp[1 << 20];

int main() {
    ifstream fin("pieaters.in");
    ofstream fout("pieaters.out");

    fin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b, c; fin >> a >> b >> c;
        cows.push_back({a, b, c});
    }

    vector<int> pos(60);
    for (int i = 1; i < (1 << m); i++) {
        for (int j = 0; j < m; j++) {
            if (i & (1 << j)) {
                if (i == (1 << j)) {
                    dp[i] = cows[j][0];
                } else if (dp[i - (1 << j)] && dp[i - (1 << j)] + cows[j][0] > dp[i]) {
                    for (int &k : pos) k = 0;
                    for (int k = 0; k < m; k++) {
                        if (i & (1 << k) && j != k) {
                            pos[cows[k][1]]++;
                            pos[cows[k][2] + 1]--;
                        }
                    }

                    int cur = 0;
                    bool check = false;
                    bool works = false;

                    for (int k = 1; k <= 50; k++) {
                        cur += pos[k];
                        if (k == cows[j][1]) check = true;
                        if (k == cows[j][2] + 1) break;
                        if (check && cur == 0) {
                            works = true;
                            break;
                        }
                    }

                    if (works) {
                        dp[i] = dp[i - (1 << j)] + cows[j][0];
                    }
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < (1 << 20); i++) {
        ans = max(ans, dp[i]);
    }

    fout << ans << '\n';

    return 0;
}
