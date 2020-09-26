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
#define MAXN 10010

using namespace std;

int n;
vector<short> p[MAXN];
vector<short> nxt[MAXN];
short val[MAXN][2];
short cur[MAXN];

void dfs(int loc, int idx, int ok, int old) {
    for (int k : nxt[loc]) {
        cur[k] += ok - old;
    }
    val[loc][idx] = ok;
    for (int k : nxt[loc]) {
        int ok2 = cur[k] ? cur[k] / abs(cur[k]) : 0;
        if (ok2 != val[k][idx]) dfs(k, idx, ok2, val[k][idx]);
    }
}

void fix(int i) {
    for (int j = 2; j < n; j++) {
        int tot = 0;
        for (int k : p[j]) tot += val[k][i];
        cur[j] = tot;
    }
    for (int j = 2; j < n; j++) {
        int ok = cur[j] ? cur[j] / abs(cur[j]) : 0;
        if (ok != val[j][i]) {
            dfs(j, i, ok, val[j][i]);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 2; i < n; i++) {
        int k; cin >> k;
        for (int j = 0; j < k; j++) {
            int x; cin >> x;
            p[i].push_back(x);
            nxt[x].push_back(i);
        }
        val[i][0] = -1;
        val[i][1] = 1;
    }

    val[0][0] = val[0][1] = -1;
    val[1][0] = val[1][1] = 1;
    fix(0);
    fix(1);

    for (int i = 0; i < n; i++) {
        if (val[i][0] == val[i][1]) {
            int x = val[i][0];
            if (x == -1) cout << "0\n";
            else if (x == 0) cout << "1/2\n";
            else cout << "1\n";
        } else {
            cout << "?\n";
        }
    }

    return 0;
}
