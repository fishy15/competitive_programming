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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    map<int, int> cnt;

    int l = 0;
    int r = 0;

    int ans = INF;

    for (; l < n; l++) {
        while (r < n && (int) cnt.size() < k) {
            cnt[nums[r]]++;
            r++;
        }

        if ((int) cnt.size() >= k) {
            ans = min(ans, r - l);
        }

        // remove current one
        cnt[nums[l]]--;
        if (cnt[nums[l]] == 0) cnt.erase(cnt.find(nums[l]));
    }

    if (ans == INF) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}
