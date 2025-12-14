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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k, q;
    cin >> n >> k >> q;

    vector<array<int, 3>> trips(q);
    for (auto &[a, b, c] : trips) {
        cin >> a >> b >> c;
        a--;
        b--;
        c--;
    }

    vector<bool> keys_needed(q);
    set<int> at_home;
    rep(i, 0, n) {
        at_home.insert(i);
    }

    // t, typ, idx
    vector<array<int, 3>> events;
    rep(i, 0, q) {
        auto [_, l, r] = trips[i];
        events.push_back({l, +1, i});
        events.push_back({r, -1, i});
    }

    sort(all(events));
    for (auto [_, typ, idx] : events) {
        auto p = trips[idx][0];
        if (typ == +1) {
            at_home.erase(p);
        } else {
            if (sz(at_home) == 0) {
                keys_needed[idx] = true;
            }
            at_home.insert(p);
        }
    }

    // check that we have enough keys
    int max_keys = 0;
    int cur_keys = 0;
    vector<array<int, 2>> key_events;
    rep(i, 0, q) {
        if (keys_needed[i]) {
            auto [_, l, r] = trips[i];
            key_events.push_back({l, +1});
            key_events.push_back({r, -1});
        }
    }

    sort(all(key_events));
    for (auto [_, diff] : key_events) {
        cur_keys += diff;
        max_keys = max(max_keys, cur_keys);
    }

    if (max_keys > k) {
        cout << "impossible\n";
    } else {
        for (auto b : keys_needed) {
            cout << b;
        }
        cout << '\n';
    }

    return 0;
}
