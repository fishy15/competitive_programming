// :pray: :arrayman:
// :pray: :summit:
// :pray: :pusheen:
// :pray: :prodakcin:
// :pray: :spacewalker:
// :pray: :duk:
// :pray: :gustav:
// :pray: :tmw:
// :pray: :eed:
// :pray: :chicubed:
// :pray: :arceus:
// :pray: :gamegame:
// :pray: :sinx:
// :pray: :eyg:
// :pray: :evan:
// :pray: :cj:
// :pray: :steph:
// :pray: :fatant:
// :pray: :mathbot:
// :pray: :dolphin:
// :pray: :stef:
// :pray: :geothermal:
// :pray: :mikey:
// :pray: :horse:
// :pray: :snek:
// :pray: :wayne:
// :pray: :wu:
// :pray: :vmaddur:
// :pray: :dorijanko:
// :pray: :gaming:
// :pray: :kassuno:
// :pray: :hyacinth:
// :pray: :chilli:
// :pray: :dhruv:
// :pray: :philip:
// :pray: :paiman:
// :pray: :camel:
// :pray: :tree:
// :pray: :tux:
// :pray: :jony:
// :pray: :kage:
// :pray: :ghost:
// :pray: :aha:

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 10000007

using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<bool> visited(n + 1, false);
    vector<int> ans;

    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    queue<pair<int, int>> cur;
    cur.push({1, true});
    while (!cur.empty()) {
        int curPos = cur.front().first;
        bool curVal = cur.front().second;
        cur.pop();

        if (visited[curPos]) continue;
        visited[curPos] = true;

        if (curVal) {
            ans.push_back(curPos);
        }

        for (int& i : adj[curPos]) {
            if (!visited[i]) {
                cur.push({i, !curVal});
            }
        }
    }

    sort(ans.begin(), ans.end());
    if (ans.size() > n / 2) {
        cout << n - ans.size() << '\n';
        for (int i = 1; i < ans[0]; i++) {
            cout << i << ' ';
        }

        for (int i = 0; i < ans.size() - 1; i++) {
            for (int j = ans[i] + 1; j < ans[i + 1]; j++) {
                cout << j << ' ';
            } 
        }

        for (int i = ans[ans.size() - 1] + 1; i <= n; i++) {
            cout << i << ' ';
        }

        cout << '\n';
    } else {
        cout << ans.size() << '\n';
        for (int& i : ans) {
            cout << i << ' ';
        }

        cout << '\n';
    }
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int q; cin >> q;
    while (q--) {
        solve();
    }

    return 0;
}
