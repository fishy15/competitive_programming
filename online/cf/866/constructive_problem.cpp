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

int get_mex(const vector<int> &nums) {
    set<int> in;

    for (auto x : nums) {
        in.insert(x);
    }

    int mex = 0;
    while (in.count(mex)) {
        mex++;
    }
    
    return mex;
}

void solve() {
    int n;
    cin >> n;

    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    int mex = get_mex(nums);

    int l = n;
    int r = -1;

    vector<int> nxt = nums;
    for (int i = 0; i < n; i++) {
        if (nums[i] == mex + 1) {
            l = min(l, i);
            r = max(r, i);
        }
    }

    if (r != -1) {
        for (int i = l; i <= r; i++) {
            nxt[i] = mex;
        }
    } else {
        map<int, int> cnt;
        for (int i = 0; i < n; i++) {
            cnt[nums[i]]++;
        }

        for (int i = 0; i < n; i++) {
            if (nums[i] > mex || cnt[nums[i]] > 1) {
                nxt[i] = mex;
                break;
            }
        }
    }

    if (mex + 1 == get_mex(nxt)) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
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
