/*
 * We can separately solve for each connected component in the graph. First of all, it is impossible for there
 * to be three paths between two nodes without there being fourth paths between two other nodes. A single 
 * cycle on its own creates a maximum of two paths between some two nodes. The next step up is having two
 * cycles, but this allows for four paths. Therefore, there is no possible graph if three is given in the 
 * input.
 *
 * Now, we can construct the graph. We can separate the graph into components that have only one path 
 * between themselves, which can be represented. We can then create a cycle that connects these components
 * if multiple exist. If there are only two components, then we cannot create this cycle, so we have to mark
 * the graph as impossible in this case. Finally, we need to check if the rest of the information given is 
 * consistent.
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

#include "supertrees.h"

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

struct DSU {
    vector<int> dsu;
    vector<int> sz;

    DSU(int n) {
        dsu.resize(n);
        sz.resize(n);
        iota(dsu.begin(), dsu.end(), 0);
        fill(sz.begin(), sz.end(), 1);
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            dsu[y] = x;
            sz[x] += sz[y];
        }
    }
};

bool solve_comp(const vector<vector<int>> &p, const vector<int> &comp, vector<pair<int, int>> &edges) {
    int n = p.size();
    DSU one_same(n); 

    for (int i : comp) {
        for (int j : comp) {
            if (p[i][j] == 0) {
                return false;
            } else if (p[i][j] == 1) {
                one_same.join(i, j);
            }
        }
    }

    vector<vector<int>> one_comp(n);
    for (int i : comp) {
        one_comp[one_same.find(i)].push_back(i);
    }

    // check if each thing in the "line" is reachable from one another
    int first_c = -1;
    int prev_c = -1;
    int cnt = 0;
    for (auto &v : one_comp) {
        if (v.empty()) continue;

        cnt++;
        for (int i : v) {
            for (int j : v) {
                if (p[i][j] != 1) {
                    return false;
                }
            }
        }

        int prev = -1;
        for (int i : v) {
            if (prev != -1) {
                edges.push_back({i, prev});
            }
            prev = i;
        }

        if (prev_c != -1) {
            edges.push_back({v[0], prev_c});
        }

        if (cnt == 1) first_c = v[0];
        prev_c = v[0];
    }

    if (cnt == 2) {
        return false;
    } 

    if (cnt >= 3) {
        edges.push_back({first_c, prev_c});
    }

    return true;
}

int construct(vector<vector<int>> p) {
    int n = p.size();

    DSU same_comp(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (p[i][j] == 3) {
                return 0;
            } else if (p[i][j] > 0) {
                same_comp.join(i, j);
            }
        }
    }

    vector<vector<int>> comp(n);
    for (int i = 0; i < n; i++) {
        comp[same_comp.find(i)].push_back(i);
    }

    vector<pair<int, int>> edge;
    bool ok = true;
    for (auto &v : comp) {
        if (!v.empty()) {
            bool res = solve_comp(p, v, edge);
            if (!res) {
                ok = false;
                break;
            }
        }
    }

    if (ok) {
        vector<vector<int>> ans(n, vector<int>(n));
        for (auto [x, y] : edge) {
            ans[x][y] = 1;
            ans[y][x] = 1;
        }
        build(ans);
        return 1;
    } else {
        return 0;
    }
}
