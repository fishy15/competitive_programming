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
#define MAXN 2001

using namespace std;

int n;
vector<int> adj[MAXN];
int p[MAXN];
int c[MAXN];
int cur[MAXN];
int val[MAXN];
int t = 1;
int d[MAXN];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

void dfs(int i, int dd) {
    if (c[i] == 0) {
        q.push({dd, i});
    }

    d[i] = dd;

    for (int x : adj[i]) {
        dfs(x, dd + 1);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    int root = 0;
    
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        p[i + 1] = a;
        adj[a].push_back(i + 1);
        c[i + 1] = b;
        if (a == 0) {
            root = i + 1;
        }
    }

    dfs(root, 1);
    int vis = 0;

    while (!q.empty()) {
        vector<int> to_add;
        int qq = q.top().second;
        q.pop();
        val[qq] = t++; 
        qq = p[qq];
        while (qq > 0) {
            if (!val[qq]) {
                if (c[qq] == 1) {
                    to_add.push_back(qq);
                }
                c[qq]--;
            }
            qq = p[qq];
        }
        for (int i = to_add.size() - 1; i >= 0; i--) {
            q.push({d[to_add[i]], to_add[i]});
        }
        vis++;
    }

    if (vis != n) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int i = 1; i <= n; i++) {
            cout << val[i] << ' ';
        }
    }

    return 0;
}
