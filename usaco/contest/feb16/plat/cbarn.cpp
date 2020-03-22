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
#define MAXN 1000

using namespace std;

int n, k;
ll nums[MAXN];

// cost[start][end]
ll cost[MAXN][MAXN];
ll dp[MAXN][8];

void solve(int l, int r, int optl, int optr, int k) {
    if (l > r) return;
    int mid = l + (r - l) / 2;

    ll maxval = INFLL;
    int opt = -1;
    
    for (int i = max(optl, mid); i <= optr; i++) {
        ll c = cost[mid % n][i % n] + dp[(i + 1) % n][k - 1];
        if (c < maxval) {
            maxval = c;
            opt = i;
        }
    }

    dp[mid % n][k] = maxval; 
    solve(l, mid - 1, optl, opt, k);
    solve(mid + 1, r, opt, optr, k);
}

int main() {
    ifstream fin("cbarn.in");
    ofstream fout("cbarn.out");

    fin >> n >> k;
    for (int i = 0; i < n; i++) {
        fin >> nums[i];
    }

    for (int i = 0; i < n; i++) {
        ll prev = 0;
        for (int j = 0; j < n; j++) {
            cost[i][(i + j) % n] = prev + j * nums[(i + j) % n];
            prev = cost[i][(i + j) % n];
        } 
    }

    ll ans = INFLL;
    for (int l = 0; l < n; l++) {
        for (int i = 0; i < n; i++) {
            dp[(l + i) % n][1] = cost[(l + i) % n][(l + n - 1) % n];
        }

        cout <<"YO\n";
        for (int i = 2; i <= k; i++) {
            solve(l, l + n - 1, l, l + n - 1, i);
        }

        ans = min(ans, dp[l][k]);
    }

    fout << ans << '\n';

    return 0;
}
