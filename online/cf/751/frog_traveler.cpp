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

struct segtree {
    int n;
    vector<pair<int, int>> st;

    segtree(int n) : n(n), st(2 * n, {INF, -1}) {}
    segtree(int n, vector<int> &nums) : segtree(n) { 
        for (int i = 0; i < n; i++) {
            st[i + n] = {i - nums[i], i};
        }
        for (int i = n - 1; i > 0; i--) {
            st[i] = min(st[i << 1], st[i << 1 | 1]);
        }
    }

    void upd(int x, int y) { 
        pair<int, int> val = {y, x};
        x += n;
        st[x] = val;
        while (x > 1) {
            st[x >> 1] = min(st[x], st[x ^ 1]);
            x >>= 1;
        }
    }

    pair<int, int> qry(int l, int r) const {
        pair<int, int> ans = {INF, -1};
        l += n;
        r += n;
        while (l < r) {
            if (l & 1) {
                ans = min(ans, st[l]);
                l++;
            }

            if (r & 1) {
                r--;
                ans = min(ans, st[r]);
            }

            l >>= 1;
            r >>= 1;
        }
        return ans;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }

    vector<int> b(n);
    for (auto &x : b) {
        cin >> x;
    }

    a.insert(a.begin(), 0);
    b.insert(b.begin(), 0);

    segtree present_ints(n + 1, a);
    
    vector<vector<int>> unslip(n + 1);
    for (int i = 0; i < n + 1; i++) {
        unslip[i + b[i]].push_back(i);
    }

    vector<int> d(n + 1, INF);
    vector<int> move(n + 1, -1);

    vector<bool> vis(n + 1);
    queue<pair<int, int>> q;

    auto push_if = [&](int x, int dd, int y) {
        if (!vis[x]) {
            vis[x] = true;
            q.push({x, dd});
            move[x] = y;
        }
    };

    auto set = [&](int x, int dist) {
        pair<int, int> res;
        for (auto y : unslip[x]) {
            while ((res = present_ints.qry(y, n + 1)).first <= y) {
                auto px = res.second;
                d[px] = dist + 1;

                present_ints.upd(res.second, INF);
                push_if(px, dist + 1, y);
            }
        }
    };

    push_if(0, 0, -1);
    while (!q.empty()) {
        auto [x, dd] = q.front();
        q.pop();
        set(x, dd);
    }

    if (d[n] == INF) {
        cout << "-1\n";
    } else {
        cout << d[n] << '\n';

        int cur = n;
        while (cur != 0) {
            cur = move[cur];
            cout << cur << ' ';
            cur += b[cur];
        }
        cout << '\n';
    }


    return 0;
}
