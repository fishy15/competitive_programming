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
#define MAXN 400010

using namespace std;

int n;
vector<int> adj[MAXN];
int in[MAXN];
int out[MAXN];
int vals[MAXN];
int nums[MAXN];
int bit[MAXN];
int ans[MAXN];
vector<array<int, 3>> qq;
map<int, vector<int>> ord;
map<int, int> idx;
int t;

void upd(int x, int v) {
    while (x < MAXN) {
        bit[x] += v;
        x += x & -x;
    }
}

int qry(int x) {
    int res = 0;
    while (x) {
        res += bit[x];
        x -= x & -x;
    }
    return res;
}

void dfs(int v, int p) {
    in[v] = ++t; 
    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v);
        }
    }
    out[v] = ++t;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> vals[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, 0);

    for (int i = 0; i < n; i++) {
        nums[in[i]] = vals[i];
        ord[nums[in[i]]].push_back(in[i]);
    }

    for (auto it = ord.begin(); it != ord.end(); it++) {
        sort(it->second.begin(), it->second.end());
    }

    for (int i = 0; i < n; i++) {
        qq.push_back({in[i], out[i], i});
    }

    sort(qq.begin(), qq.end(), [](const array<int, 3> &a, const array<int, 3> &b) {
        if (a[1] == b[1]) return a < b;
        return a[1] < b[1];
    });

    int pos = 0;
    for (int i = 1; i <= 2 * n; i++) {
        if (nums[i]) upd(i, 1);
        if (nums[i] && idx[nums[i]] > 0) {
            upd(ord[nums[i]][idx[nums[i]] - 1], -1);
        }
        while (pos < n && qq[pos][1] == i) {
            ans[qq[pos][2]] = qry(qq[pos][1]) - qry(qq[pos][0] - 1);
            pos++;
        }
        idx[nums[i]]++;
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';

    return 0;
}
