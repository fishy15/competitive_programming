/*
 * Let's take a look at all of strings that have the same prefix of a certain length. For the next character,
 * all of the ones with the same character need to be next to each other. If the prefix is the entire string,
 * then this must appear before all of the other strings that start with the same prefix. We can then form
 * a graph of implications (desribed below), and then we can recurse onto each set of strings with the same
 * prefix of length + 1.
 *
 * In order to form the set of implications, we can compare each pair of adjacent strings. If they have the
 * same character after the prefix, we can ignore. Otherwise, suppose that the first string has letter A
 * and the second string has letter B. We then have two cases: if A < B, then lowercase A implies 
 * lowercase B and uppercase B implies uppercase A. If A > B, then the only pair that works is lowercase 
 * B and uppercase A. After forming this graph of implications, we can check a lowercase and an uppercase
 * ever imply each other by calculating the SCC of the graph and seeing if they are in the same component
 * (similar to 2-SAT). We can then assign similarly to how we assign components for 2-SAT to calculate the
 * answer if valid.
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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100010

using namespace std;

int n, m;
bool impossible;
vector<int> nums[MAXN];
int first_idx[MAXN];
int last_idx[MAXN]; // stores prev index for each, reset after each run

struct SCC {
    int sz;
    vector<vector<int>> adj;
    vector<vector<int>> radj;
    vector<int> comp;
    vector<bool> vis;
    vector<int> ord;
    vector<int> cur_comp;

    void init(int m) {
        sz = 2 * m + 2;
        adj.resize(sz);
        radj.resize(sz);
        comp.resize(sz);
        vis.resize(sz);
    }

    void add_edge(int a, int b) {
        adj[a].push_back(b);
        radj[b].push_back(a);
    }

    void dfs_ord(int v) {
        vis[v] = true;
        for (int e : adj[v]) {
            if (!vis[e]) {
                dfs_ord(e);
            }
        }
        ord.push_back(v);
    }

    void dfs_scc(int v) {
        vis[v] = true;
        cur_comp.push_back(v);
        for (int e : radj[v]) {
            if (!vis[e]) {
                dfs_scc(e);
            }
        }
    }

    void find_scc() {
        for (int i = 2; i < sz; i++) {
            if (!vis[i]) {
                dfs_ord(i);
            }
        }

        fill(vis.begin(), vis.end(), false);
        reverse(ord.begin(), ord.end());

        int cnt = 0;
        for (int v : ord) {
            if (!vis[v]) {
                cur_comp = {};
                dfs_scc(v);
                for (int i : cur_comp) {
                    comp[i] = cnt;
                }
                cnt++;
            }
        }
    }
} scc;

int get_num(int i, int k) {
    return k >= (int)(nums[i].size()) ? 0 : nums[i][k];
}

void create_graph(int l, int r, int k) {
    if (impossible) return;
    if (l == r) return;
    int max_len = 0;

    for (int i = l; i <= r; i++) {
        max_len = max(max_len, (int)(nums[i].size()));
    }
    if (max_len <= k) return;
    
    for (int i = l; i <= r; i++) {
        int num = get_num(i, k);
        if (last_idx[num] != -1 && last_idx[num] != i - 1) {
            impossible = true;
            return;
        }

        if (first_idx[num] == -1) {
            first_idx[num] = i;
        }
        last_idx[num] = i;
    }

    for (int i = l + 1; i <= r; i++) {
        int pnum = get_num(i - 1, k);
        int num = get_num(i, k);

        if (pnum != 0) {
            if (num == 0) {
                impossible = true;
                return;
            } else if (pnum < num) {
                scc.add_edge(2 * pnum, 2 * num);
                scc.add_edge(2 * num + 1, 2 * pnum + 1);
            } else if (pnum > num) {
                scc.add_edge(2 * pnum + 1, 2 * num);
                scc.add_edge(2 * num, 2 * pnum + 1);

                // representing impossible cases
                scc.add_edge(2 * pnum, 2 * pnum + 1);
                scc.add_edge(2 * num + 1, 2 * num);
            }
        }
    }

    // reset the values for subqueries and create subqueries
    vector<pair<int, int>> queries;
    for (int i = l; i <= r; i++) {
        int num = get_num(i, k);
        if (first_idx[num] != -1) {
            queries.push_back({first_idx[num], last_idx[num]});
        }
        first_idx[num] = -1;
        last_idx[num] = -1;
    }

    for (auto [f, l] : queries) {
        create_graph(f, l, k + 1);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int k; cin >> k;
        for (int j = 0; j < k; j++) {
            int x; cin >> x;
            nums[i].push_back(x);
        }
    }

    impossible = false;
    fill(first_idx, first_idx + m + 1, -1);
    fill(last_idx, last_idx + m + 1, -1);
    scc.init(m);
    create_graph(0, n - 1, 0);

    if (impossible) {
        cout << "No\n";
        return 0;
    }

    scc.find_scc();

    // check if possible and figure out capitals
    vector<int> capital;
    for (int i = 1; i <= m; i++) {
        if (scc.comp[2 * i] == scc.comp[2 * i + 1]) {
            cout << "No\n";
            return 0;
        } else if (scc.comp[2 * i] < scc.comp[2 * i + 1]) {
            capital.push_back(i);
        }
    }

    cout << "Yes\n";
    cout << capital.size() << '\n';
    if (!capital.empty()) {
        for (int i : capital) {
            cout << i << ' ';
        }
        cout << '\n';
    }

    return 0;
}
