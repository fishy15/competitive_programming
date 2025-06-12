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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (auto &x : nums) {
        cin >> x;
        x = abs(x);
    }

    auto wanted = nums[0];
    sort(all(nums));

    auto num_smaller = (int) (find(all(nums), wanted) - begin(nums));
    // smaller ones are always smaller than wanted / always bigger than -wanted
    // bigger ones can choose
    // n odd => n / 2
    // n even => n / 2
    if (num_smaller > n / 2) {
        cout << "NO\n"; 
    } else {
        cout << "YES\n";
    }
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
