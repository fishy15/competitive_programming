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

int n;
vector<int> adj[MAXN];
ll cost[MAXN];
int init[MAXN];
int want[MAXN];
ll answer;

void dfs(int v, int p) {
    cost[v] = min(cost[v], cost[p]);
    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v);
        }
    }
}

pair<int, int> dfs2(int v, int p) {
    pair<int, int> ans = {0, 0};
    for (int e : adj[v]) {
        if (e != p) {
            auto res = dfs2(e, v); 
            ans.first += res.first;
            ans.second += res.second;
        }
    }

    if (init[v] != want[v]) {
        if (init[v]) {
            ans.first++;
        } else {
            ans.second++;
        }
    }

    int rem = min(ans.first, ans.second);
    answer += 2 * rem * cost[v];
    ans.first -= rem;
    ans.second -= rem;

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> cost[i] >> init[i] >> want[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, 0);
    auto res = dfs2(0, 0);

    if (res.first || res.second) {
        cout << -1 << '\n';
    } else {
        cout << answer << '\n';
    }

    return 0;
}
