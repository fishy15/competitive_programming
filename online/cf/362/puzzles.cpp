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
#define MAXN 1000000

using namespace std;

struct tree {
    int n;
    vector<vector<int>> child;
    vector<int> two_ans;
    vector<int> sz;

    tree(int n) : n(n), child(n), two_ans(n), sz(n) {}

    void dfs_sz(int v = 0) {
        sz[v] = 1;
        for (auto e : child[v]) {
            dfs_sz(e);
            sz[v] += sz[e];
        }
    }

    void dfs_ans(int v = 0) {
        for (auto e : child[v]) {
            int rest_sz = sz[v] - sz[e] - 1;
            two_ans[e] = two_ans[v] + rest_sz + 2;
            dfs_ans(e);
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    tree t(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        t.child[p].push_back(i);
    }

    t.dfs_sz();
    t.two_ans[0] = 2;
    t.dfs_ans();

    for (auto x : t.two_ans) {
        if (x % 2 == 0) {
            cout << (x / 2) << ".0 ";
        } else {
            cout << (x / 2) << ".5 ";
        }
    }
    cout << '\n';

    return 0;
}
