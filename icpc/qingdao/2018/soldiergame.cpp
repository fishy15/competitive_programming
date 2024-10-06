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

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

struct node {
    array<array<ll, 2>, 2> best;

    node() {
        best[0] = {INFLL, INFLL};
        best[1] = {INFLL, INFLL};
    }

    void pr() const {
        cout << best[0][0] << ' ' << best[0][1] << '\n';
        cout << best[1][0] << ' ' << best[1][1] << '\n';
    }
};

node comb(node a, node b, array<ll, 2> pass1, array<ll, 2> pass2) {
    node res;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            ckmin(res.best[i][j], max({a.best[i][0], pass1[1], b.best[0][j]}));
            ckmin(res.best[i][j], max({a.best[i][1], pass2[0], b.best[0][j]}));
            ckmin(res.best[i][j], max({a.best[i][1], pass2[1], b.best[1][j]}));
        }
    }
    return res;
}

struct segtree {
    int n;
    vector<node> st;

    segtree(int n) : n(n), st(4 * n) {}

    void upd(int x, const vector<array<ll, 2>> &edges) { upd(1, 0, n, x, edges); }
    void upd(int v, int l, int r, int x, const vector<array<ll, 2>> &edges) {
        if (r - l == 2) {
            node new_node;
            new_node.best[0][0] = -INFLL;
            new_node.best[0][1] = edges[l][0];
            new_node.best[1][0] = INFLL;
            new_node.best[1][1] = -INFLL;
            st[v] = new_node;
        } else if (r - l == 3) {
            node new_node;
            new_node.best[0][0] = edges[l][0];
            new_node.best[0][1] = min(max(edges[l][0], edges[l+1][0]), edges[l][1]);
            new_node.best[1][0] = -INFLL;
            new_node.best[1][1] = edges[l+1][0];
            st[v] = new_node;
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                upd(2*v, l, m, x, edges);
            } else {
                upd(2*v+1, m, r, x, edges);
            }

            array<ll, 2> pass1, pass_end;
            pass_end = edges[m-1];
            pass1 = edges[m-2];

            st[v] = comb(st[2*v], st[2*v+1], pass1, pass_end);
        }

        /*cout << "new val: " << l << ' ' << r << ' ' << endl;*/
        /*st[v].pr();*/
    }

    ll qry() const {
        return st[1].best[0][1];
    }
};

ll slow(int n, vector<array<ll, 2>> edges) {
    vector<ll> best(n+1, INFLL);
    best[0] = -INFLL;
    for (int i = 0; i < n; i++) {
        ckmin(best[i+1], max(best[i], edges[i][0]));
        if (i > 0) ckmin(best[i+1], max(best[i-1], edges[i-1][1]));
    }
    return best.back();
}

void solve() {
    int n;
    cin >> n;

    int seed = 0;
    while (true) {
        srand(seed);
        cout << seed << endl;

        vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            nums[i] = rand() % 20;
        }

        // {start, typ}
        // 0 = single
        // 1 = double
        map<int, vector<pair<int, int>>> locs;
        vector<array<int, 2>> edges(n);

        for (int i = 0; i < n; i++) {
            locs[nums[i]].push_back({i, 0});
            edges[i][0] = nums[i];
            edges[i][1] = INFLL;
            if (i < n - 1) {
                locs[nums[i] + nums[i+1]].push_back({i, 1});
                edges[i][1] = nums[i] + nums[i+1];
            }
        }


        segtree st(n+1);
        for (int i = 0; i <= n; i++) {
            st.upd(i, edges);
        }

        for (auto &[lo, idx] : locs) {
            auto hi = st.qry();

            auto b = slow(n, edges);
            if (hi != b) {
                cout << "breaks on array:\n";
                cout << "brute: " << b << ' ' << "me: " << hi << endl;
                cout << "edges:\n";
                for (int i = 0; i < n; i++) {
                    cout << edges[i][0] << ' ' << edges[i][1] << '\n';
                }
                return;
            }

            for (auto [x, i] : idx) {
                edges[x][i] = INFLL;
                st.upd(x, edges);
                if (x > 0) st.upd(x-1, edges);
                if (x < n) st.upd(x+1, edges);
            }
        }

        seed++;
    }

    return;
    
    vector<int> nums(n);
    for (auto &x : nums) {
        cin >> x;
    }

    // {start, typ}
    // 0 = single
    // 1 = double
    map<int, vector<pair<int, int>>> locs;
    vector<array<int, 2>> edges(n);

    for (int i = 0; i < n; i++) {
        locs[nums[i]].push_back({i, 0});
        edges[i][0] = nums[i];
        edges[i][1] = INFLL;
        if (i < n - 1) {
            locs[nums[i] + nums[i+1]].push_back({i, 1});
            edges[i][1] = nums[i] + nums[i+1];
        }
    }


    segtree st(n+1);
    for (int i = 0; i <= n; i++) {
        st.upd(i, edges);
    }

    /*cout << "done preset" << endl;*/

    int ans = INFLL;
    for (auto &[lo, idx] : locs) {
        auto hi = st.qry();
        ckmin(ans, hi - lo);

        /*cout << lo << ' ' << hi << endl;*/

        for (auto [x, i] : idx) {
            edges[x][i] = INFLL;
            st.upd(x, edges);
            if (x > 0) st.upd(x-1, edges);
            if (x < n) st.upd(x+1, edges);
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
