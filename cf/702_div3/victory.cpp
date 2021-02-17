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
    int n; cin >> n;
    vector<pair<int, int>> nums(n);
    set<int> ans;

    for (int i = 0; i < n; i++) {
        cin >> nums[i].first;
        nums[i].second = i + 1;
    }

    sort(nums.begin(), nums.end());
    map<int, int> cnt;
    for (auto p : nums) cnt[p.first]++;
    ll cur_tot = 0;
    for (auto p : cnt) cur_tot += (ll) p.first * p.second;
    for (auto it = cnt.rbegin(); it != cnt.rend(); it++) {
        auto p = *it;
        if (it == cnt.rbegin() || prev(it)->first <= cur_tot) {
            ans.insert(it->first);
        } else {
            break;
        }
        cur_tot -= (ll) p.first * p.second;
    }

    sort(nums.begin(), nums.end(), [](const pair<int, int> &p1, const pair<int, int> &p2) {
        if (p1.second == p2.second) {
            return p1 < p2;
        }
        return p1.second < p2.second;
    });

    vector<int> v;
    for (int i = 0; i < n; i++) {
        if (ans.count(nums[i].first)) {
            v.push_back(nums[i].second);
        }
    }

    cout << v.size() << '\n';
    for (int x : v) {
        cout << x << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
