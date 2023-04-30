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
#include <list>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void set_m(int &a, int b) {
    if (a == -1) {
        a = b;
    } else {
        a = min(a, b);
    }
}

bool same(int a, int b, int c) {
    return ((a > c) && (b > c)) || ((a < c) && (b < c));
}

void solve() {
    int n, k; cin >> n >> k;
    map<int, int> cnt;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x]++;
    }

    vector<array<int, 2>> comp;
    for (auto [v, c] : cnt) {
        if (c > k) {
            cout << "-1\n";
            return;
        }

        comp.push_back({v, c});
    }

    // dp to find smallest sequence
    // dp[i][# of set] = prev loc, -1 if not possible
    vector<vector<int>> dp(comp.size(), vector<int>(k + 1, -1)); 
    
    int sz = comp.size();
    for (int i = sz - 1; i >= 0; i--) {
        auto [_, c] = comp[i];

        if (c <= k) {
            dp[i][c] = -2; // marking as done
        }

        for (int j = i + 1; j < sz; j++) {
            for (int a = 0; a <= k; a++) {
                if (a + c <= k && dp[j][a] != -1) {
                    set_m(dp[i][a + c], j);
                }
            }
        }
    }

    list<int> res;
    set<int> in_alr;

    for (int i = 0; i < sz; i++) {
        if (dp[i][k] != -1) {
            // solve from here
            
            int cur = i;
            int tot = k;
            while (cur != -2) {
                auto [v, c] = comp[cur];

                for (int i = 0; i < c; i++) {
                    res.push_back(v);
                }

                in_alr.insert(v);
                cur = dp[cur][tot];
                tot -= c;
            }

            break;
        }
    }

    vector<array<int, 2>> left;

    for (auto [v, c] : cnt) {
        if (!in_alr.count(v)) {
            left.push_back({v, c});
        }
    }

    auto front = res.begin();

    for (int i = (int) left.size() - 1; i >= 0; i--) {
        auto [v, c] = left[i];
        for (int j = 0; j < c; j++) {
            res.push_front(v);
        }
    }

    res.push_back(0); // idk

    if (front != res.begin()) {
        auto cur = prev(front);

        cout << *cur << endl;
        for (int x : res) {
            cout << x << ' ';
        }
        cout << endl;

        while (true) {
            auto nxt = next(cur);
            bool cont = true;

            list<int>::iterator pre;
            if (cur == res.begin()) {
                cont = false;
            } else {
                pre = prev(cur);
            }

            while (nxt != res.end() && next(nxt) != res.end()) {
                if (same(*nxt, *next(nxt), *cur)) {
                    res.insert(nxt, *cur);
                    res.erase(cur);
                    break;
                }
                nxt = next(nxt);
            }
            
            if (!cont) break;
            cur = pre;
            break;
        }

    }

    for (int x : res) {
        if (x > 0) {
            cout << x << ' ';
        }
    }
    cout << '\n';

    // add larger things
    /* int allow = 0; */
    /* for (int i = (int) p.size() - 1; i >= 0; i--) { */
    /*     res.push_front(p[i]); */
    /*     pre.push_front(true); */
    /*     allow++; */

    /*     for (int i = 0; i < (int) left.size(); i++) { */
    /*     /1* for (int i = (int) left.size() - 1; i >= 0; i--) { *1/ */
    /*         auto &[v, c] = left[i]; */
    /*         if (v < p[i]) break; */

    /*         for (int j = 0; j < min(c, allow); j++) { */
    /*             res.push_front(v); */
    /*             pre.push_front(false); */
    /*         } */
    /*         c -= min(c, allow); */

    /*         if (c > 0) break; */
    /*     } */
    /* } */

    /* for (int x : res) { */
    /*     cout << x << ' '; */
    /* } */
    /* cout << '\n'; */
    /* return; */

    /* p = res; */
    /* res.clear(); */

    // add smaller things
    /* allow = 0; */
    /* for (int i = 0; i < (int) p.size(); i++) { */
    /*     int x = p[i]; */
    /*     res.push_back(x); */

    /*     deque<int> to_add; */

    /*     /1* if (pre[i]) { *1/ */
    /*         allow++; */
    /*     /1* } *1/ */

    /*     for (auto &[v, c] : left) { */
    /*         for (int j = 0; j < min(c, allow); j++) { */
    /*             to_add.push_front(v); */
    /*         } */
    /*         c -= min(c, i + 1); */
    /*     } */

    /*     while (!to_add.empty()) { */
    /*         res.push_back(to_add.front()); */
    /*         to_add.pop_front(); */
    /*     } */
    /* } */

    /* for (int x : p) { */
    /*     if (!left.empty() && left.front() > x) { */
    /*         res.push_back(left.front()); */
    /*         left.pop_front(); */
    /*     } */
    /*     res.push_back(x); */
    /* } */

    /* // add remaining in reverse order */
    /* for (int x : left) { */
    /*     res.push_front(x); */
    /* } */

}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
