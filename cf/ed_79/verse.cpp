// :pray: :steph:
// :pray: :bakekaga:

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
    int n, s; cin >> n >> s;
    vector<int> nums;
    ll sum = 0;
    int pos = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        nums.push_back(x);
        if (x > nums[pos] && sum <= s) {
            pos = i;
        }
        sum += x;
    }

    if (sum <= s) {
        cout << "0\n";
    } else {
        cout << pos + 1 << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
