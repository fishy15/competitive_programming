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
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct block {
    int start;
    int end;
    vector<int> vals = vector<int>(200);
    vector<vector<int>> dp = vector<vector<int>>(200, vector<int>(4));
    /*
     * dp[i][0] - max value starting at 0th element of block including ith element
     * dp[i][1] - max value starting at 0th element of block not including ith element
     * dp[i][2] - max value starting at 1st element of block including ith element
     * dp[i][3] - max value starting at 1st element of block not including ith element
     */
};

block b[200];
ll dp[200][2];

int main() {
    ifstream fin("optmilk.in");
    ofstream fout("optmilk.out");

    int n, d; cin >> n >> d;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        int blocknum = i / 200;
        int blockpos = i % 200;
        b[blocknum].vals[blockpos] = x;
    }

    for (int i = 0; i < n / 200; i++) {
        b[i].start = 200 * i;
        b[i].end = 200 * i + 199;
    }

    b[n / 200].end = n;

    for (int i = 0; i <= n / 200; i++) {
        b[i].dp[0][0] = b[i].vals[0];
        b[i].dp[1][2] = b[i].vals[1];

        for (int j = 2; j < b[i].end - b[i].start; j++) {
            b[i].dp[i][0] = max(b[i].dp[i - 2][0], b[i].dp[i - 3][0]) + b[i].vals[i];
            b[i].dp[i][1] = max(b[i].dp[i - 1][0], b[i].dp[i - 2][0]);
            b[i].dp[i][2] = max(b[i].dp[i - 2][2], b[i].dp[i - 3][2]) + b[i].vals[i];
            b[i].dp[i][3] = max(b[i].dp[i - 1][2], b[i].dp[i - 2][2]);
        }
    }

    //ll ans = 0;

    for (int i = 0; i < d; i++) {
        int pos, val; cin >> pos >> val;
        pos--;
    }

    return 0;
}
