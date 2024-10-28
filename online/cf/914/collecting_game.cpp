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

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    map<int, int> cnt;
    for (auto &x : a) {
        cin >> x;
        cnt[x]++;
    }

    ll sum = 0;
    int cur_cnt = 0;
    auto added_end = cnt.begin();
    auto it = cnt.begin();
    map<int, int> ans;
    while (it != cnt.end()) {
        if (added_end == it) {
            sum += (ll) added_end->first * added_end->second;
            cur_cnt += added_end->second;
            added_end++;
        }

        while (added_end != cnt.end() && sum >= added_end->first) {
            sum += (ll) added_end->first * added_end->second;
            cur_cnt += added_end->second;
            added_end++;
        }

        ans[it->first] = cur_cnt;
        it++;
    }

    for (auto x : a) {
        cout << ans[x] - 1 << ' ';
    }
    cout << '\n';
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
