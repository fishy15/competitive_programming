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

int n, m;
vector<vector<int>> unadj;
vector<bool> visited;
vector<int> ans;

void dfs(int pos) {
    int pos2 = 0;
    visited[pos] = true;
    sort(unadj[pos].begin(), unadj[pos].end());
    for (int i = 0; i < n; i++) {
        if (pos2 < unadj[pos].size()) {
            if (unadj[pos][pos2] == i) {
                pos2++;
            } else {
                if (!visited[i]) {
                    dfs(i);
                }
            }
        } else {
            if (!visited[i]) {
                dfs(i); 
            }
        }
    }

    ans.push_back(pos);
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> m;

    unadj = vector<vector<int>>(n);
    visited = vector<bool>(n, false);

    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        unadj[x].push_back(y);
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        cout << ans[i] + 1 << ' ';
    } cout << '\n';

    return 0;
}
