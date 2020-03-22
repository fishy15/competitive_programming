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
    int n, b; cin >> n >> b;
    vector<int> nums;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
    }

    sort(nums.begin(), nums.end());
    int cur = 0;
    for (int i = 0; i < n; i++) {
        if (cur + nums[i] > b) {
            cout << i;
            return;
        }
        cur += nums[i];
    }

    cout << n;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
        cout << '\n';
    }

    return 0;
}
