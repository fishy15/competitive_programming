// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
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
    int n; cin >> n;
    vector<int> nums(n);
    int prev = 0;
    set<int> notpick;
    set<int> pick;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x != prev) {
            nums[i] = x;
            pick.insert(x);
        }
        prev = x;
    }

    for (int i = 1; i <= n; i++) {
        if (!pick.count(i)) {
            notpick.insert(i);
        }
    }

    int curmax = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] == 0) {
            int val = *(notpick.begin());
            if (val >= curmax) {
                cout << "-1\n";
                return;
            }
            nums[i] = val;
            notpick.erase(val);
        }
        curmax = max(curmax, nums[i]);
    }

    for (int i = 0; i < n; i++) {
        cout << nums[i] << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int t; cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
