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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector<int> p(n), inv(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        inv[p[i]] = i;
    }

    set<int> cur_idx;
    for (int i = 0; i < k; i++) {
        cur_idx.insert(inv[i]);
    }

    auto comp = [&] {
        return *cur_idx.rbegin() - *cur_idx.begin();
    };

    int ans = comp();
    for (int i = k; i < n; i++) {
        cur_idx.erase(inv[i - k]);
        cur_idx.insert(inv[i]);
        ans = min(ans, comp());
    }

    cout << ans << '\n';

    return 0;
}
