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

int n, m;
vector<int> adj[MAXN + 1];
int p[MAXN + 1];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    queue<pair<int, int>> q;
    q.push({1, -1});

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        if (p[cur.first]) continue;
        p[cur.first] = cur.second;

        for (int e : adj[cur.first]) {
            if (!p[e]) {
                q.push({e, cur.first});
            }
        }
    }

    if (p[n]) {
        vector<int> ans;
        int cur = n;
        while (cur != -1) {
            ans.push_back(cur);
            cur = p[cur];
        }

        reverse(ans.begin(), ans.end());
        cout << ans.size() << '\n';
        for (int i : ans) {
            cout << i << ' ';
        } cout << '\n';
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}
