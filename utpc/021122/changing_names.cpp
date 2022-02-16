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
#include <functional>
#include <numeric>

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
vector<array<int, 26>> cnt;
pair<int, int> dp[1010][30];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        array<int, 26> cc{};

        for (char c : s) {
            cc[c - 'a']++;
        }

        cnt.push_back(cc);
    }

    for (int i = 0; i < 1010; i++) {
        for (int j = 0; j < 30; j++) {
            dp[i][j] = {-1, -1};
        }
    }

    dp[0][0] = {0, 0};

    for (int i = 1; i <= 26; i++) {
        map<int, int> cnts;
        for (int j = 0; j < n; j++) {
            cnts[cnt[j][i - 1]]++;
        }

        vector<int> add(m + 1);
        int cur_above = n;
        int below_sum = 0;

        for (int j = 0; j <= m; j++) {
            cur_above -= cnts[j];
            below_sum += cnts[j] * j;
            add[j] = below_sum + (n - cur_above) * j;
        }

        for (int sz = 0; sz <= m; sz++) {
            for (int st = 0; st + sz <= m; st++) {
                if (dp[st][i - 1].first == -1) continue;
                if (dp[st][i - 1].first + add[sz] >= dp[st + sz][i].first) {
                    dp[st + sz][i].first = dp[st][i - 1].first + add[sz];
                    dp[st + sz][i].second = sz;
                }
            }
        }
    }

    int cur = m;
    int pos = 26;
    while (cur > 0) {
        int sz = dp[cur][pos].second;
        cout << string(sz, 'a' + pos - 1);
        pos--;
        cur -= sz;
    }
    cout << '\n';

    return 0;
}
