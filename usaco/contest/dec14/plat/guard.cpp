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

struct cow {
    ll h, w, s;
};

int n, h;
vector<cow> cows;
ll dp[1<<20];

int main() {
    ifstream fin("guard.in");
    ofstream fout("guard.out");

    fin >> n >> h;

    for (int i = 0; i < n; i++) {
        cow c; fin >> c.h >> c.w >> c.s;
        cows.push_back(c);
    }

    ll ans = -1;

    for (int i = 1; i < (1 << n); i++) {
        ll total = 0;
        dp[i] = -1;
        for (int j = 0; j < n; j++) {
            if (i == (1 << j)) {
                total += cows[j].h;
                dp[i] = cows[j].s;
            } else if (i & (1 << j)) {
                total += cows[j].h;
                int prev = i - (1 << j); 
                if (dp[prev] >= cows[j].w) {
                    dp[i] = max(dp[i], min(dp[prev] - cows[j].w, cows[j].s));
                }
            }
        }

        if (h <= total) {
            ans = max(ans, dp[i]);
        }
    }

    if (ans == -1) {
        fout << "Mark is too tall\n";
    } else {
        fout << ans << '\n';
    }

    return 0;
}
