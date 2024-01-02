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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<ll> a(n), b(m);
    for (auto &x : a) {
        cin >> x;
    }
    for (auto &x : b) {
        cin >> x;
    }

    // cost of cutting on left side
    int max_weight_cut = n * (n + 1) / 2;
    vector<ll> min_cut_left(max_weight_cut + 1, INFLL);
    
    min_cut_left[0] = 0;
    for (int i = 0; i < n; i++) {
        int amt_taken = i + 1;
        for (int j = max_weight_cut; j >= amt_taken; j--) {
            ckmin(min_cut_left[j], min_cut_left[j - amt_taken] + a[i]);
        }
    }

    // cost of cutting on right side
    
    // the indices you swap from k * (i + 1) -> b[i] at that time
    vector<vector<int>> replace_at(max_weight_cut + 1);
    for (int i = 0; i < m; i++) {
        ll switch_time = (b[i] + i) / (i + 1);
        if (switch_time <= max_weight_cut) {
            replace_at[switch_time].push_back(i);
        }
    }

    ll fixed_portion = 0;
    ll sum_free = (ll) m * (m + 1) / 2;

    vector<ll> min_cut_right(max_weight_cut + 1);
    for (int i = 0; i <= max_weight_cut; i++) {
        for (auto x : replace_at[i]) {
            fixed_portion += b[x];
            sum_free -= x + 1;
        }
        min_cut_right[i] = fixed_portion + sum_free * i;
    }

    ll ans = INFLL;
    for (int i = 0; i <= max_weight_cut; i++) {
        ckmin(ans, min_cut_left[max_weight_cut - i] + min_cut_right[i]);
    }

    cout << ans << '\n';

    return 0;
}
