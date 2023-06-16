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

struct ColorMem {
    vector<set<pair<int, int>>> color;

    ColorMem(int n) : color(n) {}

    void add_at_color(int c, int x, int dir) {
        color[c].insert({x, dir});
    }

    void join(int x, int y, vector<int> &times, int t) {
        int old_x = x;

        if (color[x].size() <= color[y].size()) {
            swap(x, y);
        }

        for (auto [loc, dir] : color[y]) {
            if (dir == 0) {
                auto it = color[x].find({loc - 1, 1});
                if (it != color[x].end()) {
                    color[x].erase(it);
                    times[loc - 1] = t;
                } else {
                    color[x].insert({loc, dir});
                }
            } else {
                auto it = color[x].find({loc + 1, 0});
                if (it != color[x].end()) {
                    color[x].erase(it);
                    times[loc] = t;
                } else {
                    color[x].insert({loc, dir});
                }
            }
        }

        color[y].clear();

        if (old_x == x) {
            swap(color[x], color[y]);
        }
    }
};

int get_ans(int n, int k, vector<int> &times, multiset<int> &ms) {
    int cur = k;
    while (cur < n) {
        ms.erase(ms.find(times[cur - 1]));
        cur += k;
    }

    int ans;
    if (ms.empty()) {
        ans = 0;
    } else {
        ans = (*ms.begin() == -1) ? -1 : *ms.rbegin();
    }

    cur = k;
    while (cur < n) {
        ms.insert(times[cur - 1]);
        cur += k;
    }

    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> join(n - 1, -1);
    ColorMem cm(n);

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            cm.add_at_color(i - 1, i - 1, 1);
            cm.add_at_color(i, i, 0);
        }
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        cm.join(a, b, join, i + 1);
    }

    multiset<int> ms;
    for (int x : join) ms.insert(x);

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += get_ans(n, i, join, ms);
    }

    cout << ans << '\n';;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
