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
#define MAXN 100000

using namespace std;

int n;
int pos[MAXN + 1];
int rr[MAXN + 1];
int dp[MAXN + 1];

// segtree stuff
int segtree[4 * MAXN + 10];

void update(int v, int i, int x, int l = 1, int r = n) {
    if (l == r) {
        dp[i] = x;
        segtree[v] = x;
    } else {
        int m = l + (r - l) / 2;
        if (i <= m) {
            update(2 * v, i, x, l, m);
        } else {
            update(2 * v + 1, i, x, m + 1, r);
        }

        segtree[v] = max(segtree[2 * v], segtree[2 * v + 1]);
    }
}

int query(int v, int x, int y, int l = 1, int r = n) {
    if (x <= l && r <= y) {
        return segtree[v];
    } 

    if (y < l || x > r) {
        return 0;
    }

    int m = l + (r - l) / 2;
    return max(query(2 * v, x, y, l, m), query(2 * v + 1, x, y, m + 1, r));
}

int main() {
    ifstream fin("nocross.in");
    ofstream fout("nocross.out");

    fin >> n;
    for (int i = 0; i < n; i++) {
        int x; fin >> x;
        pos[i] = x;
    }

    for (int i = 0; i < n; i++) {
        int x; fin >> x;
        rr[x] = i + 1;
    }

    int ans = 0;

    for (int k = 0; k < n; k++) {
        int i = pos[k];
        vector<int> process;
        for (int j = max(1, i - 4); j <= min(n, i + 4); j++) {
            process.push_back(rr[j]);   
        }

        sort(process.rbegin(), process.rend());

        for (int j : process) {
            int prev = 0;
            if (j > 1) {
                prev = query(1, 1, j - 1);
            }
            dp[j] = max(dp[j], prev + 1);
            update(1, j, dp[j]);
            ans = max(ans, dp[j]);
        }
    }

    fout << ans << '\n';
    return 0;
}
