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
#define MAXN 1000000

using namespace std;

int n;
vector<int> adj[MAXN + 1];

bool ok(const vector<int> &v, int skip, int k) {
    int l = 0;
    int r = (int)(v.size()) - 1;
    if (l == skip) l++;
    if (r == skip) r--;
    while (l <= r) {
        int val = v[l] + v[r];
        if (l == r) val = v[l];
        if (val < k) return false;
        l++;
        r--;
        if (l == skip) l++;
        if (r == skip) r--;
    }
    return true;
}

int dfs(int v, int p, int k) {
    vector<int> odd;
    vector<int> even = {0};
    for (int e : adj[v]) {
        if (e != p) {
            int x = dfs(e, v, k);
            if (x == -1) {cout << v << ' ' << k << " -1\n";return -1;}
            odd.push_back(x + 1);
            even.push_back(x + 1);
        }
    }

    sort(odd.begin(), odd.end());
    sort(even.begin(), even.end());

    if (odd.size() % 2 == 0) {
        swap(odd, even);
    }

    int l = 0;
    int r = odd.size() - 1;
    int a = -1;

    // no skip
    if (ok(even, -1, k)) {
        a = 0;
    }

    if (v == 1) return a;

    while (l <= r) {
        int m = l + (r - l) / 2;
        bool res = ok(odd, m, k);
        if (res) {
            a = odd[m];
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    
    // cout << v << ' ' << k << ' ' << a << '\n';
    return a;
}

bool check(int k) {
    bool res = dfs(1, 1, k);
    return res == 0;
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

    int l = 1;
    int r = n;
    int ans = -1;

    while (l <= r) {
        int m = l + (r - l) / 2;
        bool res = check(m);
        if (res) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    fout << ans << '\n';

    return 0;
}
