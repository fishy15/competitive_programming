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
#define MAXN 200010

using namespace std;

constexpr int BLOCK = 450;

int n, m;
int models[MAXN][2];
int cur_ans;

int time_added[MAXN];
vector<int> small_add[BLOCK];

int nxt_change[MAXN];
int cur_stage[MAXN];
int version[MAXN];
vector<array<int, 2>> changes[MAXN];

void precalc() {
    for (int i = 0; i < BLOCK; i++) {
        small_add[i].resize(i);
    }
}

// for periods less than BLOCK

void add_small(int t, int idx) {
    auto [x, y] = models[idx];
    int sz = x + y;

    small_add[sz][(t + x) % sz]++;
    small_add[sz][t % sz]--;
    time_added[idx] = t;
}

void rem_small(int cur_t, int idx) {
    auto [x, y] = models[idx];
    int sz = x + y;
    int t = time_added[idx];

    small_add[sz][(t + x) % sz]--;
    small_add[sz][t % sz]++;

    if ((cur_t - t) % sz >= x) cur_ans--;
}

void calc_small(int t) {
    for (int i = 1; i < BLOCK; i++) {
        cur_ans += small_add[i][t % i];
    }
}

// for periods larger than BLOCK

void add_large(int t, int idx) {
    auto [x, y] = models[idx];
    
    if (t + x < m) {
        nxt_change[idx] = t + x;
        cur_stage[idx] = 0;
        changes[t + x].push_back({idx, version[idx]});
    } else {
        nxt_change[idx] = -1;
    }
}

void rem_large(int cur_t, int idx) {
    version[idx]++;
    if (cur_stage[idx] == 1) {
        cur_ans--;
    }
}

void calc_large(int t) {
    for (auto [idx, v] : changes[t]) {
        if (v != version[idx]) continue;

        auto [x, y] = models[idx];
        int nxt_t;

        if (cur_stage[idx] == 0) {
            cur_ans++;
            nxt_t = t + y;
        } else {
            cur_ans--;
            nxt_t = t + x;
        }

        cur_stage[idx] = 1 - cur_stage[idx];
        if (nxt_t < m) {
            nxt_change[idx] = nxt_t;
            changes[nxt_t].push_back({idx, v});
        } else {
            nxt_change[idx] = -1;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> models[i][0] >> models[i][1];
    }

    for (int t = 0; t < m; t++) {
        int op, k; cin >> op >> k;
        k--;

        calc_small(t);
        calc_large(t);

        if (op == 1) {
            if (models[k][0] + models[k][1] < BLOCK) {
                add_small(t, k);
            } else {
                add_large(t, k);
            }
        } else {
            if (models[k][0] + models[k][1] < BLOCK) {
                rem_small(t, k);
            } else {
                rem_large(t, k);
            }
        }

        cout << cur_ans << '\n';
    }

    return 0;
}
