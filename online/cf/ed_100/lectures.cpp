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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 300010

using namespace std;

int n, k;
vector<int> adj[MAXN];

int dsu[MAXN];
int sz[MAXN];
int in[MAXN];
int out[MAXN];
int in2[MAXN];

vector<int> adj2[MAXN];

int pp[MAXN];
int nxt[MAXN];
int pos[MAXN];
bool bad = false;

vector<int> get_seq(int x) {
    int cnt = 0;
    vector<int> ans;
    int cur = x;
    while (pp[cur] != -1) {
        cnt++;
        if (cnt > n) {
            bad = true;
            return ans;
        }
        cur = pp[cur];
    }
    while (cur != -1) {
        ans.push_back(cur);
        cur = nxt[cur];
    }
    return ans;
}

int find(int x) {
    if (x == dsu[x]) return x;
    return dsu[x] = find(dsu[x]);
}

void join(int i, int j) {
    if ((i = find(i)) != (j = find(j))) {
        if (sz[i] < sz[j]) swap(i, j);
        dsu[j] = dsu[i];
        sz[i] += sz[j];
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        adj[x].push_back(i + 1);
    }

    memset(pp, -1, sizeof pp);
    memset(nxt, -1, sizeof nxt);

    for (int i = 0; i <= n; i++) {
        dsu[i] = i;
        sz[i] = 1;
    }

    for (int i = 0; i < k; i++) {
        int a, b; cin >> a >> b;
        out[a]++;
        in[b]++;
        join(a, b);
        nxt[a] = b;
        pp[b] = a;
    }

    for (int i = 1; i <= n; i++) {
        if (in[i] > 1 || out[i] > 1) {
            cout << "0\n";
            return 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int x : adj[i]) {
            if (find(i) != find(x)) {
                adj2[find(i)].push_back(find(x));
                in2[find(x)]++;
            }
        }
    }

    queue<int> cur;
    for (int i = 1; i <= n; i++) {
        if (i == find(i) && in2[i] == 0) {
            cur.push(i);
        }
    }

    vector<int> ans;
    while (!cur.empty()) {
        int t = cur.front();
        cur.pop();
        ans.push_back(t);
        for (int x : adj2[t]) {
            in2[x]--;
            if (!in2[x]) cur.push(x);
        }
    }

    vector<int> ans2;
    for (int x : ans) {
        vector<int> ret = get_seq(x);
        if (bad) {
            cout << "0\n";
            return 0;
        }
        for (int y : ret) ans2.push_back(y);
    }

    if (ans2.size() < n) {
        cout << "0\n";
        return 0;
    }

    for (int i = 0; i < n; i++) {
        pos[ans2[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        for (int x : adj[i]) {
            if (pos[i] > pos[x]) {
                cout << "0\n";
                return 0;
            }
        }
    }

    for (int x : ans2) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}
