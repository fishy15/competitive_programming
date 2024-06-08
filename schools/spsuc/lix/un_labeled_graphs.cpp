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
#include <cassert>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int bits_needed(int x) {
    int steps = 0;
    while (x > 0) {
        x /= 2;
        steps++;
    }
    return steps;
}

vector<vector<bool>> construct(int n, int big, vector<vector<bool>> &adj) {
    vector res(big, vector<bool>(big));

    auto bits_len = bits_needed(n-1);
    auto bit = [&](int x) { return n + x; };
    auto p1 = n + bits_len;
    auto p2 = p1 + 1;
    auto start = p2 + 1;

    assert(start < big);

    // copy over graph
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = adj[i][j];
        }
    }

    // present bits
    for (int i = 0; i < n; i++) {
        res[i][p1] = res[p1][i] = 1;
        res[i][p2] = res[p2][i] = 1;
    }

    // bits
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bits_len; j++) {
            if (i & (1 << j)) {
                res[i][bit(j)] = res[bit(j)][i] = 1;
            }
        }
    }

    // chain together bits
    for (int i = 0; i < bits_len - 1; i++) {
        res[bit(i)][bit(i+1)] = res[bit(i+1)][bit(i)] = 1;
    }

    // start node
    res[start][bit(0)] = res[bit(0)][start] = 1;

    return res;
}

vector<vector<bool>> reconstruct(int big, int n, const vector<vector<bool>> &adj) {
    auto bits_len = bits_needed(n-1);

    vector<int> deg(big);
    for (int i = 0; i < big; i++) {
        for (int j = 0; j < big; j++) {
            if (adj[i][j]) {
                deg[i]++;
            }
        }
    }

    // find duplicate
    vector<pair<vector<bool>, int>> n_rows;
    for (int i = 0; i < big; i++) {
        if (deg[i] == n) {
            n_rows.push_back({adj[i], i});
        }
    }

    sort(n_rows.begin(), n_rows.end());
    int p1 = -1;
    for (int i = 0; i < (int) n_rows.size() - 1; i++) {
        if (n_rows[i].first == n_rows[i+1].first) {
            p1 = n_rows[i].second;
            break;
        }
    }

    auto present = adj[p1];
    
    // find start and bits
    int start = -1;
    vector<int> bit;
    set<int> vis;
    for (int i = 0; i < big; i++) {
        if (deg[i] == 1 && !present[i]) {
            int j = find(adj[i].begin(), adj[i].end(), true) - adj[i].begin();
            if (!present[j]) {
                start = i;
                bit.push_back(j);
                vis = {i, j};
                break;
            }
        }
    }

    for (int i = 1; i < bits_len; i++) {
        auto cur = bit.back();
        vis.insert(cur);
        for (int j = 0; j < big; j++) {
            if (!present[j] && adj[cur][j] && !vis.count(j)) {
                bit.push_back(j);
                break;
            }
        }
    }

    vector<int> perm(big);
    for (int i = 0; i < big; i++) {
        if (present[i]) {
            for (int j = 0; j < big; j++) {
                if (adj[i][j] && !present[j]) {
                    auto bit_idx = find(bit.begin(), bit.end(), j) - bit.begin();
                    if (bit_idx != bits_len) {
                        perm[i] += 1 << bit_idx;
                    }
                }
            }
        } else {
            perm[i] = -1;
        }
    }

    vector res(n, vector<bool>(n));
    for (int i = 0; i < big; i++) {
        if (present[i]) {
            for (int j = 0; j < big; j++) {
                if (present[j]) {
                    res[perm[i]][perm[j]] = adj[i][j];
                }
            }
        }
    }

    return res;
}

vector<vector<bool>> shuffle(vector<vector<bool>> adj) {
    int n = (int) adj.size();
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);

    for (int i = 0; i < n; i++) {
        swap(perm[i], perm[rand() % n]);
    }

    vector res(n, vector<bool>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[perm[i]][perm[j]] = adj[i][j];
        }
    }

    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int v1, v2;
    cin >> v1 >> v2;

    vector adj(v1, vector<bool>(v1));
    for (int i = 0; i < v1; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < v1; j++) {
            adj[i][j] = (s[j] == '1');
        }
    }

    vector<vector<bool>> res;
    if (v1 < v2) {
        res = construct(v1, v2, adj);
    } else {
        res = reconstruct(v1, v2, adj);
    }

    for (auto &row : res) {
        for (auto x : row) {
            cout << x;
        }
        cout << '\n';
    }

    return 0;
}
