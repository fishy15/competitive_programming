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
#define MAXN 200000

using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> nums;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    for (int i = 0; i < n - 1; i++) {
        if (abs(nums[i + 1] - nums[i]) > 1) {
            cout << "YES\n" << i + 1 << ' ' << i + 2 << '\n';
            return;
        }
    }

    cout << "NO\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
