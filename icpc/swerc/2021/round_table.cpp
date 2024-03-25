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

#include <bits/extc++.h>
using namespace __gnu_pbds;

template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    int n;
    cin >> n;

    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }

    // move 0 to the beginning
    auto zero_it = find(p.begin(), p.end(), 0);
    rotate(p.begin(), zero_it, p.end());

    vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        pos[p[i]] = i;
    }

    ll moves = 0;

    Tree<int> inserted_idx;
    inserted_idx.insert(pos[0]);
    inserted_idx.insert(pos[1]);

    // need to insert i in the correct order in the circle
    for (int i = 2; i < n; i++) {
        // index we are currently at
        auto cur_idx = inserted_idx.order_of_key(pos[i - 1]); 
        auto it = prev(inserted_idx.lower_bound(pos[i]));
        auto want_idx = inserted_idx.order_of_key(*it);

        // want to go from cur_idx -> want_idx
        if (want_idx < cur_idx) want_idx += inserted_idx.size();
        moves += (ll) (n - i) * (want_idx - cur_idx);

        inserted_idx.insert(pos[i]);
    }

    cout << moves << '\n';
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
