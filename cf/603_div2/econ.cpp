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
#define MOD 1001001007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000001

using namespace std;

int n;
struct tree {
    int sz;
    int up[2001];
    int in[2001];
    int out[2001];
    int lift[2001][12];
    vector<int> connect[1001];
    int below[2001];
    int time = 0;
    int dp[1001][1001];

    void dfs(int i, int par) {
        in[i] = time;

        lift[i][0] = par;
        for (int j = 1; j <= 11; j++) {
            lift[i][j] = lift[lift[i][j - 1]][j - 1];
        }
        
        for (int j : connect[i]) {
            time++;
            dfs(j, i);
        }
        time++;
        out[i] = time;
    }

    int dfs2(int i, int par) {
        int ans = 0;

        for (int j : connect[i]) {
            ans += dfs2(j, i) + 1;
        }

        return below[i] = ans;
    }

    bool is_ancestor(int par, int child) {
        return in[par] <= in[child] && out[par] >= out[child];
    }

    int lca(int a, int b) {
        if (is_ancestor(a, b)) {
            return a;
        } 

        if (is_ancestor(b, a)) {
            return b;
        }

        for (int i = 11; i >= 0; i--) {
            if (!is_ancestor(lift[a][i], b)) {
                a = lift[a][i];
            }
        }

        return lift[a][0];
    }

    void qqqq() {
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (i == j) {
                    dp[i][j] = up[i];
                } else {
                    dp[i][j] = lca(dp[i][j - 1], up[j]);
                }
            }
        }
    }
};

int ans[1001];

int main() {
    //cin.tie(0); ios::sync_with_stdio(0);

    cin >> n;
    tree t1, t2;
    cin >> t1.sz;
    for (int i = 1; i < t1.sz; i++) {
        int a; cin >> a;
        t1.connect[a - 1].push_back(i);
    }

    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        t1.up[i] = a - 1;
    }

    cin >> t2.sz;
    for (int i = 1; i < t2.sz; i++) {
        int a; cin >> a;
        t2.connect[a - 1].push_back(i);
    }

    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        t2.up[i] = a - 1;
    }

    t1.dfs(0, 0);
    t1.dfs2(0, 0);
    t2.dfs(0, 0);
    t2.dfs2(0, 0);
    t1.qqqq();
    t2.qqqq();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << t1.below[t1.dp[i][j]] << ' ';
        } cout << '\n';
    }

    for (int i = 0; i < n; i++) {
        ans[i] = t1.below[t1.dp[0][i]];
        for (int j = 0; j < i; j++) {
            ans[i] = max(ans[i], ans[j] + t1.below[t1.dp[j + 1][i]]);
            ans[i] = max(ans[i], ans[j] + t2.below[t2.dp[j + 1][i]]);
        }
        cout << ans[i] << '\n';
    }

    cout << ans[n - 1] << '\n';
    return 0;
}
