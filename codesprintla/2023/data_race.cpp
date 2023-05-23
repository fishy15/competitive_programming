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

#define int ll

struct event {
    int t;
    int val;
};

struct counter {
    map<int, int> cnt;

    void add(int x) {
        cnt[x]++;
    }

    bool rem(int x) {
        cnt[x]--;
        if (cnt[x] == 0) {
            cnt.erase(x);
        }
        
        return cnt.size() == 0;
    }

    bool all_distinct() const {
        return cnt.size() == 1;
    }

    int get() const {
        return cnt.begin()->first;
    }
};

signed main() {
    cin.tie(0)->sync_with_stdio(0);

    int t, n, a;
    cin >> t >> n >> a;

    vector<array<int, 4>> threads(t);
    for (int i = 0; i < t; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        threads[i] = {a, b, c, d};
    }

    map<int, vector<event>> events_add, events_rem;
    for (auto &[t, p, v, a] : threads) {
        if (v > n) {
            int ignore = v - n;
            t += ignore;
            (p += ignore) %= n;
            v -= ignore;
        }

        events_add[p].push_back({t, a});

        int end = p + v - 1;
        if (end < n) {
            events_rem[end].push_back({t + v - 1, a});
        } else {
            int until_end = n - p;
            int after_end = v - until_end;
            events_rem[n - 1].push_back({t + until_end - 1, a});
            events_add[0].push_back({t + until_end, a});
            events_rem[after_end - 1].push_back({t + v - 1, a});
        }
    }

    events_add[0].push_back({-INFLL, 0});
    events_rem[n - 1].push_back({-INFLL + n - 1, 0});

    vector<int> important;
    for (const auto &[x, _] : events_add) important.push_back(x);
    for (const auto &[x, _] : events_rem) important.push_back(x);

    sort(important.begin(), important.end());
    important.erase(unique(important.begin(), important.end()), important.end());

    map<int, counter> m;
    vector<int> ans(a + 1);
    int sz = important.size();
    for (int i = 0; i < sz; i++) {
        int p = important[i];
        for (auto [t, val] : events_add[p]) {
            m[t - p].add(val);
        }

        auto &latest = m.rbegin()->second;
        if (latest.all_distinct()) {
            ans[latest.get()]++;
        } else {
            ans[a]++;
        }

        for (auto [t, val] : events_rem[p]) {
            auto res = m[t - p].rem(val);
            if (res) {
                m.erase(t - p);
            }
        }

        if (i != sz - 1) {
            int until_nxt = important[i + 1] - p - 1;
            auto &latest = m.rbegin()->second;
            if (latest.all_distinct()) {
                ans[latest.get()] += until_nxt;
            } else {
                ans[a] += until_nxt;
            }
        }
    }

    for (auto x : ans) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}
