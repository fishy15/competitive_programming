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
#define MAXN 2500

using namespace std;

int n, m;
vector<array<ll, 3>> edge;
ll dist[MAXN];
int p[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        edge.push_back({a, b, c});
    }

    int change = -1;
    for (int i = 0; i < n; i++) {
        for (auto e : edge) {
            if (dist[e[1]] > dist[e[0]] + e[2]) {
                dist[e[1]] = dist[e[0]] + e[2];
                p[e[1]] = e[0];
                if (i == n - 1) change = e[1];
            }
        }
    }

    if (change == -1) {
        cout << "NO\n";
    } else {
        int cur = p[change];
        for (int i = 0; i < n; i++) cur = p[cur];
        change = cur;
        vector<int> ans = {change};
        cur = p[cur];
        while (cur != change) {
            ans.push_back(cur);
            cur = p[cur];
        }
        ans.push_back(change);
        reverse(ans.begin(), ans.end());

        cout << "YES\n";
        for (int i : ans) {
            cout << i + 1 << ' ';
        } cout << '\n';
    }

    return 0;
}
