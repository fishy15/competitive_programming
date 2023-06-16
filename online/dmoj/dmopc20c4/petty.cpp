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
#define MAXN 1000000

using namespace std;

int n, m;
vector<int> adj[MAXN];
pair<int, vector<int>> ans;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    ans.second.assign(n, 1);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 0; i < (1 << n); i++) {
        vector<int> opt(n);
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                opt[j] = 1;
            } else {
                opt[j] = 2;
            }
        }

        int cnt = 0;
        for (int j = 0; j < n; j++) {
            int a = 0;
            
            for (int x : adj[j]) {
                if (opt[x] == opt[j]) a++;
            }

            if (a % 2 == 0) {
                cnt++;
            }
        }

        ans = max(ans, {cnt, opt});
    }

    cout << ans.first << '\n';
    for (int i = 0; i < n; i++) {
        cout << ans.second[i];
        if (i < n - 1) {
            cout << ' ';
        } else {
            cout << '\n';
        }
    }

    return 0;
}
