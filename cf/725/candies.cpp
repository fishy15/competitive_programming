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
    vector<int> nums(n);

    ll sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        sum += nums[i];
    }

    if (sum % n != 0) {
        cout << "-1\n";
        return;
    }

    sort(nums.begin(), nums.end(), greater<>());

    ll sum_move = 0;
    for (int x : nums) {
        if (x < sum / n) {
            sum_move += sum / n - x;
        }
    }

    if (sum_move == 0) {
        cout << "0\n";
        return;
    }

    ll tot = 0;
    for (int i = 0; i < n; i++) {
        tot += nums[i] - sum / n;
        if (tot >= sum_move) {
            cout << i + 1 << '\n';
            return;
        }
    }

    cout << "-1\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
