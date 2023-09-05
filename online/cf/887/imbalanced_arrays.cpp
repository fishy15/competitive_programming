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
    for (auto &x : a) {
        cin >> x;
    }

    deque<int> sorted = {a.begin(), a.end()};
    sort(sorted.begin(), sorted.end());

    for (int i = 0; i < n; i++) {
        int j = n - sorted[i];
        if (j != 0 && j != n && sorted[j - 1] == sorted[j]) {
            cout << "NO\n";
            return;
        }
    }

    if (sorted[0] == 0 && sorted.back() == n) {
        cout << "NO\n";
        return;
    }

    map<int, int> ans;
    int cur_sub = 0;
    int power = n;
    while (!sorted.empty()) {
        if (sorted[0] - cur_sub == 0) {
            ans[sorted[0]] = -power;
            power--;

            while (!sorted.empty() && sorted[0] - cur_sub == 0) {
                sorted.pop_front();
            }
        } else {
            int lst = sorted.back();
            ans[lst] = power;
            power--;

            while (!sorted.empty() && sorted.back() == lst) {
                sorted.pop_back();
                cur_sub++;
            }
        }
    }

    cout << "YES\n";
    for (auto x : a) {
        cout << ans[x] << ' ';
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
