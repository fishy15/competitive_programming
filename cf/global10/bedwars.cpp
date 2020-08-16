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

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    string ss[4] = {"RL", "RRL", "RLL", "RRLL"};
    int ans = INF;
    for (int a = 0; a < 4; a++) {
        vector<int> dp(n + 1, INF);
        dp[0] = 0;
        for (int i = 0; i < n; i++) {
            for (auto s2 : ss) {
                if (i < s2.size() - 1) continue;
                int cnt = 0;
                for (int j = 0; j < s2.size(); j++) {
                    if (s2[j] != s[i - s2.size() + 1 + j]) {
                        cnt++;
                    }
                }
                dp[i + 1] = min(dp[i + 1], dp[i - s2.size() + 1] + cnt);
            }
        }
        ans = min(ans, dp[n]); 
        string s3;
        for (int i = 1; i < n; i++) {
            s3 += s[i]; 
        }
        s3 += s[0];
        s = s3;
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
