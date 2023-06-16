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
#define MAXN 1010

using namespace std;

int n;
ll nums[MAXN];
ll ans;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    for (int i = 0; i < n; i += 2) {
        ll cur_height = 0;
        ll min_height = INF;
        for (int j = i + 1; j < n; j += 2) {
            cur_height += nums[j - 1];
            cur_height -= nums[j];

            if (i + 1 == j) {
                ans += min(nums[i], nums[j]);
            } else {
                ans += max(0LL, min(min_height, nums[i]) - max(0LL, cur_height) + 1);
            }

            min_height = min(min_height, cur_height);
        }
    }

    cout << ans << '\n';

    return 0;
}
