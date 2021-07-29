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
#define MAXN 100010

using namespace std;

int n, m;
vector<array<int, 3>> adj[MAXN];
vector<pair<int, int>> radj[MAXN];

int pos;
int loc[MAXN];

bool check(int x, bool pls) {
    vector<int> deg(n + 1);
    for (int i = 1; i <= n; i++) {
        for (auto e : adj[i]) {
            if (e[1] > x) {
                deg[i]++;
            }
        }
    }

    queue<int> smth;

    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) {
            smth.push(i);
        }
    }

    int cnt = 0;

    while (!smth.empty()) {
        int t = smth.front();
        smth.pop();
        cnt++;
        if (pls) {
            loc[t] = pos++;
        }

        for (auto e : radj[t]) {
            if (e.second > x) {
                deg[e.first]--;
                if (deg[e.first] == 0) {
                    smth.push(e.first);
                }
            }
        }
    }

    return cnt == n;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v, c; cin >> u >> v >> c;
        adj[u].push_back({v, c, i + 1});
        radj[v].push_back({u, c});
    }

    int l = 0;
    int r = 1e9;
    int a = -1;

    while (l <= r) {
        int m = l + (r - l) / 2;
        bool qq = check(m, false);

        if (qq) {
            a = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    check(a, true);
    int k = 0;
    vector<int> kk;

    for (int i = 1; i <= n; i++) {
        for (auto e : adj[i]) {
            if (loc[e[0]] > loc[i]) {
                k++;
                kk.push_back(e[2]);
            }
        }
    }

    cout << a << ' ' << k << '\n';
    for (int i : kk) cout << i << ' ';
    cout << '\n';

    return 0;
}
