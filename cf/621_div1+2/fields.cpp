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
#define MAXN 200000

using namespace std;

int n, m, k;

vector<int> spec;
vector<int> adj[MAXN + 1];

int dist[MAXN + 1];
int dist2[MAXN + 1];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> k;

    for (int i = 0; i < k; i++) {
        int x; cin >> x;
        spec.push_back(x);
    }

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // distance from source
    queue<pair<int, int>> q;
    q.push({1, 1});
    int cnt = 0;

    while (!q.empty() && cnt < n) {
        auto x = q.front();
        q.pop();
        if (dist[x.first]) {
            continue;
        }

        dist[x.first] = x.second;
        cnt++;

        for (int e : adj[x.first]) {
            if (!dist[e]) {
                q.push({e, x.second + 1});
            }
        }
    }

    // distance from end
    q = {};
    cnt = 0;
    q.push({n, 1});

    while (!q.empty() && cnt < n) {
        auto x = q.front();
        q.pop();
        if (dist2[x.first]) {
            continue;
        }

        dist2[x.first] = x.second;
        cnt++;

        for (int e : adj[x.first]) {
            if (!dist2[e]) {
                q.push({e, x.second + 1});
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        dist[i]--;
        dist2[i]--;
    }

    sort(spec.begin(), spec.end(), [](const int& k1, const int& k2) {
        if (dist2[k1] == dist2[k2]) {
            return k1 < k2;
        }

        return dist2[k1] < dist2[k2];
    });

    int ans = 0;
    for (int i = 1; i < k; i++) {
        // make longest possible without going over n
        int tot = min(dist[spec[i]] + dist2[spec[i - 1]] + 1, dist[n]);
        ans = max(ans, tot);
    }

    if (ans == 0) {
        ans = dist[n];
    }

    cout << ans << '\n';

    return 0;
}
