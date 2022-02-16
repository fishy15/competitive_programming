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
    vector<vector<int>> adj;

    tree(int n) : n(n), adj(n) {}

    void add_edge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    pair<int, int> max_d(int v, int p) {
        pair<int, int> ans = {0, v};
        for (int e : adj[v]) {
            if (e != p) {
                ans = max(ans, max_d(e, v));
            }
        }
        return {ans.first + 1, ans.second};
    }

    int get_d() {
        auto [d, v] = max_d(0, 0);
        return max_d(v, v).first;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int v1, v2; cin >> v1;
    tree t1(v1);

    for (int i = 0; i < v1 - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        t1.add_edge(a, b);
    }

    cin >> v2;
    tree t2(v2);

    for (int i = 0; i < v2 - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        t2.add_edge(a, b);
    }

    cout << t1.get_d() + t2.get_d() << '\n';

    return 0;
}
