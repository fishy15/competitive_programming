// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
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
#define MOD 2012

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000

using namespace std;

int n;
string s;

// dp[index][open]
int dp[MAXN + 1][MAXN + 1];

int main() {
    ifstream fin("bbreeds.in");
    ofstream fout("bbreeds.out");

    fin >> s;
    n = (int)(s.size());

    dp[n][0] = 1;

    for (int i = n - 1; i >= 0; i++) {
        for (int op = 0; op <= n / 2; op++) {
            if (s[i] == '(') {
                dp[i][op] = dp[i + 1][op] + dp[i + 1][op + 1];
            } else {
                dp[i][op] += 
            }
        }
    }

    return 0;
}
