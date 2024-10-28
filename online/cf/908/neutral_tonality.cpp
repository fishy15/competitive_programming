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
    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(m);
    for (auto &x : a) {
        cin >> x;
    }
    for (auto &x : b) {
        cin >> x;
    }

    map<int, vector<int>> nums_before;
    for (auto x : a) {
        nums_before[x] = {};
    }

    vector<int> smallest;
    for (auto x : b) {
        auto it = nums_before.upper_bound(x);
        if (it == nums_before.begin()) {
            smallest.push_back(x);
        } else {
            prev(it)->second.push_back(x);
        }
    }

    for (auto x : a) {
        auto it = nums_before.find(x);
        if (it != nums_before.end()) {
            auto &v = it->second;
            sort(v.begin(), v.end(), greater<>{});

            for (auto y : v) {
                cout << y << ' ';
            }

            nums_before.erase(it);
        }

        cout << x << ' ';
    }

    sort(smallest.begin(), smallest.end(), greater<>{});
    for (auto x : smallest) {
        cout << x << ' ';
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
