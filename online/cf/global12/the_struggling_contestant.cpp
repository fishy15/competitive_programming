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
    vector<int> freq(n);
    rep(i, 0, n) {
        cin >> nums[i];
        nums[i]--;
        freq[nums[i]]++;
    }

    auto max_freq = *max_element(all(freq));
    if (max_freq > (n + 1) / 2) {
        cout << "-1\n";
        return;
    }

    int seg_count = 1;
    vector<int> end_count(n);
    end_count[nums[0]]++;
    rep(i, 0, n-1) {
        if (nums[i] == nums[i+1]) {
            seg_count++;
            end_count[nums[i]]++;
            end_count[nums[i+1]]++;
        }
    }
    end_count[nums[n-1]]++;
    
    int ans = seg_count - 1;
    auto max_count = *max_element(all(end_count));
    if (max_count > seg_count + 1) {
        ans += max_count - seg_count - 1;
    }

    cout << ans << '\n';
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
