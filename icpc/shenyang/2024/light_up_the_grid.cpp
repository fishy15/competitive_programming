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
#include <bitset>

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

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

vector<ll> gen_mask_costs(int single, int row, int col, int all) {
    vector dist(1 << 16, array<ll, 16>{});
    for_each(all(dist), [&](auto &v) { v.fill(INFLL); });
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> pq;

    auto process = [&](int old_mask, int old_pos, ll old_dist) {
        auto process1 = [&](int toggle, int cost) {
            int new_pos = old_pos ^ toggle;
            int new_mask = old_mask | (1 << new_pos);
            int new_dist = old_dist + cost;
            if (new_dist < dist[new_mask][new_pos]) {
                dist[new_mask][new_pos] = new_dist;
                pq.push({new_dist, new_mask, new_pos});
            }
        };

        process1(0b1000, single);
        process1(0b0100, single);
        process1(0b0010, single);
        process1(0b0001, single);

        process1(0b1100, row);
        process1(0b0011, row);

        process1(0b1010, col);
        process1(0b0101, col);

        process1(0b1111, all);
    };

    // add from a "ghost" node to everything
    // needed since we don't immediately win if empty mask
    process(0, 0b0000, 0);

    while (!pq.empty()) {
        auto [old_dist, old_mask, old_pos] = pq.top();
        pq.pop();
        if (old_dist == dist[old_mask][old_pos]) {
            process(old_mask, old_pos, old_dist);
        }
    }

    vector<ll> ans(1 << 16);
    rep(i, 0, 1 << 16) {
        ans[i] = *min_element(all(dist[i]));
    }

    return ans;
}

int read_grid() {
    string row1, row2;
    cin >> row1 >> row2;

    int res = 0;
    if (row1[1] == '0') res ^= 1 << 3;
    if (row1[0] == '0') res ^= 1 << 2;
    if (row2[1] == '0') res ^= 1 << 1;
    if (row2[0] == '0') res ^= 1 << 0;
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t, single, row, col, all;
    cin >> t >> single >> row >> col >> all;

    // generate the costs of visiting every mask
    auto mask_costs = gen_mask_costs(single, row, col, all);

    // min cost to reach it or any superset
    for (int m = (1 << 16) - 1; m >= 0; m--) {
        rep(i, 0, 16) {
            if (!(m & (1 << i))) {
                ckmin(mask_costs[m], mask_costs[m ^ (1 << i)]);
            }
        }
    }

    while (t--) {
        int n;
        cin >> n;

        int mask = 0;
        rep(i, 0, n) {
            int pos = read_grid();
            mask ^= 1 << pos;
        }

        cout << mask_costs[mask] << '\n';
    }

    return 0;
}
