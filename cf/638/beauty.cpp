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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> nums;
    set<int> nn;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
        nn.insert(x);
    }

    if (nn.size() > k) {
        cout << "-1\n";
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (nn.size() == k) break;
        if (!nn.count(i)) nn.insert(i);
    }

    sort(nums.begin(), nums.end());

    cout << n * nn.size() << '\n';
    for (int i = 0; i < n; i++) {
        for (int j : nn) {
            cout << j << ' ';
        }
    }

    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
