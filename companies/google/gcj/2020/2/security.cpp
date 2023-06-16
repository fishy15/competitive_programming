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

void solve() {
    int c, d; cin >> c >> d;
    vector<int> info(c);
    vector<vector<int>> adj(c);
    vector<pair<int, int>> edge;
    vector<int> ans(d);
    map<pair<int, int>, int> m;
    for (int i = 1; i < c; i++) {
        cin >> info[i];
    }
    for (int i = 0; i < d; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        edge.push_back({x, y});
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<pair<int, int>> smth;
    vector<pair<int, int>> smth2;
    for (int i = 1; i < c; i++) {
        if (info[i] > 0) smth.push_back({info[i], i}); 
        else smth2.push_back({-info[i], i});
    }

    sort(smth.begin(), smth.end());
    sort(smth2.begin(), smth2.end());
    vector<int> ord = {0};
    int cur1 = 0;
    int cur2 = 0;

    while (ord.size() < c) {
        while (cur2 < smth2.size() && ord.size() >= smth2[cur2].first) {
            ord.push_back(smth2[cur2].second); 
            cur2++;
        }
        if (cur1 < smth.size()) {
            ord.push_back(smth[cur1].second);
            cur1++;
        }
    }

    vector<int> tt(c);
    vector<int> vis(c, false);
    vis[0] = true;
    for (int i = 1; i < c; i++) {
        int j = ord[i];
        if (info[j] < 0) {
            if (-info[j] == i) {
                tt[j] = tt[ord[i - 1]] + 1;
            } else {
                tt[j] = tt[ord[i - 1]];
            }
        } else {
            tt[j] = info[j];
        }

        
        bool done = false;
        for (int k : adj[j]) {
            if (vis[k]) {
                int len = tt[j] - tt[k];
                for (int a = 0; a < d; a++) {
                    if (edge[a] == make_pair(j, k) || edge[a] == make_pair(k, j)) {
                        if (done || !len) {
                            ans[a] = 1e6;
                        } else {
                            ans[a] = len;
                            done = true;
                        }
                    }
                }
            }
        }
        vis[j] = true;
    }

    for (int a : ans) {
        if (!a) a = 1e6;
        cout << a << ' ';
    } cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
