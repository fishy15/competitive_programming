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
#define MAXN 300000

using namespace std;

int n, k;
string ord;
int dp[MAXN + 1];
int pre[MAXN + 1];

int main() {
    ifstream fin("redistricting.in");
    ofstream fout("redistricting.out");

    fin >> n >> k >> ord;

    for (int i = 0; i < n; i++) {
        if (ord[i] == 'H') {
            pre[i + 1] = pre[i] + 1;
        } else {
            pre[i + 1] = pre[i] - 1;
        }
    }

    multiset<pair<int, int>> ms = {{0, 0}};
    for (int i = 1; i <= n; i++) {
        auto beg = *ms.begin();
        dp[i] = beg.first;

        if (beg.second >= pre[i]) {
            dp[i]++;
        }

        ms.insert({dp[i], pre[i]});
        if (i - k >= 0) {
            ms.erase(ms.find({dp[i - k], pre[i - k]}));
        }
        //cout << dp[i] << ' ' << beg.first << ' ' << beg.second << '\n';
    }

    fout << dp[n] << '\n';

    return 0;
}
