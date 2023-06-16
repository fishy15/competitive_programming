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

struct vals {
    map<int, ll> sum;
    map<int, int> cnt;
};

int n;
int c[MAXN];
ll ans[MAXN];
vector<int> adj[MAXN];

vals dfs(int v, int p) {
    vals cur;
    for (int e : adj[v]) {
        if (e != p) {
            vals res = dfs(e, v);
            if (res.cnt.size() > cur.cnt.size()) swap(res, cur);
            for (auto p : res.cnt) {
                if (!cur.cnt.count(p.first)) {
                    cur.cnt[p.first] = p.second;
                    cur.sum[p.second] += p.first;
                } else {
                    cur.sum[cur.cnt[p.first]] -= p.first;
                    cur.cnt[p.first] += p.second;
                    cur.sum[cur.cnt[p.first]] += p.first;
                }
            }
        }
    }

    if (!cur.cnt.count(c[v])) {
        cur.cnt[c[v]] = 1;
        cur.sum[1] += c[v];
    } else {
        cur.sum[cur.cnt[c[v]]] -= c[v];
        cur.cnt[c[v]]++;
        cur.sum[cur.cnt[c[v]]] += c[v];
    }

    ans[v] = cur.sum.rbegin()->second;
    return cur;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, -1);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';

    return 0;
}
