/*
 * We can solve recursively by keeping track of how many lower-level employees are within the current 
 * subtree. If there is one, then we have reached the end. Otherwise, we can find the maximum value of 
 * the LCAs within the set, which is the value of the root of the subtree. We can then split the set of
 * lower-level employees to subgroups that have a smaller value for their LCA.
 */
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
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 510

using namespace std;

int n;
int lca_v[MAXN][MAXN];
int cur_sz;
vector<pair<int, int>> edge;
vector<int> val;

int solve(vector<int> cur, int p) {
    if ((int)(cur.size()) == 1) {
        if (p != -1) {
            edge.push_back({p, cur[0]});
        }
        return cur[0];
    }

    int max_val = 0;
    for (int i : cur) {
        for (int j : cur) {
            max_val = max(max_val, lca_v[i][j]);
        }
    }

    int root = cur_sz;
    if (p != -1) {
        edge.push_back({p, root});
    }
    val.push_back(max_val);
    cur_sz++;

    vector<int> set1, set2;
    while (true) {
        for (int i : cur) {
            if (lca_v[cur[0]][i] == max_val) {
                set2.push_back(i);
            } else {
                set1.push_back(i);
            }
        }
        
        solve(set1, root);

        if (set2.empty()) {
            break;
        }

        cur = set2;
        set1.clear();
        set2.clear();
    }

    return root;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> lca_v[i][j];
        }
    }

    vector<int> cur_last;
    for (int i = 0; i < n; i++) {
        val.push_back(lca_v[i][i]);
        cur_last.push_back(i);
    }

    cur_sz = n;
    int root = solve(cur_last, -1);

    cout << cur_sz << '\n';
    for (int i : val) {
        cout << i << ' ';
    }
    cout << '\n';

    cout << root + 1 << '\n';

    for (auto [x, y] : edge) {
        cout << y + 1 << ' ' << x + 1 << '\n';
    }

    return 0;
}
