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

vector<ll> cost_to_middle(const vector<int> &top, const vector<int> &middle, const vector<array<int, 3>> &offers) {
    int n = top.size();
    vector<ll> top_psum(n + 1);
    vector<ll> mid_psum(n + 1);
    for (int i = 0; i < n; i++) {
        top_psum[i + 1] = top_psum[i] + top[i];
        mid_psum[i + 1] = mid_psum[i] + middle[i];
    }

    vector<vector<int>> to_add(n + 1), to_rem(n + 1);
    for (auto [l, r, k] : offers) {
        to_add[l].push_back(k);
        to_rem[r].push_back(k);
    }

    vector<ll> min_enter(n, -INFLL);
    multiset<int, greater<int>> cur_enter_cost;
    for (int i = 0; i < n; i++) {
        for (auto x : to_add[i]) {
            cur_enter_cost.insert(x);
        }
        for (auto x : to_rem[i]) {
            cur_enter_cost.erase(cur_enter_cost.find(x));
        }

        if (!cur_enter_cost.empty()) {
            min_enter[i] = *cur_enter_cost.begin() + top_psum[i + 1];
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    array<vector<int>, 3> grid;
    for (int i = 0; i < 3; i++) {
        grid[i] = vector<int>(n);
        for (auto &x : grid[i]) {
            cin >> x;
        }
    }

    vector<array<int, 3>> offers(q);
    for (auto &[l, r, k] : offers) {
        cin >> l >> r >> k;
        l--;
    }

    return 0;
}
