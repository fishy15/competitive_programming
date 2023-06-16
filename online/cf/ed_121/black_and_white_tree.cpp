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
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 300010

using namespace std;

int n;
bool black[MAXN];
vector<int> adj[MAXN];

// 0 - nothing, 1 - black in subtree, 2 - works
int state[MAXN]; 
bool ans[MAXN];

template<typename T>
T ckmax(T &a, T b) {
    return a = max(a, b);
}

void dfs(int v, int p) {
    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v);
            if (state[e] == 2) {
                ckmax(state[v], 2);
            } else if (state[e] == 1) {
                if (black[v]) {
                    ckmax(state[v], 2);
                } else {
                    ckmax(state[v], 1);
                }
            }
        }
    }

    if (state[v] == 0 && black[v]) {
        state[v] = 1;
    }

    // set neighbors to work
    if (black[v]) {
        for (int e : adj[v]) {
            ans[e] = true;
        }
    }
}

void dfs_reroot(int v, int p, int pstate) {
    if (state[v] == 2 || pstate == 2 || black[v]) {
        ans[v] = true;
    }

    int cnt[3] = {0, 0, 0};
    for (int e : adj[v]) {
        if (e != p) {
            cnt[state[e]]++;
        }
    }

    cnt[pstate]++;

    for (int e : adj[v]) {
        if (e != p) {
            cnt[state[e]]--;

            if (cnt[2] > 0 || (cnt[1] > 0 && black[v])) {
                dfs_reroot(e, v, 2);
            } else if (cnt[1] > 0 || black[v]) {
                dfs_reroot(e, v, 1);
            } else {
                dfs_reroot(e, v, 0);
            }

            cnt[state[e]]++;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        black[i] = (x == 1);
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, 0);
    if (state[0] == 2) {
        ans[0] = true;
    }

    dfs_reroot(0, 0, 0);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';

    return 0;
}
