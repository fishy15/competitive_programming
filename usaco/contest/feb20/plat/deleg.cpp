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
#define MAXN 100000

using namespace std;

int n;
int qq;
vector<int> adj[MAXN + 1];
vector<int> len;

int dfs(int v, int p) {
    int ans = 0;
    for (int e : adj[v]) {
        if (v == qq) {
            len.push_back(dfs(e, v) + 1);
        } else if (e != p) {
            ans += dfs(e, v) + 1;
        }
    }

    return ans;
}

int main() {
    ifstream fin("deleg.in");
    ofstream fout("deleg.out");

    fin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; fin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int q = INF;
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() > 2) {
            qq = i;
            q = min(q, qq);
        }
    }

    dfs(qq, 0);

    if (q == qq) {
        sort(len.begin(), len.end());
    } 

    int a1 = INF;

    for (int i = 0; i < len.size(); i++) {
        // cout << len[i] << ' ' ;
        if (i + i + 1 != len.size()) {
            a1 = min(a1, len[i] + len[len.size() - i - 1]);
        } else {
            a1 = min(a1, len[i]);
        }
    }

    int a2 = len[len.size() - 1];

    for (int i = 0; i < len.size() - 1; i++) {
        a2 = min(a2, len[i] + len[len.size() - i - 2]);
    }

    fout << max(a1, a2) << '\n';
    return 0;
}
