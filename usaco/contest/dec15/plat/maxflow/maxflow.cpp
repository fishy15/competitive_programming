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
// :pray: :coolguy:
// :pray: :imax:
// :pray: :howlet:
// :pray: :darren:
// :pray: :arie: 
// :pray: :blastman: 
// :pray: :zephyr: 
// :pray: :bigc:

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
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100000

using namespace std;

int n, k;
int l;
int t;
vector<int> en;
vector<int> ex;
vector<vector<int>> adj;
vector<vector<int>> up;
vector<int> prefix;
int cur;
int ans;

void dfs(int node, int parent) {
    en[node] = t;
    t++;

    up[node][0] = parent;
    for (int i = 1; i <= l; i++) {
        up[node][i] = up[up[node][i - 1]][i - 1]; 
    }

    for (int next : adj[node]) {
        if (next != parent) {
            dfs(next, node);
        }
    }

    ex[node] = t;
    t++;
}

int dfs2(int node, int parent) {
    int sum = prefix[node];
    for (int i : adj[node]) {
        if (i != parent) {
            sum += dfs2(i, node);
        }
    }

    ans = max(ans, sum);
    return sum;
}

bool is_ancestor(int parent, int child) {
    return en[parent] <= en[child] && ex[parent] >= ex[child];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) {
        return u;
    } 

    if (is_ancestor(v, u)) {
        return v;
    }

    for (int i = l; i >= 0; i--) {
        if (!is_ancestor(up[u][i], v)) {
            u = up[u][i];
        }
    }

    return up[u][0];
}

int main() {
    ifstream fin("maxflow.in");
    ofstream fout("maxflow.out");

    fin >> n >> k;

    adj = vector<vector<int>>(n + 1);
    en = vector<int>(n + 1);
    ex = vector<int>(n + 1);
    prefix = vector<int>(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int x, y; fin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    l = ceil(log2(n));

    up = vector<vector<int>>(n + 1, vector<int>(l + 1));

    dfs(1, 1);

    for (int i = 0; i < k; i++) {
        int x, y; fin >> x >> y;
        int com = lca(x, y);
        prefix[com]--;
        prefix[up[com][0]]--;
        prefix[x]++;
        prefix[y]++;
    }

    dfs2(1, 1);
    fout << ans << '\n';

    return 0;
}
