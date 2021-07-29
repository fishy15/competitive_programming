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
#define MAXN 400000

using namespace std;

int n;
map<int, int> cnt;

int dp[MAXN + 1];
int dp2[MAXN + 1];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (cnt.count(x)) {
            cnt[x]++;
        } else {
            cnt[x] = 1;
        }
    }

    for (auto p : cnt) {
        dp[p.second]++;
        dp2[p.second] += p.second;
    }

    for (int i = 1; i <= n; i++) {
        dp[i] += dp[i - 1];
        dp2[i] += dp2[i - 1];
    }

    // i is the shorter side
    int x = 0;
    int y = 0;
    for (int i = 1; i <= n; i++) {
        int tot = dp2[i] + ((int)cnt.size() - dp[i]) * i;
        int j = tot / i;
        if (j < i) break;
        if (i * j > x * y) {
            x = i;
            y = j;
        }
    }

    vector<vector<int>> ans = vector<vector<int>>(x, vector<int>(y));
    int i = 0;
    int j = 0;
    int c = 0;
    int cur = 0;
    
    vector<pair<int, int>> smth;
    for (auto p : cnt) {
        smth.push_back(p);
    }

    sort(smth.begin(), smth.end(), [](const pair<int, int> &p1, const pair<int, int> &p2) {
        if (p1.second == p2.second) {
            return p1.first < p2.first;
        }
        
        return p1.second > p2.second;
    });

    auto it = smth.begin();
    while (c < x * y) {
        if (ans[i][j]) {
            i++; i %= x;
        } else {
            if (cur == it->second || cur == x) {
                it++;
                cur = 0;
            }

            ans[i][j] = it->first;
            cur++;
            i++; i %= x;
            j++; j %= y;
            c++;
        }
    }

    cout << x * y << '\n';
    cout << x << ' ' << y << '\n';
    for (auto& v : ans) {
        for (auto x : v) {
            cout << x << ' ';
        }
        cout << '\n';
    }

    return 0;
}
