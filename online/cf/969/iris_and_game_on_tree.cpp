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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector adj(n, vector<int>());
    rep(i, 0, n - 1) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    string s;
    cin >> s;

    int leaf_one = 0;
    int leaf_zero = 0;
    int leaf_question = 0;
    int other_question = 0;
    rep(i, 1, n) {
        if (sz(adj[i]) == 1) {
            if (s[i] == '0') leaf_zero++;
            else if (s[i] == '1') leaf_one++;
            else leaf_question++;
        } else {
            if (s[i] == '?') {
                other_question++;
            }
        }
    }

    int ans = 0;
    if (s[0] == '?') {
        if (leaf_one >= leaf_zero) {
            ans = leaf_one;
        } else {
            ans = leaf_zero;
        }

        if (other_question % 2 == 0 || leaf_one != leaf_zero) {
            ans += leaf_question / 2;
        } else {
            ans += (leaf_question + 1) / 2;
        }
    } else {
        if (s[0] == '0') {
            ans = leaf_one;
        } else {
            ans = leaf_zero;
        }

        ans += (leaf_question + 1) / 2;
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
