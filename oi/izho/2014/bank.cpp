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
int a[30];
int b[30];
// {current index, amt left in current person}
pair<int, int> dp[(1 << 20) + 10];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    for (int i = 1; i < (1 << m); i++) {
        for (int j = 0; j < m; j++) {
            if (i & (1 << j)) {
                int prev = i - (1 << j);
                pair<int, int> nxt;
                if (b[j] + dp[prev].second == a[dp[prev].first]) {
                    nxt = {dp[prev].first + 1, 0};
                } else {
                    nxt = {dp[prev].first, b[j] + dp[prev].second};
                }
                if (nxt.first == n && nxt.second == 0) {
                    cout << "YES\n";
                    return 0;
                }
                dp[i] = max(dp[i], nxt);
            }
        }
    }

    cout << "NO\n";

    return 0;
}
