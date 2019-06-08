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

#define MAXN 200000

using namespace std;

int n, q;
vector<vector<int>> adj;
int preorder[MAXN + 1];
int pos[MAXN + 1];
int sz[MAXN + 1];

int curpos;

int dfs(int val) {
    preorder[curpos] = val;
    pos[val] = curpos;
    curpos++;
    
    sz[val]++;

    for (int i = 0; i < adj[val].size(); i++) {
        sz[val] += dfs(adj[val][i]);
    }

    return sz[val];
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    cin >> n >> q;

    adj = vector<vector<int>>(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int x; cin >> x;
        adj[x].push_back(i + 2);
    }

    dfs(1);


    /* for (int i = 1; i <= n; i++) { */
    /*     for (int j = 0; j < sz[i]; j++) { */
    /*         cout << preorder[pos[i] + j] << ' '; */
    /*     } */
    /*     cout << '\n'; */
    /* } */

    for (int i = 0; i < q; i++) {
        int u, k; cin >> u >> k;
        if (sz[u] < k) {
            cout << "-1\n";
        } else {
            cout << preorder[pos[u] + k - 1] << '\n';
        }
    }

    return 0;
}
