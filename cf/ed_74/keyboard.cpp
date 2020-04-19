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
string s;

int cnt[20];
int cntp[20][20];
ll dp[1 << 20];

ll get(int mm) {
    int tot = 0; 
    for (int i = 0; i < m; i++) {
        if (!((1 << i) & mm)) continue;
        for (int j = 0; j < m; j++) {
            if (!((1 << j) & mm)) tot += cntp[i][j];
        }
    }
    return tot;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    cin >> s;

    for (char c : s) {
        cnt[c - 'a']++;
    }

    for (int i = 1; i < n; i++) {
        int a = s[i - 1] - 'a';
        int b = s[i] - 'a';
        cntp[a][b]++;
        if (a != b) cntp[b][a]++;
    }

    for (int i = 1; i < (1 << m); i++) {
        dp[i] = INFLL;

        for (int j = 0; j < m; j++) {
            if ((1 << j) & i) {
                int mm = i - (1 << j);
                dp[i] = min(dp[i], dp[mm]);
            }
        }

        dp[i] += get(i);
    }

    cout << dp[(1 << m) - 1] << '\n';

    return 0;
}
